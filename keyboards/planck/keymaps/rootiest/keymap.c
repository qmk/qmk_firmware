/* Copyright 2021 Chris Laprade
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "raw_hid.h"
#include "print.h"
#include "muse.h"

/*
 * Define keyboard name to be used by UI.
 * This allows for using a different name
 * than the one defined by QMK for your board.
 */
#define KEEB_MODEL_NAME "The Rootiest BoogieBoard"

// Give names to the layers so they are easier to reference
enum custom_layers {
    _BASE,
    _QWERTY = _BASE,
    _COLEMAK,
    _DVORAK,
    _SYMBLS,
    _RAISE = _SYMBLS,
    _NUMBRS,
    _LOWER = _NUMBRS,
    _PLOVER,
    _FEATURS,
    _ADJUST = _FEATURS,
    _NUMPD,
    _TABULA,
    _MOUSY,
};

#define LOWER MO(_NUMBRS)
#define RAISE MO(_SYMBLS)

// unicode hexes
#define UC_DEG UC(0x00B0)   // °
#define UC_DEGF UC(0x2109)  // ℉

// Time (ms) to wait between frames for the wake rgb animation
#define WAKE_ANIMATION_TIMER_FREQUENCY 50

// Is a display connected
// #define USING_OLED_DISPLAY false

// wait DELAY ms before unregistering media keys
#define TAP_CODE_DELAY 10

// Modifier remover
#define WITHOUT_MODS(...)                      \
    do {                                       \
        const uint8_t _real_mods = get_mods(); \
        clear_mods();                          \
        {__VA_ARGS__} set_mods(_real_mods);    \
    } while (0)

// A whole boatload of audio "songs" defined for use by the keyboard
#ifdef AUDIO_ENABLE
float planck_song[][2]    = SONG(PLANCK_SOUND);
float hello_song[][2]     = SONG(ONE_UP_SOUND2);
float bye_song[][2]       = SONG(GOODBYE_SOUND);
float num_song[][2]       = SONG(DVORAK_SOUND);
float qwerty_song[][2]    = SONG(QWERTY_SOUND);
float colemak_song[][2]   = SONG(COLEMAK_SOUND);
float dvorak_song[][2]    = SONG(DVORAK_SOUND);
float funk_song[][2]      = SONG(COLEMAK_SOUND);
float workman_song[][2]   = SONG(WORKMAN_SOUND);
float term_song[][2]      = SONG(TERMINAL_SOUND);
float lover_song[][2]     = SONG(PLOVER_SOUND);
float ode_song[][2]       = SONG(ODE_TO_JOY);
float rock_song[][2]      = SONG(ROCK_A_BYE_BABY);
float clue_song[][2]      = SONG(CLUEBOARD_SOUND);
float camp_song[][2]      = SONG(CAMPANELLA);
float imp_march_song[][2] = SONG(IMPERIAL_MARCH);
float gameover_song[][2]  = SONG(MARIO_GAMEOVER);
float puzzle_song[][2]    = SONG(ZELDA_PUZZLE2);
float caps_on[][2]        = SONG(CAPS_LOCK_ON_SOUND);
float caps_off[][2]       = SONG(CAPS_LOCK_OFF_SOUND);
float slctl_on[][2]       = SONG(SCROLL_LOCK_ON_SOUND);
float slctl_off[][2]      = SONG(SCROLL_LOCK_OFF_SOUND);
float slalt_on[][2]       = SONG(NUM_LOCK_ON_SOUND);
float slalt_off[][2]      = SONG(NUM_LOCK_OFF_SOUND);
float leader_started[][2] = SONG(LEAD_START_SOUND);
float leader_succeed[][2] = SONG(LEAD_SUCCESS_SOUND);
float leader_fail[][2]    = SONG(LEAD_FAIL_SOUND);
float plover_song[][2]    = SONG(PLOVER_SOUND);
float plover_gb_song[][2] = SONG(PLOVER_GOODBYE_SOUND);
#endif

// Declare stored memory config
typedef union {
    uint32_t raw;
    struct {
        bool    do_wakeup_animation : 1;
        uint8_t rgbcon_tracker : 8;
        bool    do_wakeup_audio : 1;
    };
} user_config_t;

user_config_t user_config;

// Initialize variable holding the binary
// representation of active modifiers.
uint8_t mod_state = 0;

// Declare custom keycodes
enum custom_keycodes {
    MO_BASE = SAFE_RANGE,
    MO_SYMBLS,
    MO_NUMBRS,
    MO_FEATURS,
    QWERTY,
    COLEMAK,
    DVORAK,
    PLOVER,
    BACKLIT,
    MUSIC_ON,
    MUSIC_OFF,
    EXT_PLV,
    MY_RGBCON,
    MY_DEGREES,
    ALT_TAB,
    PRINT_WPM_KEY,
    IRONY,
    WAKE_ANI_TOG,
    WAKE_AUD_TOG,
    DO_RESET,
    KC_PRVWD,
    KC_NXTWD,
    KC_LSTRT,
    KC_LEND,
    KC_DLINE,
    KC_REDO,
    KC_SAVE,
    KC_SLCTALL,
    KC_ALTF4,
    KC_KILL,
    KC_LCUT,
    KC_LCOPY,
    KC_NXTAB,
    KC_PRVTAB,
};

// Declare unicode map array
enum unicode_names { BANG, SNEK };
const uint32_t unicode_map[] PROGMEM = {
    //[UCD_BANG]  = 0x203D,   // ‽
    //[UCD_IRONY] = 0x2E2E,   // ⸮
    [SNEK] = 0x1F40D,  // 🐍
};

enum combo_events { ZC_COPY, XV_PASTE };

const uint16_t PROGMEM copy_combo[]  = {KC_Z, KC_C, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_X, KC_V, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [ZC_COPY]  = COMBO_ACTION(copy_combo),
    [XV_PASTE] = COMBO_ACTION(paste_combo),
};

// Tap Dance key declarations
enum {
    TD_DEG_DEGF,
    TD_SMILEY,
    TD_LSHFT_CAPS,
    TD_LCTL_STICKY,
    TD_LALT_STICKY,
    TD_LOWER,
    TD_RAISE,
};

// Declare available Tap-Dance states
typedef enum {
    TD_NONE,
    TD_SINGLE_TAP,
    TD_DOUBLE_TAP,
    TD_TRIPLE_TAP,
    TD_DOUBLE_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_HOLD,
    TD_TRIPLE_HOLD,
    TD_UNKNOWN,
} td_state_t;

// Tap-Dance struct
typedef struct {
    bool       is_press_action;
    td_state_t state;
} td_tap_t;

// Whether or not to do the wake animation+sound
bool do_wake_animation;

// Variable to keep track of the rgb mode assigned by the RGB_CON key
static uint8_t rgbcon_tracker = 0;

// Used by the on-board WPM tracker
char wpm_str[12];

// Variables used for the alt-tab key
bool     is_alt_tab_active = false;
uint16_t alt_tab_timer     = 0;

// Variables used by the Irony key
#define IRONY_HOLD_DELAY 500
uint16_t irony_pressed_time;
bool     irony_active  = false;
bool     irony_shifted = false;
char     irony_str[4]  = "⸮";
char     bang_str[4]   = "‽";

// Variables used for the rgb wakeup animation
static uint16_t wake_rgb_timer;
static uint8_t  wake_rgb_count = 0;
bool            waking_up      = false;
bool            do_wake_audio  = false;

// Muse variables
bool     muse_mode      = false;
bool     musical_mode   = false;
uint8_t  last_muse_note = 0;
uint16_t muse_counter   = 0;
uint8_t  muse_offset    = 70;
uint16_t muse_tempo     = 50;

// Used by Leader key chords
bool did_leader_succeed;
LEADER_EXTERNS();

// Tap-Dance stuffs, initializing functions that are coded further below
td_state_t cur_dance(tap_dance_state_t* state);
void       sml_finished(tap_dance_state_t* state, void* user_data);
void       sml_reset(tap_dance_state_t* state, void* user_data);
void       scap_finished(tap_dance_state_t* state, void* user_data);
void       scap_reset(tap_dance_state_t* state, void* user_data);
void       slctl_finished(tap_dance_state_t* state, void* user_data);
void       slctl_reset(tap_dance_state_t* state, void* user_data);
void       slalt_finished(tap_dance_state_t* state, void* user_data);
void       slalt_reset(tap_dance_state_t* state, void* user_data);
bool       lctl_sticky = false;
bool       lalt_sticky = false;

// This function is called when lock indicators (caps-lock led) are changed/toggled/updated
bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(10, led_state.caps_lock);
#ifdef AUDIO_ENABLE
    static uint8_t caps_state = 0;
    if (caps_state != led_state.caps_lock) {
        // When the caps-lock led state changes play sounds
        led_state.caps_lock ? PLAY_SONG(caps_on) : PLAY_SONG(caps_off);
        caps_state = led_state.caps_lock;
    }
#endif
    return true;
}

// Define key layout/layers
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {                                             // Define all the layers
    [_BASE] = LAYOUT_planck_mit(                                                                           //
        QK_GESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,                      //
        LT(_TABULA, KC_TAB), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,       //
        TD(TD_LSHFT_CAPS), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, SC_SENT,    //
        TD(TD_LCTL_STICKY), QK_LEAD, KC_LGUI, TD(TD_LALT_STICKY), MO(_SYMBLS), KC_SPC, MO(_NUMBRS), KC_LEFT, KC_DOWN, KC_UP, KC_RGHT),
    /*
    Base Layer [0]
     * ,-----------------------------------------------------------------------------------.
     * |Gr/ESC|   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |BckSpc|
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |Tabula|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |   '  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |SH/CAP|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | LCtrl|Leader|  OS  |  Alt |Symbol|    Space    |Number| Left | Dwn  |  Up  | Right|
     * `-----------------------------------------------------------------------------------'
    */

    [_COLEMAK] = LAYOUT_planck_mit(                                                                        //
        QK_GESC, KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_BSPC,                   //
        LT(_TABULA, KC_TAB), KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O, KC_QUOT,          //
        TD(TD_LSHFT_CAPS), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH, SC_SENT,    //
        TD(TD_LCTL_STICKY), QK_LEAD, KC_LGUI, TD(TD_LALT_STICKY), MO(_SYMBLS), KC_SPC, MO(_NUMBRS), KC_LEFT, KC_DOWN, KC_UP, KC_RGHT),
    /*
    Colemak Layer [1]
     * ,-----------------------------------------------------------------------------------.
     * |Gr/ESC|   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |Tabula|   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |SH/CAP|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | LCtrl|Leader|  OS  |  Alt |Symbol|    Space    |Number| Left | Dwn  |  Up  | Right|
     * `-----------------------------------------------------------------------------------'
    */

    [_DVORAK] = LAYOUT_planck_mit(                                                                    //
        QK_GESC, KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_BSPC,         //
        LT(_TABULA, KC_TAB), KC_A, KC_O, KC_E, KC_U, KC_I, KC_D, KC_H, KC_T, KC_TRNS, KC_S, KC_SLSH,  //
        TD(TD_LSHFT_CAPS), KC_SCLN, KC_Q, KC_J, KC_K, KC_X, KC_B, KC_M, KC_W, KC_V, KC_Z, SC_SENT,    //
        TD(TD_LCTL_STICKY), QK_LEAD, KC_LGUI, TD(TD_LALT_STICKY), MO(_SYMBLS), KC_SPC, MO(_NUMBRS), KC_LEFT, KC_DOWN, KC_UP, KC_RGHT),
    /* Dvorak Layer [2]
     * ,-----------------------------------------------------------------------------------.
     * |Gr/ESC|   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |Tabula|   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |SH/CAP|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | LCtrl|Leader|  OS  |  Alt |Symbol|    Space    |Number| Left | Dwn  |  Up  | Right|
     * `-----------------------------------------------------------------------------------'
     */
    [_SYMBLS] = LAYOUT_planck_mit(                                                                                     //
        KC_MPLY, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,       //
        KC_DEL, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,                 //
        KC_TRNS, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, LSFT(KC_LCTL), LSFT(KC_LCTL), KC_HOME, KC_END, KC_TRNS,  //
        TG(_NUMPD), KC_TRNS, KC_TRNS, KC_TRNS, TO(_BASE), KC_TRNS, KC_TRNS, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY),
    /*
    Symbols Layer [3]
    * ,-----------------------------------------------------------------------------------.
    * | Play |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |BckSpc|
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |Delete|  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |   |  |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Shift|  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |LShLCt|LShLCt| Home |  End |------|
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | TG(7)|------|------|------| Base |    -----    | MO(4)| Next | Vol- | Vol+ | Play |
    * `-----------------------------------------------------------------------------------'
    */

    [_NUMBRS] = LAYOUT_planck_mit(                                                                          //
        KC_MPLY, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,                       //
        KC_DEL, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,       //
        KC_TRNS, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, KC_TRNS,  //
        TG(_NUMPD), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TO(_BASE), KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY),

    /*
    Numbers Layer [4]
    * ,-----------------------------------------------------------------------------------.
    * | Play |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |BckSpc|
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |Delete|  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |   \  |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Shift|  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |   #  |   /  | PgUp | PgDwn|------|
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | TG(7)|------|------|------| MO(3)|    -----    | Base | Next | Vol- | Vol+ | Play |
    * `-----------------------------------------------------------------------------------'
    */

    [_PLOVER] = LAYOUT_planck_mit(                                                        //
        KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1,           //
        XXXXXXX, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC,     //
        XXXXXXX, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,  //
        EXT_PLV, XXXXXXX, XXXXXXX, KC_C, KC_V, XXXXXXX, KC_N, KC_M, XXXXXXX, XXXXXXX, XXXXXXX),
    /* Plover Layer [5]
     * ,-----------------------------------------------------------------------------------.
     * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Exit |      |      |   A  |   O  |             |   E  |   U  |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */

    [_FEATURS] = LAYOUT_planck_mit(                                                                                                         //
        LCTL(LALT(KC_DEL)), DO_RESET, DB_TOGG, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, TD(TD_DEG_DEGF), TD(TD_SMILEY), KC_DEL,  //
        RGB_VAI, RGB_VAD, MU_NEXT, AU_ON, AU_OFF, AG_NORM, AG_SWAP, DF(_BASE), DF(_COLEMAK), DF(_DVORAK), TO(_PLOVER), MY_RGBCON,            //
        KC_TRNS, AU_PREV, AU_NEXT, MU_ON, MU_OFF, MI_ON, MI_OFF, KC_TRNS, KC_TRNS, CK_ON, CK_OFF, KC_ENTER,                                  //
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TG(_MOUSY), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
    /*
    Special Features Layer [6]
    * ,-----------------------------------------------------------------------------------.
    * |C+A+DL| Reset| Debug|RGBTog|RGBMod| Hue+ | Hue- | Sat+ | Sat- |Unicod| Emoji|Delete|
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |RGBVAI|RGBVAD|MUNEXT| AU_ON|AU_OFF|RALTGU|SALTGU| Base |Colemk|Dvorak|Plover|RGBCON|
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |------|AUPREV|AU_EXT| MU_ON|MU_OFF| MI_ON|MI_OFF|------|------|CLK-ON|CLKOFF|Enter |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |------|------|------|------|------|    TG(8)    |------|------|------|------|------|
    * `-----------------------------------------------------------------------------------'
    */

    [_NUMPD] = LAYOUT_planck_mit(                                                                              //
        KC_ESC, KC_HOME, KC_UP, KC_END, KC_PERC, KC_LCBR, KC_RCBR, KC_TAB, KC_P7, KC_P8, KC_P9, KC_BSPC,       //
        KC_TILD, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSLS, KC_LBRC, KC_RBRC, KC_PSLS, KC_P4, KC_P5, KC_P6, KC_PMNS,  //
        KC_LSFT, KC_SLSH, KC_CUT, KC_COPY, KC_PASTE, KC_LT, KC_GT, KC_PAST, KC_P1, KC_P2, KC_P3, KC_PPLS,      //
        TO(_BASE), QK_LEAD, KC_LGUI, KC_LALT, SC_LCPO, KC_SPC, SC_RCPC, KC_HASH, KC_P0, KC_PDOT, KC_PENT),
    /*
    Numpad Layer [7]
    * ,-----------------------------------------------------------------------------------.
    * | Esc  | Home |  Up  |  End |   %  |   {  |   }  |  Tab |   7  |   8  |   9  |BckSpc|
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |   ~  | Left | Down | Right|   \  |   [  |   ]  |   /  |   4  |   5  |   6  |   -  |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Shift|   /  |Ctrl+X|Ctrl+C|Ctrl+V|   <  |   >  |   *  |   1  |   2  |   3  |   +  |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Base |Leader|  Alt |  OS  |LCtl/(|    Space    |)/RCtl|   #  |   0  |   .  |Enter |
    * `-----------------------------------------------------------------------------------'
    */
    [_TABULA] = LAYOUT_planck_mit(                                                                                                   //
        KC_ESC, KC_ALTF4, VK_TOGG, PRINT_WPM_KEY, WAKE_ANI_TOG, WAKE_AUD_TOG, KC_REDO, UC_NEXT, UC_WINC, CG_TOGG, AG_TOGG, KC_DLINE,  //
        KC_NXTAB, KC_SLCTALL, KC_SAVE, KC_TRNS, KC_FIND, SH_TG, SH_TG, IRONY, KC_LCUT, KC_LCOPY, KC_TRNS, KC_KILL,                   //
        KC_LSFT, KC_UNDO, KC_CUT, KC_COPY, KC_PASTE, KC_PRVWD, KC_NXTWD, TG(_MOUSY), KC_TRNS, KC_HOME, KC_END, SC_SENT,              //
        TO(_BASE), KC_LCTL, KC_LGUI, KC_LALT, SC_LSPO, ALT_TAB, SC_RSPC, KC_PRVWD, KC_BRID, KC_BRIU, KC_NXTWD),
    /* Tabular Layer [8]
     * ,-----------------------------------------------------------------------------------.
     * |  Esc |Alt+F4|Veloci|  WPM |WakANI|WakAUD|Ctrl+Y|UCMode|UCWinC|CtGUTg|AltGTg| DLine|
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |  Tab |Ctrl+A|Ctrl+S|------|Ctrl+F| SWAP | SWAP |  ⸮^‽ |CutLin|CpyLin|------|DelLin|
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Shift|Ctrl+Z|Ctrl+X|Ctrl+C|Ctrl+V|PrVWin|NxtWin| TG(8)|------| Home |  End |Enter |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Base | LCtrl|  Alt |  OS  |LSft/(|   Alt+Tab   |)/RSft|PrvSel|ScrBr-|ScrBr+|NxtSel|
     * `-----------------------------------------------------------------------------------'
     */

    [_MOUSY] = LAYOUT_planck_mit(                                                                                                  //
        KC_ESC, KC_BTN1, KC_MS_U, KC_BTN2, KC_TRNS, KC_TRNS, KC_TRNS, UC_NEXT, UC_WINC, CG_TOGG, AG_TOGG, KC_BSPC,  //
        KC_TAB, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS, KC_TRNS, IRONY, VK_TOGG, KC_TRNS, KC_TRNS, KC_TRNS,                   //
        KC_LSFT, KC_UNDO, KC_CUT, KC_COPY, KC_PASTE, KC_PRVWD, KC_NXTWD, KC_TRNS, KC_HOME, KC_BTN3, KC_END, SC_SENT,               //
        TO(_BASE), KC_LCTL, KC_LGUI, KC_LALT, KC_BTN1, ALT_TAB, KC_BTN2, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R)};
/* MousePad Layer [9]
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |MsBtn1| MsUp |MsBtn2|------|------|------|UCMode|UCWinC|CtGUTg|AltGTg|BckSpc|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   ~  |MsLeft|MsDown|MsRigt|------|------|------|  ⸮^‽ |Veloci|------|------|------|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|------|Ctrl+X|Ctrl+C|Ctrl+V|------|------|------| Home |MsBtn3|  End |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Base | LCtrl|  Alt |  OS  |MsBtn1|   Alt+Tab   |MsBtn2|MsWhlL|MsWhlD|MsWhlU|MsWhlR|
 * `-----------------------------------------------------------------------------------'
 */

// Define RGB layers | assign leds and their values for each rgb layer
const rgblight_segment_t PROGMEM my_warning_layer[]  = RGBLIGHT_LAYER_SEGMENTS({1, 9, HSV_RED}, {0, 1, HSV_RED});
const rgblight_segment_t PROGMEM my_allgood_layer[]  = RGBLIGHT_LAYER_SEGMENTS({1, 9, HSV_GREEN}, {0, 1, HSV_GREEN});
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS({1, 1, HSV_RED}, {8, 1, HSV_RED});
const rgblight_segment_t PROGMEM my_number_layer[]   = RGBLIGHT_LAYER_SEGMENTS({1, 1, HSV_MAGENTA}, {8, 1, HSV_MAGENTA});
const rgblight_segment_t PROGMEM my_symbol_layer[]   = RGBLIGHT_LAYER_SEGMENTS({1, 1, HSV_GREEN}, {8, 1, HSV_GREEN});
const rgblight_segment_t PROGMEM my_tabula_layer[]   = RGBLIGHT_LAYER_SEGMENTS({3, 4, HSV_CORAL}, {1, 1, HSV_CORAL}, {8, 1, HSV_CORAL});
const rgblight_segment_t PROGMEM my_mousy_layer[]    = RGBLIGHT_LAYER_SEGMENTS({3, 4, HSV_TURQUOISE}, {1, 1, HSV_TURQUOISE}, {8, 1, HSV_TURQUOISE}, {7, 1, HSV_MAGENTA});
const rgblight_segment_t PROGMEM my_numpad_layer[]   = RGBLIGHT_LAYER_SEGMENTS({3, 4, HSV_GOLD}, {1, 1, HSV_GOLD}, {8, 1, HSV_GOLD}, {7, 1, HSV_BLUE});
const rgblight_segment_t PROGMEM my_features_layer[] = RGBLIGHT_LAYER_SEGMENTS({3, 4, HSV_BLUE}, {1, 1, HSV_BLUE}, {8, 1, HSV_BLUE});
const rgblight_segment_t PROGMEM my_base_layer[]     = RGBLIGHT_LAYER_SEGMENTS({0, 0, HSV_BLACK});
const rgblight_segment_t PROGMEM my_colemak_layer[]  = RGBLIGHT_LAYER_SEGMENTS({1, 1, HSV_GREEN});
const rgblight_segment_t PROGMEM my_dvorak_layer[]   = RGBLIGHT_LAYER_SEGMENTS({1, 1, HSV_ORANGE});
const rgblight_segment_t PROGMEM my_plover_layer[]   = RGBLIGHT_LAYER_SEGMENTS({1, 1, HSV_GOLD});

// Define the array of rgb layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(my_base_layer,      // Base Layer
                                                                               my_colemak_layer,   // Overrides previous layer
                                                                               my_dvorak_layer,    // Overrides previous layers
                                                                               my_symbol_layer,    // Overrides previous layers
                                                                               my_number_layer,    // ...etc                                                                              my_features_layer,  // Overrides  layers
                                                                               my_plover_layer,    //
                                                                               my_features_layer,  //
                                                                               my_numpad_layer,    //
                                                                               my_tabula_layer,    //
                                                                               my_mousy_layer,     //
                                                                               my_capslock_layer,  //
                                                                               my_warning_layer,   //
                                                                               my_allgood_layer);  // CapsLock Layer);

// Configure encoders
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (musical_mode) {
        if (clockwise) {
            tap_code16(MU_NEXT);
        } else {
            tap_code16(MU_NEXT);
        }
    } else {
        if (muse_mode) {
            if (IS_LAYER_ON(_RAISE)) {
                if (clockwise) {
                    muse_offset++;
                } else {
                    muse_offset--;
                }
            } else {
                if (clockwise) {
                    muse_tempo += 1;
                } else {
                    muse_tempo -= 1;
                }
            }
        } else {
            if (index == 0) { /* First encoder */
                uint16_t held_keycode_timer = timer_read();
                switch (get_highest_layer(layer_state)) {
                    case 0:                                 // Base Layer
                        if ((get_mods() & MOD_MASK_GUI)) {  // GUI-ed
                            if (clockwise) {
                                tap_code(KC_RIGHT);

                            } else {
                                tap_code(KC_LEFT);
                            }
                        } else if ((get_mods() & MOD_MASK_ALT)) {  // Alt-ed
                            if (clockwise) {
                                tap_code16(LALT(KC_TAB));  // Alt+Tabbing
                            } else {
                                tap_code16(LSA(KC_TAB));
                            }
                        } else if ((get_mods() & MOD_MASK_SHIFT)) {  // Shifted
                            const uint8_t _real_mods = get_mods();
                            unregister_code16(KC_LSFT);
                            unregister_code16(KC_RSFT);
                            clear_mods();
                            if (clockwise) {
                                tap_code16(KC_MS_WH_DOWN);
                            } else {
                                tap_code16(KC_MS_WH_UP);
                            }
                            set_mods(_real_mods);
                        } else if ((get_mods() & MOD_MASK_CTRL)) {  // Ctrl-ed
                            if (clockwise) {
                                tap_code16(RCTL(KC_TAB));  // Ctrl+Tabbing
                            } else {
                                tap_code16(RCS(KC_TAB));
                            }
                        } else {  // Normal or unspecified modifiers
                            if (clockwise) {
                                // Volume control requires extra timer to function correctly
                                register_code(KC_VOLU);
                                while (timer_elapsed(held_keycode_timer) < TAP_CODE_DELAY) {
                                    // no-op
                                }
                                unregister_code(KC_VOLD);
                            } else {
                                register_code(KC_VOLD);
                                while (timer_elapsed(held_keycode_timer) < TAP_CODE_DELAY) {
                                    // no-op
                                }
                                unregister_code(KC_VOLU);
                            }
                        }
                        return false;
                        break;
                    case 3:  // Symbols Layer
                        if (clockwise) {
                            tap_code(KC_WH_D);  // Mouse wheeling
                        } else {
                            tap_code(KC_WH_U);
                        }
                        return false;
                        break;
                    case 4:  // Numbers Layer
                        if (clockwise) {
                            tap_code(KC_WH_D);  // Mouse wheeling
                        } else {
                            tap_code(KC_WH_U);
                        }
                        return false;
                        break;
                    case 6:  // Features Layer
                        if (clockwise) {
                            tap_code16(KC_DOWN);
                        } else {
                            tap_code16(KC_UP);
                        }
                    default:  // Any other layer
                        if ((get_mods() & MOD_MASK_CSAG)) {
                            if (clockwise) {
                                WITHOUT_MODS({ SEND_STRING(SS_TAP(X_RIGHT)); });
                            } else {
                                WITHOUT_MODS({ SEND_STRING(SS_TAP(X_LEFT)); });
                            }
                        } else {
                            if (clockwise) {
                                tap_code(KC_DOWN);  // Simple Up/Down
                            } else {
                                tap_code(KC_UP);
                            }
                        }
                        return false;
                        break;
                }
            } else if (index == 1) { /* Second encoder (if we had one) */
                if (clockwise) {
                    tap_code16(LCTL(KC_LEFT));  // Ctrl+Left/Right
                } else {
                    tap_code16(LCTL(KC_RIGHT));
                }
            }
        }
    }
    return true;
}

// OLED CONFIGURATION
/*
static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00};

    oled_write_P(qmk_logo, false);
}
*/

// Process Combo events
void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case ZC_COPY:
            if (pressed) {
                tap_code16(LCTL(KC_C));
            }
            break;
        case XV_PASTE:
            if (pressed) {
                tap_code16(LCTL(KC_V));
            }
            break;
    }
}

// Runs every time a key is pressed or released
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
#ifdef CONSOLE_ENABLE
    dprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif
    // Store the current modifier state in the variable for later reference
    mod_state = get_mods();
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
                PLAY_SONG(qwerty_song);
            }
            return false;
            break;
        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
                PLAY_SONG(colemak_song);
            }
            return false;
            break;
        case DVORAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_DVORAK);
                PLAY_SONG(dvorak_song);
            }
            return false;
            break;
        case PLOVER:
            if (record->event.pressed) {
#ifdef AUDIO_ENABLE
                stop_all_notes();
                PLAY_SONG(plover_song);
#endif
                layer_off(_RAISE);
                layer_off(_LOWER);
                layer_off(_ADJUST);
                layer_on(_PLOVER);
                if (!eeconfig_is_enabled()) {
                    eeconfig_init();
                }
                keymap_config.raw  = eeconfig_read_keymap();
                keymap_config.nkro = 1;
                eeconfig_update_keymap(keymap_config.raw);
            }
            return false;
            break;
        case EXT_PLV:
            if (record->event.pressed) {
#ifdef AUDIO_ENABLE
                PLAY_SONG(plover_gb_song);
#endif
                layer_off(_PLOVER);
            }
            return false;
            break;
        case MO_SYMBLS:
            if (record->event.pressed) {
                layer_on(_SYMBLS);
            } else {
                layer_off(_SYMBLS);
            }
            return false;
        case MO_NUMBRS:
            if (record->event.pressed) {
                layer_on(_NUMBRS);
            } else {
                layer_off(_NUMBRS);
            }
            return false;
        case MO_FEATURS:
            if (record->event.pressed) {
                layer_on(_FEATURS);
            } else {
                layer_off(_FEATURS);
            }
            return false;
        case MUSIC_ON:
            if (record->event.pressed) {
                musical_mode = true;
                register_code16(MU_ON);
            } else {
                unregister_code16(MU_ON);
            }
            break;
        case MUSIC_OFF:
            if (record->event.pressed) {
                musical_mode = false;
                register_code16(MU_OFF);
            } else {
                unregister_code16(MU_OFF);
            }
            break;
        case KC_PRVWD:  // Control+Left
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_LEFT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                }
            }
            break;
        case KC_NXTWD:  // Control+Right
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_RIGHT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                }
            }
            break;
        case KC_PRVTAB:  // Control+Shift+Tab
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_mods(mod_config(MOD_LSFT));
                register_code(KC_TAB);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_mods(mod_config(MOD_LSFT));
                unregister_code(KC_TAB);
            }
            break;
        case KC_NXTAB:  // Control+Tab
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_TAB);
                } else {
                    register_mods(mod_config(MOD_LSFT));
                    register_code(KC_TAB);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                }
            }
            break;
        case KC_LSTRT:  // Basically just Home
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    // CMD-arrow on Mac, but we have CTL and GUI swapped
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                } else {
                    register_code(KC_HOME);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_code(KC_HOME);
                }
            }
            break;
        case KC_LEND:  // Basically just End
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    // CMD-arrow on Mac, but we have CTL and GUI swapped
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                } else {
                    register_code(KC_END);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_code(KC_END);
                }
            }
            break;
        case KC_DLINE:  // Control+BackSpace
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_BSPC);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_BSPC);
            }
            break;
        case KC_COPY:  // Copy: Control+C
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_C);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_C);
            }
            return false;
        case KC_PASTE:  // Paste: Control+V
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_V);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_V);
            }
            return false;
        case KC_CUT:  // Cut: Control+X
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_X);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_X);
            }
            return false;
            break;
        case KC_UNDO:  // Undo: Control+Z
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_Z);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_Z);
            }
            return false;
        case KC_REDO:  // Redo: Control+Y
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_Y);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_Y);
            }
            break;
        case KC_SAVE:  // Save: Control+S
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_S);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_S);
            }
            return false;
        case KC_FIND:  // Find: Control+F
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_F);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_F);
            }
            return false;
        case KC_SLCTALL:  // Select All: Control+A
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_A);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_A);
            }
            return false;
        case KC_KILL:  // Kill: Delete Line
            if (record->event.pressed) {
                tap_code(KC_HOME);
                register_mods(mod_config(MOD_LSFT));
                tap_code(KC_END);
                unregister_mods(mod_config(MOD_LSFT));
                tap_code(KC_DELETE);
            } else {
            }
            return false;
        case KC_LCUT:  // Cut Line
            if (record->event.pressed) {
                tap_code(KC_HOME);
                register_mods(mod_config(MOD_LSFT));
                tap_code(KC_END);
                unregister_mods(mod_config(MOD_LSFT));
                register_mods(mod_config(MOD_LCTL));
                tap_code(KC_X);
                unregister_mods(mod_config(MOD_LCTL));
            } else {
            }
            return false;
        case KC_LCOPY:  // Copy Line
            if (record->event.pressed) {
                tap_code(KC_HOME);
                register_mods(mod_config(MOD_LSFT));
                tap_code(KC_END);
                unregister_mods(mod_config(MOD_LSFT));
                register_mods(mod_config(MOD_LCTL));
                tap_code(KC_C);
                unregister_mods(mod_config(MOD_LCTL));
                tap_code(KC_END);
            } else {
            }
            return false;
        case KC_ALTF4:  // Close Window: Alt+F4
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LALT));
                register_code(KC_F4);
            } else {
                unregister_mods(mod_config(MOD_LALT));
                unregister_code(KC_F4);
            }
            return false;
        case ALT_TAB:  // Change Window: Super ⭍ Alt+Tab
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                register_code(KC_TAB);
#ifdef CONSOLE_ENABLE
                dprint("I've tabbed to another window!\n");
#endif
            } else {
                unregister_code(KC_TAB);
            }
            break;
        case KC_BSPC: {
            // Initialize a boolean variable that keeps track
            // of the delete key status: registered or not?
            static bool delkey_registered;
            if (record->event.pressed) {
                // Detect the activation of either shift keys
                if (mod_state & MOD_MASK_SHIFT) {
                    // First temporarily canceling both shifts so that
                    // shift isn't applied to the KC_DEL keycode
                    del_mods(MOD_MASK_SHIFT);
                    register_code(KC_DEL);
                    // Update the boolean variable to reflect the status of KC_DEL
                    delkey_registered = true;
                    // Reapplying modifier state so that the held shift key(s)
                    // still work even after having tapped the Backspace/Delete key.
                    set_mods(mod_state);
                    return false;
                }
            } else {  // on release of KC_BSPC
                // In case KC_DEL is still being sent even after the release of KC_BSPC
                if (delkey_registered) {
                    unregister_code(KC_DEL);
                    delkey_registered = false;
                    return false;
                }
            }
        }
            // Let QMK process the KC_BSPC keycode as usual outside of shift
            return true;

        case DO_RESET:  // Reset button with LED indication
            if (record->event.pressed) {
                rgblight_set_effect_range(0, 9);
                rgblight_sethsv_noeeprom(HSV_RED);
                rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
                rgblight_blink_layer(11, 5000);
                reset_keyboard();
            }
            break;
        case WAKE_ANI_TOG:  // Toggle the Wakeup RGB animation
            if (record->event.pressed) {
                user_config.do_wakeup_animation ^= 1;   // Toggles the status
                eeconfig_update_user(user_config.raw);  // Writes the new status to EEPROM
                if (user_config.do_wakeup_animation) {
                    print("Wake animation enabled.\n");
                    PLAY_SONG(slctl_on);

                } else {
                    print("Wake animation disabled.\n");
                    PLAY_SONG(slctl_off);
                }
            }
            break;
        case WAKE_AUD_TOG:  // Toggle the wake-up music
            if (record->event.pressed) {
                user_config.do_wakeup_audio ^= 1;       // Toggles the status
                eeconfig_update_user(user_config.raw);  // Writes the new status to EEPROM
                if (user_config.do_wakeup_audio) {
                    print("Wake music enabled.\n");
                    PLAY_SONG(slctl_on);

                } else {
                    print("Wake music disabled.\n");
                    PLAY_SONG(slctl_off);
                }
            }
            break;
        case IRONY:  // Outputs Irony/Interrobang symbols
            if ((get_mods() & MOD_MASK_SHIFT)) {
                irony_shifted = true;
            } else {
                irony_shifted = false;
            }
            if (record->event.pressed) {
                if (irony_shifted) {
                    send_unicode_string(bang_str);
                } else {
                    send_unicode_string(irony_str);
                }
                irony_active       = true;
                irony_pressed_time = timer_read();
            } else {
                irony_active       = false;
                irony_pressed_time = 0;
                irony_shifted      = false;
            }
            return false;
        case TG(_NUMPD):  // Toggle the NumPad layer
            if (record->event.pressed) {
#ifdef AUDIO_ENABLE
                PLAY_SONG(hello_song);
#endif
                print("I've activated the NumPad!\n");
            } else {
            }
            break;
        case TG(_TABULA):  // Toggle the Tabula layer
            if (record->event.pressed) {
#ifdef AUDIO_ENABLE
                PLAY_SONG(lover_song);
#endif
                print("I've activated Tabular!\n");
            } else {
            }
            break;
        case TG(_MOUSY):  // Toggle the MouseyPad layer
            if (record->event.pressed) {
#ifdef AUDIO_ENABLE
                PLAY_SONG(funk_song);
#endif
                print("I've activated the MousePad!\n");
            } else {
            }
            break;
        case TO(_BASE):  // Return to the base layer
            if (record->event.pressed) {
#ifdef AUDIO_ENABLE
                PLAY_SONG(planck_song);
#endif
                print("I've returned to the Base Layer!\n");
            } else {
            }
            break;
        case PRINT_WPM_KEY:  // Prints the current average words-per-minute to the console
            sprintf(wpm_str, "Current WPM: %hu", get_current_wpm());
            printf("%s\n", wpm_str);
            break;

        case MY_RGBCON:  // Cycles through custom RGB animation presets
            if (record->event.pressed) {
                // when keycode RGB-CON is pressed
                user_config.rgbcon_tracker = rgbcon_tracker + 1;  // Toggles the status
                eeconfig_update_user(user_config.raw);
                switch (rgbcon_tracker) {
                    case 0:
                        rgblight_set_effect_range(0, 9);
                        rgblight_sethsv(HSV_BLACK);
                        rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
                        print("Changed RGB mode to: Disabled RGB\n");
                        rgbcon_tracker++;
                        break;
                    case 1:
                        rgblight_set_effect_range(0, 9);
                        rgblight_sethsv(HSV_WHITE);
                        rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
                        print("Changed RGB mode to: Static White\n");
                        rgbcon_tracker++;
                        break;
                    case 2:
                        rgblight_set_effect_range(0, 9);
                        rgblight_sethsv(HSV_CYAN);
                        rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
                        print("Changed RGB mode to: Static Cyan\n");
                        rgbcon_tracker++;
                        break;
                    case 3:
                        rgblight_set_effect_range(0, 9);
                        rgblight_sethsv(HSV_WHITE);
                        rgblight_mode(RGBLIGHT_MODE_BREATHING);
                        print("Changed RGB mode to: Breathing Lights\n");
#ifdef AUDIO_ENABLE
                        print("Played Marching song!\n");
                        PLAY_SONG(imp_march_song);
#endif
                        rgbcon_tracker++;
                        break;
                    case 4:
                        rgblight_set_effect_range(0, 9);
                        rgblight_sethsv(HSV_RED);
                        rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL);
                        print("Changed RGB mode to: Rainbow Swirl\n");
                        rgbcon_tracker++;
                        break;
                    case 5:
                        rgblight_set_effect_range(0, 9);
                        rgblight_sethsv(HSV_CYAN);
                        rgblight_mode(RGBLIGHT_MODE_RAINBOW_MOOD);
                        print("Changed RGB mode to: Rainbow Mood\n");
#ifdef AUDIO_ENABLE
                        print("Played Game Over song!\n");
                        PLAY_SONG(gameover_song);
#endif
                        rgbcon_tracker = 0;
                        break;
                    case 6:
                        rgblight_set_effect_range(0, 9);
                        rgblight_sethsv(HSV_BLACK);
                        rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
                        print("Changed RGB mode to: Disabled RGB\n");
                        rgbcon_tracker = 1;
                        break;
                }
            } else {
            }
            break;
    }
    return true;
};

// Runs *after* a key is pressed
void post_process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case QK_DEBUG_TOGGLE:
            // Blink the warning layer when the debug key is pressed
            rgblight_blink_layer_repeat(debug_enable ? 11 : 12, 1500, 3);

            // Update the console with the debug mode status
            if (debug_enable) {
                print("Debug mode enabled.\n");
                PLAY_SONG(slctl_on);

            } else {
                print("Debug mode disabled.\n");
                PLAY_SONG(slctl_off);
            }
            break;
    }
}

// RGB Default Layer assignments
layer_state_t default_layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _SYMBLS, _NUMBRS, _FEATURS);

    // Sets the default RGB layer states
    rgblight_set_layer_state(0, layer_state_cmp(state, _BASE));
    rgblight_set_layer_state(1, layer_state_cmp(state, _COLEMAK));
    rgblight_set_layer_state(2, layer_state_cmp(state, _DVORAK));
    return state;
}

// RGB Layer assignments
layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _SYMBLS, _NUMBRS, _FEATURS);

    // Sets the RGB layer states
    rgblight_set_layer_state(5, layer_state_cmp(state, _PLOVER));
    rgblight_set_layer_state(6, layer_state_cmp(state, _FEATURS));
    rgblight_set_layer_state(3, layer_state_cmp(state, _SYMBLS));
    rgblight_set_layer_state(4, layer_state_cmp(state, _NUMBRS));
    rgblight_set_layer_state(7, layer_state_cmp(state, _NUMPD));
    rgblight_set_layer_state(8, layer_state_cmp(state, _TABULA));
    rgblight_set_layer_state(9, layer_state_cmp(state, _MOUSY));
    return state;
}

// Runs the wakeup rgb animation + music
void rgb_wakeup_sequence(void) {
    if (waking_up) {
        if ((timer_elapsed(wake_rgb_timer) > WAKE_ANIMATION_TIMER_FREQUENCY)) {
            if (wake_rgb_count < 1) {
                rgblight_sethsv_noeeprom(HSV_OFF);
                rgblight_set_effect_range(0, 9);
            } else if (wake_rgb_count < 2 && wake_rgb_count > 0) {
                rgblight_sethsv_noeeprom(HSV_BLACK);
                rgblight_set_effect_range(0, 2);
                rgblight_sethsv_noeeprom(HSV_WHITE);
                rgblight_set_effect_range(2, 9);
            } else if (wake_rgb_count < 3 && wake_rgb_count > 1) {
                rgblight_sethsv_noeeprom(HSV_BLACK);
                rgblight_set_effect_range(0, 2);
                rgblight_sethsv_noeeprom(HSV_WHITE);
                rgblight_set_effect_range(2, 9);
            } else if (wake_rgb_count < 4 && wake_rgb_count > 2) {
                rgblight_sethsv_noeeprom(HSV_BLACK);
                rgblight_set_effect_range(0, 3);
                rgblight_sethsv_noeeprom(HSV_WHITE);
                rgblight_set_effect_range(3, 9);
            } else if (wake_rgb_count < 5 && wake_rgb_count > 3) {
                rgblight_sethsv_noeeprom(HSV_BLACK);
                rgblight_set_effect_range(0, 4);
                rgblight_sethsv_noeeprom(HSV_WHITE);
                rgblight_set_effect_range(4, 9);
            } else if (wake_rgb_count < 6 && wake_rgb_count > 4) {
                rgblight_sethsv_noeeprom(HSV_BLACK);
                rgblight_set_effect_range(0, 5);
                rgblight_sethsv_noeeprom(HSV_WHITE);
                rgblight_set_effect_range(5, 9);
            } else if (wake_rgb_count < 7 && wake_rgb_count > 5) {
                rgblight_sethsv_noeeprom(HSV_BLACK);
                rgblight_set_effect_range(0, 6);
                rgblight_sethsv_noeeprom(HSV_WHITE);
                rgblight_set_effect_range(6, 9);
            } else if (wake_rgb_count < 8 && wake_rgb_count > 6) {
                rgblight_sethsv_noeeprom(HSV_BLACK);
                rgblight_set_effect_range(0, 7);
                rgblight_sethsv_noeeprom(HSV_WHITE);
                rgblight_set_effect_range(7, 9);
            } else if (wake_rgb_count < 9 && wake_rgb_count > 7) {
                rgblight_sethsv_noeeprom(HSV_BLACK);
                rgblight_set_effect_range(0, 8);
                rgblight_sethsv_noeeprom(HSV_WHITE);
                rgblight_set_effect_range(8, 9);
            } else if (wake_rgb_count < 10 && wake_rgb_count > 8) {
                rgblight_sethsv_noeeprom(HSV_BLACK);
                rgblight_set_effect_range(0, 0);
                rgblight_sethsv_noeeprom(HSV_WHITE);
                rgblight_set_effect_range(0, 9);
            } else if (wake_rgb_count < 11 && wake_rgb_count > 9) {
                rgblight_sethsv_noeeprom(HSV_BLACK);
                rgblight_set_effect_range(0, 8);
                rgblight_sethsv_noeeprom(HSV_WHITE);
                rgblight_set_effect_range(8, 9);
            } else if (wake_rgb_count < 12 && wake_rgb_count > 10) {
                rgblight_sethsv_noeeprom(HSV_BLACK);
                rgblight_set_effect_range(0, 7);
                rgblight_sethsv_noeeprom(HSV_WHITE);
                rgblight_set_effect_range(7, 9);
            } else if (wake_rgb_count < 13 && wake_rgb_count > 11) {
                rgblight_sethsv_noeeprom(HSV_BLACK);
                rgblight_set_effect_range(0, 6);
                rgblight_sethsv_noeeprom(HSV_WHITE);
                rgblight_set_effect_range(6, 9);
            } else if (wake_rgb_count < 14 && wake_rgb_count > 12) {
                rgblight_sethsv_noeeprom(HSV_BLACK);
                rgblight_set_effect_range(0, 5);
                rgblight_sethsv_noeeprom(HSV_WHITE);
                rgblight_set_effect_range(5, 9);
            } else if (wake_rgb_count < 15 && wake_rgb_count > 13) {
                rgblight_sethsv_noeeprom(HSV_BLACK);
                rgblight_set_effect_range(0, 4);
                rgblight_sethsv_noeeprom(HSV_WHITE);
                rgblight_set_effect_range(4, 9);
            } else if (wake_rgb_count < 16 && wake_rgb_count > 14) {
                rgblight_sethsv_noeeprom(HSV_BLACK);
                rgblight_set_effect_range(0, 3);
                rgblight_sethsv_noeeprom(HSV_WHITE);
                rgblight_set_effect_range(3, 9);
            } else if (wake_rgb_count < 17 && wake_rgb_count > 15) {
                rgblight_sethsv_noeeprom(HSV_BLACK);
                rgblight_set_effect_range(0, 2);
                rgblight_sethsv_noeeprom(HSV_WHITE);
                rgblight_set_effect_range(2, 9);
            } else if (wake_rgb_count < 18 && wake_rgb_count > 16) {
                rgblight_sethsv_noeeprom(HSV_BLACK);
                rgblight_set_effect_range(0, 1);
                rgblight_sethsv_noeeprom(HSV_WHITE);
                rgblight_set_effect_range(1, 9);
            } else if (wake_rgb_count > 17) {
                // Final frame of wake-up rgb animation
                rgblight_sethsv_noeeprom(HSV_BLACK);
                rgblight_set_effect_range(0, 9);
                waking_up = false;
                print("I have awoken!\n");
#ifdef AUDIO_ENABLE
                // Play the wake-up sound *after* we finish the animation
                if (do_wake_audio) {
                    PLAY_SONG(puzzle_song);
                }
#endif
            }
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            wake_rgb_count++;
            wake_rgb_timer = timer_read();
        }
    }
}

// Spits out some unicode special characters in response to a tap-dance
void send_degree_symbol(tap_dance_state_t* state, void* user_data) {
    switch (state->count) {
        case 4:
            // ℃
            unicode_input_start();
            register_hex(0x2103);
            unicode_input_finish();
            print("You pressed the Degrees key 4 times!\n");
            reset_tap_dance(state);
            break;
        case 3:
            //℉
            unicode_input_start();
            register_hex(0x2109);
            unicode_input_finish();
            print("You pressed the Degrees key 3 times!\n");
            reset_tap_dance(state);
            break;
        case 2:
            // €
            unicode_input_start();
            register_hex(0x20AC);
            unicode_input_finish();
            print("You pressed the Degrees key 2 times!\n");
            reset_tap_dance(state);
            break;
        case 1:
            // °
            unicode_input_start();
            register_hex(0x00B0);
            unicode_input_finish();
            print("You pressed the Degrees key 1 time!\n");
            reset_tap_dance(state);
            break;
    }
}

// Handles per-key configuration of Retro-Tapping
bool get_retro_tapping(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        default:
            return false;
    }
}
// Handles per-key configuration of Hold-on-Other-Key-Press
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            return true;
        default:
            return false;
    }
}
// Handles per-key configuration of Quick-Tap
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        default:
            return QUICK_TAP_TERM;
    }
}
// Handles per-key configuration of Permissive-Hold
bool get_permissive_hold(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        default:
            return false;
    }
}
/*
 * The following two functions make leader keys "musical"
 * by playing sound at different stages of the leader chord
 */
// Called when you tap the Leader key
void leader_start_user(void) {
#ifdef AUDIO_ENABLE
    PLAY_SONG(leader_started);
#endif
}
// Called when either the leader sequence is completed, or the leader timeout is hit
void leader_end_user(void) {
    if (did_leader_succeed) {
#ifdef AUDIO_ENABLE
        PLAY_SONG(leader_succeed);
#endif
    } else {
#ifdef AUDIO_ENABLE
        PLAY_SONG(leader_fail);
#endif
    }
}

// Monitors and labels the current state of any tap-dances
td_state_t cur_dance(tap_dance_state_t* state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else
            return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted)
            return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed)
            return TD_DOUBLE_HOLD;
        else
            return TD_DOUBLE_TAP;
    }
    if (state->count == 3) {
        if (state->interrupted || !state->pressed)
            return TD_TRIPLE_TAP;
        else
            return TD_TRIPLE_HOLD;
    } else
        return TD_UNKNOWN;
}

// Create an instance of 'td_tap_t' for each tap dance.
static td_tap_t sml_state   = {.is_press_action = true, .state = TD_NONE};
static td_tap_t scap_state  = {.is_press_action = true, .state = TD_NONE};
static td_tap_t slctl_state = {.is_press_action = true, .state = TD_NONE};
static td_tap_t slalt_state = {.is_press_action = true, .state = TD_NONE};

// Left-Shift->Sticky-Caps tap-dance finished
void scap_finished(tap_dance_state_t* state, void* user_data) {
    scap_state.state = cur_dance(state);
    switch (scap_state.state) {
        case TD_SINGLE_HOLD:
            register_code(KC_LSFT);
            break;
        default:
            if (host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK)) {
                tap_code(KC_CAPS);
                reset_tap_dance(state);
                break;
            } else {
                if ((state->count) >= TAPPING_TOGGLE) {
                    tap_code(KC_CAPS);
                    reset_tap_dance(state);
                    break;
                } else {
                    register_code(KC_LSFT);
                    break;
                }
            }
    }
}

// Left-Shift->Sticky-Caps tap-dance reset
void scap_reset(tap_dance_state_t* state, void* user_data) {
    unregister_code(KC_LSFT);
    scap_state.state = TD_NONE;
}

// Sticky-Left-Control tap-dance finished
void slctl_finished(tap_dance_state_t* state, void* user_data) {
    slctl_state.state = cur_dance(state);
    switch (slctl_state.state) {
        case TD_SINGLE_HOLD:
            register_code(KC_LCTL);
            break;
        default:
            if (lctl_sticky) {
                unregister_code(KC_LCTL);
                lctl_sticky = false;
                PLAY_SONG(slctl_off);
                reset_tap_dance(state);
                break;
            } else {
                if ((state->count) >= TAPPING_TOGGLE) {
                    register_code(KC_LCTL);
                    lctl_sticky = true;
                    PLAY_SONG(slctl_on);
                    reset_tap_dance(state);
                    break;
                } else {
                    register_code(KC_LCTL);
                    reset_tap_dance(state);
                    break;
                }
            }
    }
}

// Sticky-Left-Control tap-dance reset
void slctl_reset(tap_dance_state_t* state, void* user_data) {
    if (!lctl_sticky) {
        unregister_code(KC_LCTL);
        slctl_state.state = TD_NONE;
    } else {
        slctl_state.state = TD_NONE;
    }
}

// Sticky-Left-Alt tap-dance finished
void slalt_finished(tap_dance_state_t* state, void* user_data) {
    slalt_state.state = cur_dance(state);
    switch (slalt_state.state) {
        case TD_SINGLE_HOLD:
            register_code(KC_LALT);
            break;
        default:
            if (lalt_sticky) {
                unregister_code(KC_LALT);
                lalt_sticky = false;
                PLAY_SONG(slalt_off);
                reset_tap_dance(state);
                break;
            } else {
                if ((state->count) >= TAPPING_TOGGLE) {
                    register_code(KC_LALT);
                    lalt_sticky = true;
                    PLAY_SONG(slalt_on);
                    reset_tap_dance(state);
                    break;
                } else {
                    register_code(KC_LALT);
                    reset_tap_dance(state);
                    break;
                }
            }
    }
}

// Sticky-Left-Alt tap-dance reset
void slalt_reset(tap_dance_state_t* state, void* user_data) {
    if (!lalt_sticky) {
        unregister_code(KC_LALT);
        slalt_state.state = TD_NONE;
    } else {
        slalt_state.state = TD_NONE;
    }
}

// Smiley key tap-dance finished
void sml_finished(tap_dance_state_t* state, void* user_data) {
    sml_state.state = cur_dance(state);
    switch (sml_state.state) {
        default:
            switch (state->count) {
                default:
                    // 👍
                    send_unicode_string("👍");
                    print("You pressed the Emoji key at least 11 times!\n");
                    reset_tap_dance(state);
                    break;
                case 10:
                    // 👎
                    send_unicode_string("👎");
                    print("You pressed the Emoji key 10 times!\n");
                    reset_tap_dance(state);
                    break;
                case 9:
                    //🍌
                    send_unicode_string("🍌");
                    print("You pressed the Emoji key 9 times!\n");
                    reset_tap_dance(state);
                    break;
                case 8:
                    // 🍑
                    send_unicode_string("🍑");
                    print("You pressed the Emoji key 8 times!\n");
                    reset_tap_dance(state);
                    break;
                case 7:
                    // 🐕
                    send_unicode_string("🐕");
                    print("You pressed the Emoji key 7 times!\n");
                    reset_tap_dance(state);
                    break;
                case 6:
                    // 🐈
                    send_unicode_string("🐈");
                    print("You pressed the Emoji key 6 times!\n");
                    reset_tap_dance(state);
                    break;
                case 5:
                    // 🐍
                    send_unicode_string("🐍");
                    print("You pressed the Emoji key 5 times!\n");
                    reset_tap_dance(state);
                    break;
                case 4:
                    //🐒
                    send_unicode_string("🐒");
                    print("You pressed the Emoji key 4 times!\n");
                    reset_tap_dance(state);
                    break;
                case 3:
                    // 💩
                    send_unicode_string("💩");
                    print("You pressed the Emoji key 3 times!\n");
                    reset_tap_dance(state);
                    break;
                case 2:
                    // 🙁
                    send_unicode_string("🙁");
                    print("You pressed the Emoji key 2 times!\n");
                    reset_tap_dance(state);
                    break;
                case 1:
                    // 🙂
                    send_unicode_string("🙂");
                    print("You pressed the Emoji key 1 time!\n");
                    reset_tap_dance(state);
                    break;
            }
            break;
        case TD_SINGLE_HOLD:
            // 👍
            send_unicode_string("👍");
            print("You single-held the Emoji key!\n");
            reset_tap_dance(state);
            break;
        case TD_DOUBLE_HOLD:
            // 👎
            send_unicode_string("👎");
            print("You double-held the Emoji key!\n");
            reset_tap_dance(state);
            break;
        case TD_TRIPLE_HOLD:
            //🤯
            send_unicode_string("🤯");
            print("You triple-held the Emoji key!\n");
            reset_tap_dance(state);
            break;
        case TD_NONE:
            reset_tap_dance(state);
            break;
    }
}
void sml_reset(tap_dance_state_t* state, void* user_data) { sml_state.state = TD_NONE; }

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for °, twice for ℉, thrice for ℃
    [TD_DEG_DEGF]    = ACTION_TAP_DANCE_FN(send_degree_symbol),                          //
    [TD_LSHFT_CAPS]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, scap_finished, scap_reset),    //
    [TD_LCTL_STICKY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, slctl_finished, slctl_reset),  //
    [TD_LALT_STICKY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, slalt_finished, slalt_reset),  //
    [TD_SMILEY]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sml_finished, sml_reset),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(TD_LSHFT_CAPS):
        case TD(TD_LCTL_STICKY):
        case TD(TD_LALT_STICKY):
            return 200;
        case TD(TD_SMILEY):
            return 500;
        default:
            return TAPPING_TERM;
    }
}

// Dip-Switch controls
void dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
#ifdef AUDIO_ENABLE
            static bool play_sound = false;
#endif
            if (active) {
#ifdef AUDIO_ENABLE
                if (play_sound) {
                    PLAY_SONG(plover_song);
                }
#endif
                layer_on(_ADJUST);
            } else {
#ifdef AUDIO_ENABLE
                if (play_sound) {
                    PLAY_SONG(plover_gb_song);
                }
#endif
                layer_off(_ADJUST);
            }
#ifdef AUDIO_ENABLE
            play_sound = true;
#endif
            break;
        }
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
}

// Runs at every complete matrix scan
void matrix_scan_user(void) {
    // Some code for controlling MIDI output
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
    // Check the shift-state and hold-time for the Irony key
    if (irony_active) {
        if ((get_mods() & MOD_MASK_SHIFT)) {
            irony_shifted = true;
        } else {
            irony_shifted = false;
        }
        if (timer_elapsed(irony_pressed_time) >= IRONY_HOLD_DELAY) {
            if (irony_shifted) {
                send_unicode_string(bang_str);
            } else {
                send_unicode_string(irony_str);
            }
        }
    }

    // Monitor and respond to the current Alt+Tab state
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
    // Monitor and perform leader-key chords
    LEADER_DICTIONARY() {
        did_leader_succeed = leading = false;

        SEQ_ONE_KEY(KC_E) {
            SEND_STRING(SS_LCTL(SS_LSFT("t")));
            did_leader_succeed = true;
        }
        SEQ_ONE_KEY(KC_C) {
            SEND_STRING(SS_LGUI("r") SS_DELAY(250) "calc\n");
            did_leader_succeed = true;
        }
        else SEQ_ONE_KEY(KC_V) {
            SEND_STRING(SS_LCTL("v"));
            did_leader_succeed = true;
        }
        else SEQ_TWO_KEYS(KC_E, KC_D) {
            SEND_STRING(SS_LGUI("r") "cmd\n" SS_LCTL("c"));
            did_leader_succeed = true;
        }
        else SEQ_TWO_KEYS(KC_A, KC_C) {
            SEND_STRING(SS_LCTL("a") SS_LCTL("c"));
            did_leader_succeed = true;
        }
        else SEQ_THREE_KEYS(KC_C, KC_A, KC_T) {
            send_unicode_string("😸");
            did_leader_succeed = true;
        }
        else SEQ_THREE_KEYS(KC_B, KC_A, KC_T) {
            send_unicode_string("🦇");
            did_leader_succeed = true;
        }
        else SEQ_THREE_KEYS(KC_D, KC_O, KC_G) {
            send_unicode_string("🐶");
            did_leader_succeed = true;
        }
        else SEQ_FIVE_KEYS(KC_S, KC_M, KC_I, KC_L, KC_E) {
            send_unicode_string("🙂");
            did_leader_succeed = true;
        }
        else SEQ_FOUR_KEYS(KC_H, KC_A, KC_P, KC_Y) {
            send_unicode_string("🙂");
            did_leader_succeed = true;
        }
        else SEQ_FIVE_KEYS(KC_H, KC_A, KC_P, KC_P, KC_Y) {
            send_unicode_string("🙂");
            did_leader_succeed = true;
        }
        else SEQ_THREE_KEYS(KC_S, KC_A, KC_D) {
            send_unicode_string("🙁");
            did_leader_succeed = true;
        }
        else SEQ_THREE_KEYS(KC_Y, KC_E, KC_S) {
            send_unicode_string("👍");
            did_leader_succeed = true;
        }
        else SEQ_TWO_KEYS(KC_N, KC_O) {
            send_unicode_string("👎");
            did_leader_succeed = true;
        }
        else SEQ_THREE_KEYS(KC_W, KC_O, KC_W) {
            send_unicode_string("🤯");
            did_leader_succeed = true;
        }
        else SEQ_THREE_KEYS(KC_P, KC_O, KC_O) {
            send_unicode_string("💩");
            did_leader_succeed = true;
        }
        else SEQ_FOUR_KEYS(KC_P, KC_O, KC_O, KC_P) {
            send_unicode_string("💩");
            did_leader_succeed = true;
        }
        else SEQ_FOUR_KEYS(KC_B, KC_O, KC_A, KC_T) {
            send_unicode_string("⛵");
            did_leader_succeed = true;
        }
        leader_end();
    }
    // Run the wake-up RGB animation if performing wake-up
    if (do_wake_animation) {
        rgb_wakeup_sequence();
    }
}

// Music mask controls

bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
        case RAISE:
        case LOWER:
            return false;
        default:
            return true;
    }
}

void suspend_power_down_user(void) {
    // Runs during start of system suspend
    print("Going to sleep.");
}

void suspend_wakeup_init_user(void) {
    // Runs during wake from system suspend
}

void keyboard_post_init_user(void) {
    // Print welcome message to console
    printf("Welcome to %s!\n", KEEB_MODEL_NAME);
    // Read the user config from EEPROM
    user_config.raw   = eeconfig_read_user();
    do_wake_animation = user_config.do_wakeup_animation;
    do_wake_audio     = user_config.do_wakeup_audio;
    rgbcon_tracker    = user_config.rgbcon_tracker;

    // Tell the console the status of saved config
    if (user_config.do_wakeup_animation) {
        print("Wake animation enabled.\n");
    } else {
        print("Wake animation disabled.\n");
    }
    if (user_config.do_wakeup_audio) {
        print("Wake music enabled.\n");
    } else {
        print("Wake music disabled.\n");
    }
    switch (user_config.rgbcon_tracker) {
        case 2:
            print("RGB mode: Static White\n");
            break;
        case 3:
            print("RGB mode: Static Cyan\n");
            break;
        case 4:
            print("RGB mode: Breathing Lights\n");
            break;
        case 5:
            print("RGB mode: Rainbow Swirl\n");
            break;
        case 6:
            print("RGB mode: Rainbow Mood\n");
            break;
        default:
            print("RGB mode: Disabled RGB\n");
            break;
    }

    // Enable the LED layers
    rgblight_enable_noeeprom();  // Enables RGB, without saving settings
    rgblight_layers = my_rgb_layers;

    /*
     * Initialize the LED crawl wake animation here
     * To perform it on just the first wake
     */
    wake_rgb_timer = timer_read();
    waking_up      = true;

    // Initialize OLED display
    /*
        if (USING_OLED_DISPLAY) {
            print("Initializing display!\n");
            render_logo();
        }
    */
}

// EEPROM is getting reset!
void eeconfig_init_user(void) {
    user_config.raw                 = 0;
    eeconfig_update_user(user_config.raw);  // Write default value to EEPROM now
}

// Communicate 2-way with host via HID_RAW
#ifdef RAW_ENABLE
void raw_hid_receive(uint8_t* data, uint8_t length) {
    //  Sample code below simply echoes back to the console any data received by the raw_hid process

#    ifdef CONSOLE_ENABLE
    dprint("Received USB data from host system:\n");
    dprintf("%s\n", data);
#    endif
}
#endif
