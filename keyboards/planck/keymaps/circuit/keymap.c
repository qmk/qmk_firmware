// Layout picture at http://www.keyboard-layout-editor.com/#/gists/125febfad6960add078e6f14256539b6

#pragma message "You may need to add LAYOUT_planck_grid to your keymap layers - see default for an example"
#include "planck.h"
#include "action_layer.h"
#ifdef AUDIO_ENABLE
#include "audio.h"
#endif
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _DVORAK 1
#define _LOCKED 2
#define _NUMBER 3
#define _ACTION 4
#define _FUNCTN 5

enum planck_keycodes {
    QWERTY = SAFE_RANGE,
    DVORAK,
    NUMBER,
    ACTION
};

// Key code names
#define SFT_ENT FUNC(0) // Tap for enter, hold for right shift
#define LOCK    FUNC(1)
#define KC_PSTE KC_PASTE

#ifdef TAP_DANCE_ENABLE
#define SFT_CAP TD(0)   // Left shift, double tap for caps
#endif
#ifndef TAP_DANCE_ENABLE
#define SFT_CAP KC_LSFT // Regular left shift
#endif

// Tap Dance Definitions
#ifdef TAP_DANCE_ENABLE
qk_tap_dance_action_t tap_dance_actions[] = {
    [0]  = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS)
};
#endif

// Function definitions
const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_ENT),
    [1] = ACTION_LAYER_TOGGLE(_LOCKED)
};

// Layout definitions
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | BKSP |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |   '  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |*Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  Up  |SftEnt|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl | Alt  | Cmd  | Vol- | ACTN |    Space    | NUMS | Vol+ | Left | Down | Left |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = {
    {KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
    {KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
    {SFT_CAP, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   SFT_ENT},
    {KC_LCTL, KC_LALT, KC_LGUI, KC_VOLD, ACTION,  KC_SPC,  KC_SPC,  NUMBER,  KC_VOLU, KC_LEFT, KC_DOWN, KC_RGHT}
},

/* DVORAK
 * ,-----------------------------------------------------------------------------------.
 * |      |   '  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = {
    {_______, KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    _______},
    {_______, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_Z   },
    {_______, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* LOCK
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      | NULL |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOCKED] = {
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* NUMBERS
 * ,-----------------------------------------------------------------------------------.
 * |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   ~  | NULL | NULL | NULL |   |  |   _  |   +  |   {  |   }  |   ?  |   /  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   `  | NULL | NULL | NULL |   \  |   -  |   =  |   [  |   ]  |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |     NULL    |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMBER] = {
    {_______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______},
    {_______, KC_TILD, XXXXXXX, XXXXXXX, XXXXXXX, KC_PIPE, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_QUES, KC_SLSH},
    {_______, KC_GRV,  XXXXXXX, XXXXXXX, XXXXXXX, KC_BSLS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______, _______},
    {_______, _______, _______, _______, _______, XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______}
},

/* ACTIONS
 * ,-----------------------------------------------------------------------------------.
 * |      |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | NULL | NULL | NULL | NULL | NULL | NULL | NULL | NULL | NULL | NULL | NULL |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CAPS | Undo |  Cut | Copy | Paste| NULL | NULL | NULL | NULL | NULL | PgUp | Enter|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      | Mute |      |     NULL    |      | NULL | Home | PgDn |  End |
 * `-----------------------------------------------------------------------------------'
 */
[_ACTION] = {
    {_______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL },
    {_______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX},
    {KC_CAPS, KC_UNDO, KC_CUT,  KC_COPY, KC_PSTE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, KC_ENT },
    {_______, _______, _______, KC_MUTE, _______, XXXXXXX, XXXXXXX, _______, XXXXXXX, KC_HOME, KC_PGDN, KC_END }
},

/* FUNCTIONS
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  F13 |  F14 |  F15 |  F16 |  F17 |  F18 |  F19 |  F20 |  F21 |  F22 |  F23 |  F24 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | NULL | NULL | NULL | NULL | NULL |QWERTY|DVORAK| NULL | NULL | NULL | NULL | NULL |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Reset| NULL | Lock | NULL |      |     NULL    |      | NULL | NULL | NULL | NULL |
 * `-----------------------------------------------------------------------------------'
 */
[_FUNCTN] = {
    {KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12 },
    {KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24 },
    {XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QWERTY,  DVORAK,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX},
    {RESET,   XXXXXXX, LOCK,    XXXXXXX, _______, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX}
}

};

#ifdef AUDIO_ENABLE
float tone_startup[][2] = SONG(STARTUP_SOUND);
float tone_qwerty[][2] = SONG(QWERTY_SOUND);
float tone_dvorak[][2] = SONG(DVORAK_SOUND);
float music_scale[][2] = SONG(MUSIC_SCALE_SOUND);
float tone_goodbye[][2] = SONG(GOODBYE_SOUND);
#endif


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                if (IS_LAYER_ON(_DVORAK)) {
#ifdef AUDIO_ENABLE
                    PLAY_SONG(tone_qwerty);
#endif
                    layer_off(_DVORAK);
                }
            }
            return false;
            break;
        case DVORAK:
            if (record->event.pressed) {
                if (!IS_LAYER_ON(_DVORAK)) {
#ifdef AUDIO_ENABLE
                    PLAY_SONG(tone_dvorak);
#endif
                    layer_on(_DVORAK);
                }
            }
            return false;
            break;
        case NUMBER:
            if (record->event.pressed) {
                layer_on(_NUMBER);
                update_tri_layer(_NUMBER, _ACTION, _FUNCTN);
            } else {
                layer_off(_NUMBER);
                update_tri_layer(_NUMBER, _ACTION, _FUNCTN);
            }
            return false;
            break;
        case ACTION:
            if (record->event.pressed) {
                layer_on(_ACTION);
                update_tri_layer(_NUMBER, _ACTION, _FUNCTN);
            } else {
                layer_off(_ACTION);
                update_tri_layer(_NUMBER, _ACTION, _FUNCTN);
            }
            return false;
            break;
    }
    return true;
}

void matrix_init_user(void) {
#ifdef AUDIO_ENABLE
    startup_user();
#endif
}

#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
    PLAY_SONG(tone_startup);
}

void shutdown_user()
{
    PLAY_SONG(tone_goodbye);
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}

#endif
