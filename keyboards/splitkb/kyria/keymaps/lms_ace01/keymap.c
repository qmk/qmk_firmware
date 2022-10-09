/* Copyright 2021 Luis Moreno <acevice69@gmail.com>
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
#include "keymap_spanish.h"

// Insert key state definition (Insert/Overwrite Mode)
static bool ins_state = true;

// Git Commands
static const char *sendstring_commands[] = {
    // Config
    "config //global",

    // Create
    "init",
    "clone",

    // Local changes
    "status",
    "diff",
    "add",
    "rm",
    "mv",
    "commit",
    "stash",
    "reset",
    "revert",

    // Branches and Tags
    "branch /b @",
    "switch",
    "checkout",
    "tag",

    // Update & Publish
    "remote",
    "fetch",
    "pull",
    "push",

    // Merge & Rebase
    "merge",
    "rebase",

    // Commit history
    "logg"
};

// Layers definition
enum layers {
    _QWERTY_ES,
    _COLEMAK_ES,
    _SYMBOL,
    _FN_NUMPAD,
    _NAVIGATION,
    _GIT_CMDS,
    _SETTINGS
};

// Encoder Modes definition
#ifdef ENCODER_ENABLE
#define ENC_ALT_MAX_TIME 1250

typedef enum {
    ENC_MODE_CHAR_LINE,
    ENC_MODE_WORD_PAGE,
    ENC_MODE_TABBING,
    ENC_MODE_VOLUME,
    ENC_MODE_LAST
} encoder_mode_t;

static encoder_mode_t enc_mode;

void encoder_cycle_mode(bool up);
#endif

// Tap Dance declarations/definitions
#ifdef TAP_DANCE_ENABLE
#define ACTION_TAP_DANCE_FN_ADVANCED_USER(user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset, user_user_data) \
    { .fn = {user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset}, .user_data = (void *)user_user_data, }

#define MAX_MOD 3  // Max number of modifiers: 0-Base, 1-Shift, 2-Ctrl

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP
} td_state_t;

typedef struct {
    bool       is_press_action;
    td_state_t state;
} td_tap_t;

typedef struct {
    uint16_t keycode;         // Keycode:
                              //  - Tap if keycode != KC_NO
    uint8_t  layer[MAX_MOD];  // Layer with modifiers (0-Base, 1-Shift, 2-Ctrl):
                              //  - Tap if keycode == KC_NO
                              //  - Single Hold: Activate while holding
                              //  - Double Tap: (Un)lock Layer
} td_user_data_t;

enum td_actions {
    TAB,
    ESC,
    SPC,
    ENT,
    LWR,
    RAI
};

static td_tap_t td_tap_state = {
    .is_press_action = true,
    .state           = TD_NONE
};

td_state_t td_current       (qk_tap_dance_state_t *state);
void       td_kc_ly_finished(qk_tap_dance_state_t *state, void *user_data);
void       td_kc_ly_reset   (qk_tap_dance_state_t *state, void *user_data);

qk_tap_dance_action_t tap_dance_actions[] = {
    [TAB] = ACTION_TAP_DANCE_DOUBLE(KC_TAB, KC_CAPS),
    [ESC] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, td_kc_ly_finished, td_kc_ly_reset, \
                                              &((td_user_data_t) { KC_ESC, { _NAVIGATION, _QWERTY_ES, _QWERTY_ES }})),
    [SPC] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, td_kc_ly_finished, td_kc_ly_reset, \
                                              &((td_user_data_t) { KC_SPC, { _SYMBOL    , _QWERTY_ES, _QWERTY_ES }})),
    [ENT] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, td_kc_ly_finished, td_kc_ly_reset, \
                                              &((td_user_data_t) { KC_ENT, { _SYMBOL    , _QWERTY_ES, _QWERTY_ES }})),
    [LWR] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, td_kc_ly_finished, td_kc_ly_reset, \
                                              &((td_user_data_t) {  KC_NO, { _NAVIGATION, _GIT_CMDS , _QWERTY_ES }})),
    [RAI] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, td_kc_ly_finished, td_kc_ly_reset, \
                                              &((td_user_data_t) {  KC_NO, { _FN_NUMPAD , _GIT_CMDS , _QWERTY_ES }}))
};
#endif

// Keycode definitions
enum custom_keycodes {
    CK_QUOT = SAFE_RANGE,  // Single/Double quote
    CK_BSDI,               // Backspace/Delete/Insert
    CK_ENCM,               // Encoder Mode (-)
    CK_ENCP,               // Encoder Mode (+)
    CK_LYDF,               // Activate Default Layer
    G_CONF,                // Git Commands
    G_INIT,
    G_CLONE,
    G_STAT,
    G_DIFF,
    G_ADD,
    G_RM,
    G_MV,
    G_COMM,
    G_STASH,
    G_RESET,
    G_REVER,
    G_BRANC,
    G_SWTCH,
    G_CHECK,
    G_TAG,
    G_REMOT,
    G_FETCH,
    G_PULL,
    G_PUSH,
    G_MERGE,
    G_REBAS,
    G_LOG
};

#define LY_QWES  DF(_QWERTY_ES)
#define LY_CLES  DF(_COLEMAK_ES)

#ifdef TAP_DANCE_ENABLE
    #define TD_TBCP  TD(TAB)
    #define TD_ESSY  TD(ESC)
    #define TD_SPSY  TD(SPC)
    #define TD_ENSY  TD(ENT)
    #define TD_LOWR  TD(LWR)
    #define TD_RAIS  TD(RAI)
#else
    #define TD_TBCP  MT(MOD_LSFT, KC_TAB)
    #define TD_ESSY  LT(_SYMBOL , KC_ESC)
    #define TD_SPSY  KC_SPC
    #define TD_ENSY  KC_ENT
    #define TD_LOWR  TT(_NAVIGATION)
    #define TD_RAIS  TT(_SYMBOL)
#endif

#define MO_LSFT OSM(MOD_LSFT)
#define MO_LCTL OSM(MOD_LCTL)
#define MO_LALT OSM(MOD_LALT)

#define MT_RGUI  MT(MOD_RGUI, KC_LEFT)
#define MT_RALT  MT(MOD_RALT, KC_DOWN)
#define MT_RCTL  MT(MOD_RCTL, KC_UP)
#define MT_RSFT  MT(MOD_RSFT, KC_RGHT)

// Keymap definitions
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// clang-format off
/*
 * Basic characters (QWERTY ES)
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |Esc/LNav|   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |BS/Dl/In|
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Tab/Caps|   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  |   Ñ  |   ´ ¨  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |EncMode-|   Z  |   X  |   C  |   V  |   B  | LGit |      |  |      | LGit |   N  |   M  |  , ; |  . : |  - _ |EncMode+|
 * `-------------------------------------------| LNav | Space|  | Enter|LFnNum|-------------------------------------------'
 *                        +--------------------+------+   /  |  |   /  +------+--------------------+
 *                        | Shift| Ctrl | Alt  | GUI  | LSym |  | LSym | GUI  | AltGr| Ctrl | Shift|
 *                        |      |      |      |      |      |  |      |  <-  |   v  |   ^  |  ->  |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY_ES] = LAYOUT(
      TD_ESSY,    ES_Q,    ES_W,    ES_E,    ES_R,    ES_T,                                        ES_Y,    ES_U,    ES_I,    ES_O,    ES_P, CK_BSDI,
      TD_TBCP,    ES_A,    ES_S,    ES_D,    ES_F,    ES_G,                                        ES_H,    ES_J,    ES_K,    ES_L, ES_NTIL, ES_ACUT,
      CK_ENCM,    ES_Z,    ES_X,    ES_C,    ES_V,    ES_B, TD_LOWR, XXXXXXX, XXXXXXX, TD_RAIS,    ES_N,    ES_M, ES_COMM,  ES_DOT, ES_MINS, CK_ENCP,
                                 MO_LSFT, MO_LCTL, MO_LALT, KC_LGUI, TD_SPSY, TD_ENSY, MT_RGUI, MT_RALT, MT_RCTL, MT_RSFT
    ),
/*
 * Basic characters (COLEMAK ES)
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |Esc/LNav|   Q  |   W  |   F  |   P  |   G  |                              |   J  |   L  |   U  |   Y  |   Ñ  |BS/Dl/In|
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Tab/Caps|   A  |   R  |   S  |   T  |   D  |                              |   H  |   N  |   E  |   I  |   O  |   ´ ¨  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |EncMode-|   Z  |   X  |   C  |   V  |   B  | LGit |      |  |      | LGit |   K  |   M  |  , ; |  . : |  - _ |EncMode+|
 * `-------------------------------------------| LNav | Space|  | Enter|LFnNum|-------------------------------------------'
 *                        +--------------------+------+   /  |  |   /  +------+--------------------+
 *                        | Shift| Ctrl | Alt  | GUI  | LSym |  | LSym | GUI  | AltGr| Ctrl | Shift|
 *                        |      |      |      |      |      |  |      |  <-  |   v  |   ^  |  ->  |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_COLEMAK_ES] = LAYOUT(
      TD_ESSY,    ES_Q,    ES_W,    ES_F,    ES_P,    ES_G,                                        ES_J,    ES_L,    ES_U,    ES_Y, ES_NTIL, CK_BSDI,
      TD_TBCP,    ES_A,    ES_R,    ES_S,    ES_T,    ES_D,                                        ES_H,    ES_N,    ES_E,    ES_I,    ES_O, ES_ACUT,
      CK_ENCM,    ES_Z,    ES_X,    ES_C,    ES_V,    ES_B, TD_LOWR, XXXXXXX, XXXXXXX, TD_RAIS,    ES_K,    ES_M, ES_COMM,  ES_DOT, ES_MINS, CK_ENCP,
                                 MO_LSFT, MO_LCTL, MO_LALT, KC_LGUI, TD_SPSY, TD_ENSY, MT_RGUI, MT_RALT, MT_RCTL, MT_RSFT
    ),
/*
 * Symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  1 ! |  2 " |  3 · |  4 $ |  5 % |                              |  6 & |  7 / |  8 ( |  9 ) |  0 = |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  ¡ ¿ |  ' " |  º ª |   \  |  | ¡ |                              |  ~ $ |  + * |  - _ |   /  |  ' ? |  ` ^   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  @ ⅛ |   {  |   (  |  [ ° |  < > |      |      |  |      |      |   >  |  ] ¯ |   )  |  } ˘ |  # £ |        |
 * `----------------------+------+------+------+------+      |  |      +------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYMBOL] = LAYOUT(
      _______,    ES_1,    ES_2,    ES_3,    ES_4,    ES_5,                                        ES_6,    ES_7,    ES_8,    ES_9,    ES_0, _______,
      _______, ES_IEXL, CK_QUOT, ES_MORD, ES_BSLS, ES_PIPE,                                     ES_TILD, ES_PLUS, ES_MINS, ES_SLSH, ES_QUOT,  ES_GRV,
      _______,   ES_AT, ES_LCBR, ES_LPRN, ES_LBRC, ES_LABK, _______, XXXXXXX, XXXXXXX, _______, ES_RABK, ES_RBRC, ES_RPRN, ES_RCBR, ES_HASH, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * Function keys, NumPad keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |      |                              |  , ; |  7 / |  8 ( |  9 ) |   *  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  F5  |  F6  |  F7  |  F8  |      |                              |  . : |  4 $ |  5 % |  6 & |  - _ |  + *   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  F9  |  F10 |  F11 |  F12 |      |      |      |  |      |      |  0 = |  1 ! |  2 " |  3 · |   /  |        |
 * `----------------------+------+------+------+------+      |  |      +------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_FN_NUMPAD] = LAYOUT(
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4, XXXXXXX,                                     ES_COMM,    ES_7,    ES_8,    ES_9, ES_ASTR, _______,
      _______,   KC_F5,   KC_F6,   KC_F7,   KC_F8, XXXXXXX,                                      ES_DOT,    ES_4,    ES_5,    ES_6, ES_MINS, ES_PLUS,
      _______,   KC_F9,  KC_F10,  KC_F11,  KC_F12, XXXXXXX, _______, XXXXXXX, XXXXXXX, _______,    ES_0,    ES_1,    ES_2,    ES_3, ES_SLSH, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * Navigation (Mouse deactivated for space saving)
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      | MBt1 | MUp  | MBt2 |      |                              | PgUp | Home |  Up  |  End | PgUp |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | Menu | MLeft| MDown|MRight|      |                              | PgDn | Left | Down | Right| PgDn |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |PrtScr|ScrLck| Pause|      |        |
 * `----------------------+------+------+------+------+      |  |      +------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAVIGATION] = LAYOUT(
      _______, XXXXXXX, KC_BTN1, KC_MS_U, KC_BTN2, XXXXXXX,                                     KC_PGUP, KC_HOME,   KC_UP,  KC_END, KC_PGUP, _______,
      _______,  KC_APP, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX,                                     KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______,
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, _______, XXXXXXX, KC_PSCR, KC_SLCK, KC_PAUS, XXXXXXX, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * Git Commands
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |Config|      |      | Init |      |                              |      | Clone|      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | Diff | Add  |  Rm  |  Mv  |      |                              |Remote| Fetch| Pull | Push | Merge| Rebase |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |Commit| Stash| Reset|Revert|Status|      |      |  |      |      |  Log |Branch|Switch|ChkOut|  Tag |        |
 * `----------------------+------+------+------+------+      |  |      +------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_GIT_CMDS] = LAYOUT(
      _______,  G_CONF, XXXXXXX, XXXXXXX,  G_INIT, XXXXXXX,                                     XXXXXXX, G_CLONE, XXXXXXX, XXXXXXX, XXXXXXX, _______,
      _______,  G_DIFF,   G_ADD,    G_RM,    G_MV, XXXXXXX,                                     G_REMOT, G_FETCH,  G_PULL,  G_PUSH, G_MERGE, G_REBAS,
      _______,  G_COMM, G_STASH, G_RESET, G_REVER,  G_STAT, _______, XXXXXXX, XXXXXXX, _______,   G_LOG, G_BRANC, G_SWTCH, G_CHECK,   G_TAG, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * Settings (Default Layer, RGB, Media)
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |QWE_ES|CLM_ES|      |      |      |                              |      |      | Vol+ |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | TOG  | HUE+ | SAT+ | VAL+ | MOD  |                              | Mute | Prev | Play | Next |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |  LDef  |      | HUE- | SAT- | VAL- | RMOD |      |      |  |      |      |      |      | Vol- |      |      |  LDef  |
 * `----------------------+------+------+------+------+      |  |      +------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SETTINGS] = LAYOUT(
      _______, LY_QWES, LY_CLES, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, KC_VOLU, XXXXXXX, XXXXXXX, _______,
      _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_MOD,                                     KC_MUTE, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
      CK_LYDF, XXXXXXX, RGB_HUD, RGB_SAD, RGB_VAD, RGB_RMOD,_______, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, KC_VOLD, XXXXXXX, XXXXXXX, CK_LYDF,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+      |  |      +------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};
// clang-format on

/*
 * INITIALIZING FUNCTIONS
 */
void matrix_init_user(void) {
#ifdef ENCODER_ENABLE
    enc_mode = ENC_MODE_CHAR_LINE;
#endif
}

/*
 * LAYER FUNCTIONS
 */
layer_state_t layer_state_set_user(layer_state_t state) {
    // Activate Settings layer when both Symbol and Navigation layers are on
    return update_tri_layer_state(state, _SYMBOL, _NAVIGATION, _SETTINGS);
}

/*
 * MACRO FUNCTIONS
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Get current modifier status (Normal and One Shot)
    uint8_t mod_state = get_mods();
    uint8_t osm_state = get_oneshot_mods();

    // Process keycode
    switch (keycode) {
        case CK_QUOT:  // Single/Double Quote
            if (record->event.pressed) {
                if ((mod_state | osm_state) & MOD_MASK_SHIFT) {
                    register_code(ES_2);       // Shift(2)     -> "
                } else {
                    register_code(ES_QUOT);    // Single Quote -> '
                }
            } else {
                if ((mod_state | osm_state) & MOD_MASK_SHIFT) {
                    unregister_code(ES_2);     // Shift(2)     -> "
                } else {
                    unregister_code(ES_QUOT);  // Single Quote -> '
                }
            }

            return false;
            break;
        case CK_BSDI: {  // Backspace/Delete/Insert
            static bool delkey_registered = false;

            if (record->event.pressed) {
                // Ctrl   -> Insert/Overwrite Mode
                // Shift  -> Delete
                // Normal -> Backspace
                if ((mod_state | osm_state) & MOD_MASK_CTRL) {
                    del_mods(MOD_MASK_CTRL);
                    del_oneshot_mods(MOD_MASK_CTRL);

                    tap_code(KC_INS);

                    set_mods(mod_state);
                    set_oneshot_mods(osm_state);

                    ins_state = !ins_state;
                } else if ((mod_state | osm_state) & MOD_MASK_SHIFT) {
                    delkey_registered = true;

                    del_mods(MOD_MASK_SHIFT);
                    del_oneshot_mods(MOD_MASK_SHIFT);

                    register_code(KC_DEL);

                    set_mods(mod_state);
                    set_oneshot_mods(osm_state);
                } else {
                    register_code(KC_BSPC);
                }
            } else {
                // Unregister keycode sent after the release of CK_BSDI
                if (delkey_registered) {
                    unregister_code(KC_DEL);
                    delkey_registered = false;
                } else {
                    unregister_code(KC_BSPC);
                }
            }

            return false;
        }
            break;
        case CK_LYDF:  // De-activate all layers and activate Default layer
            layer_move(get_highest_layer(default_layer_state));

            return false;
            break;
        case G_CONF ... G_LOG:
            if (record->event.pressed) {
                del_mods(MOD_MASK_SHIFT);
                del_oneshot_mods(MOD_MASK_SHIFT);

                SEND_STRING("git ");
                send_string(sendstring_commands[keycode - G_CONF]);

                set_mods(mod_state);
                set_oneshot_mods(osm_state);
            }

            break;
#ifdef ENCODER_ENABLE
        case CK_ENCM:  // Encoder Mode (-)
            if (record->event.pressed) {
                encoder_cycle_mode(false);
            }

            break;
        case CK_ENCP:  // Encoder Mode (+)
            if (record->event.pressed) {
                encoder_cycle_mode(true);
            }

            break;
#endif
    }

    return true;
};

/*
 * TAP DANCE FUNCTIONS
 */
#ifdef TAP_DANCE_ENABLE
td_state_t td_current(qk_tap_dance_state_t *state) {
    switch (state->count) {
        case 1:
            return ((!state->pressed) ? TD_SINGLE_TAP : TD_SINGLE_HOLD);
        case 2:
            return TD_DOUBLE_TAP;
        default:
            return TD_UNKNOWN;
    }
}

void td_kc_ly_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_tap_state.state  = td_current(state);
    uint16_t  keycode   = ((td_user_data_t *)user_data)->keycode;
    uint8_t  *layer_arr = ((td_user_data_t *)user_data)->layer;
    uint8_t   layer_sel = *(layer_arr + 0);

    // Get current modifier status (Normal and One Shot) and select layer
    uint8_t mod_state = get_mods();
    uint8_t osm_state = get_oneshot_mods();

    if ((mod_state | osm_state) & MOD_MASK_SHIFT) {
        if (*(layer_arr + 1) > _QWERTY_ES) {
            layer_sel = *(layer_arr + 1);
        }
    }

    if ((mod_state | osm_state) & MOD_MASK_CTRL) {
        if (*(layer_arr + 2) > _QWERTY_ES) {
            layer_sel = *(layer_arr + 2);
        }
    }

    switch (td_tap_state.state) {
        case TD_NONE:
        case TD_UNKNOWN:
            break;
        case TD_SINGLE_TAP:
            // Send keycode if available
            // Otherwise, Lock Layer (Base/Shift/Ctrl) and Unlock rest of selectable layers
            if (keycode != KC_NO) {
                tap_code(keycode);
            } else {
                uint8_t layer_aux;

                for (layer_aux = _GIT_CMDS; layer_aux >= _SYMBOL; layer_aux--) {
                    if ((layer_aux == layer_sel) && (!layer_state_is(layer_aux))) {
                        layer_on(layer_aux);
                    } else {
                        layer_off(layer_aux);
                    }
                }
            }

            break;
        case TD_SINGLE_HOLD:
            // Lock Layer (Base/Shift/Ctrl) while Single Hold on the way
            layer_on(layer_sel);
            break;
        case TD_DOUBLE_TAP:
            // (Un)lock Layer (Base/Shift/Ctrl)
            if (layer_state_is(layer_sel)) {
                layer_off(layer_sel);
            } else {
                layer_on(layer_sel);
            }

            break;
    }
}

void td_kc_ly_reset(qk_tap_dance_state_t *state, void *user_data) {
    uint8_t *layer_arr = ((td_user_data_t *)user_data)->layer;

    if (td_tap_state.state == TD_SINGLE_HOLD) {
        // Unlock any Layer (Base/Shift/Ctrl) when Single Hold finalizes
        uint8_t i;
        uint8_t layer_aux;

        for (i = 0; i < MAX_MOD; i++) {
            layer_aux = *(layer_arr + i);

            if ((layer_aux > _QWERTY_ES)) {
                layer_off(layer_aux);
            }
        }
    }

    td_tap_state.state = TD_NONE;
}
#endif

/*
 * OLED FUNCTIONS
 */
#ifdef OLED_DRIVER_ENABLE
static void render_kyria_logo(void) {
    static const char PROGMEM kyria_logo[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xe0, 0xf0, 0x78, 0x38, 0x1c, 0x1e, 0x0e,
        0x8e, 0x86, 0x86, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x86,
        0x86, 0x8e, 0x0e, 0x1e, 0x1c, 0x38, 0x78, 0xf0, 0xe0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0xe0, 0xf0, 0xfc, 0x3e, 0x0f, 0x07, 0x83, 0xe1, 0xf0, 0xf8, 0xbc, 0x9e, 0x8f, 0x87,
        0x87, 0x83, 0x81, 0x81, 0xe0, 0x78, 0x1f, 0x07, 0xff, 0xff, 0x07, 0x1f, 0x78, 0xe0, 0x81, 0x81,
        0x83, 0x87, 0x87, 0x8f, 0x9e, 0xbc, 0xf8, 0xf0, 0xe1, 0x83, 0x07, 0x0f, 0x3e, 0xfc, 0xf0, 0xe0,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0xfc, 0xff, 0x03, 0x00, 0x00, 0x00, 0xfc, 0xff, 0x07, 0x07, 0x3f, 0x73, 0xc7, 0x8f, 0x8d,
        0x89, 0x99, 0x99, 0xb1, 0xf7, 0xee, 0xf8, 0xf0, 0xff, 0xff, 0xf0, 0xf8, 0xee, 0xf7, 0xb1, 0x99,
        0x99, 0x89, 0x8d, 0x8f, 0xc7, 0x73, 0x3f, 0x07, 0x07, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xff,
        0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x3f, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xe0, 0xe0, 0xfc, 0xce, 0xe3, 0xf1, 0xb1,
        0x91, 0x99, 0x99, 0x8d, 0xef, 0x77, 0x1f, 0x0f, 0xff, 0xff, 0x0f, 0x1f, 0x77, 0xef, 0x8d, 0x99,
        0x99, 0x91, 0xb1, 0xf1, 0xe3, 0xce, 0xfc, 0xe0, 0xe0, 0xff, 0x3f, 0x00, 0x00, 0x00, 0xc0, 0xff,
        0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x07, 0x0f, 0x3f, 0x7c, 0xf0, 0xe0, 0xc1, 0x87, 0x0f, 0x1f, 0x3d, 0x79, 0xf1, 0xe1,
        0xe1, 0xc1, 0x81, 0x81, 0x07, 0x1e, 0xf8, 0xe0, 0xff, 0xff, 0xe0, 0xf8, 0x1e, 0x07, 0x81, 0x81,
        0xc1, 0xe1, 0xe1, 0xf1, 0x79, 0x3d, 0x1f, 0x0f, 0x87, 0xc1, 0xe0, 0xf0, 0x7c, 0x3f, 0x0f, 0x07,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x07, 0x0f, 0x1e, 0x1c, 0x38, 0x78, 0x70,
        0x71, 0x61, 0x61, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x61,
        0x61, 0x71, 0x70, 0x78, 0x38, 0x1c, 0x1e, 0x0f, 0x07, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0xc0, 0xfe, 0xfe, 0xfe, 0xc6, 0xe0, 0xf0, 0x70, 0x30, 0x10, 0x00, 0x70,
        0xf0, 0xf0, 0x80, 0x00, 0xc0, 0xf0, 0xf0, 0x70, 0x10, 0xc0, 0xf0, 0xf0, 0xf0, 0x70, 0x30, 0x30,
        0x30, 0xc0, 0xf6, 0xf6, 0xf6, 0x06, 0x00, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xf0, 0xf0, 0xe0, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x10, 0x1f, 0x1f, 0x1f, 0x03, 0x0f, 0x1f, 0x1e, 0x18, 0x10, 0x00, 0xc0, 0xc0,
        0xe7, 0xff, 0x7f, 0x3f, 0x0f, 0x03, 0x01, 0x00, 0x18, 0x1f, 0x1f, 0x1f, 0x00, 0x00, 0x00, 0x00,
        0x18, 0x1f, 0x1f, 0x1f, 0x00, 0x0e, 0x1f, 0x1f, 0x1f, 0x19, 0x0d, 0x1f, 0x1f, 0x1f, 0x03, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
}

static void render_qmk_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0
    };

    oled_write_P(qmk_logo, false);
}

static void render_status(void) {
    // Get current modifier status (Normal and One Shot)
    uint8_t mod_state = get_mods();
    uint8_t osm_state = get_oneshot_mods();
    uint8_t osl_state = get_oneshot_locked_mods();
    bool    caps_lock = host_keyboard_led_state().caps_lock;

    // QMK Logo
    render_qmk_logo();

#ifdef ENCODER_ENABLE
    // Host Keyboard Encoder Mode
    switch (enc_mode) {
        case ENC_MODE_CHAR_LINE:
            oled_write_P(PSTR("ENC \020 CHAR/LINE\n"), false);
            break;
        case ENC_MODE_WORD_PAGE:
            oled_write_P(PSTR("ENC \020 WORD/PAGE\n"), false);
            break;
        case ENC_MODE_TABBING:
            oled_write_P(PSTR("ENC \020 TABBING\n"),   false);
            break;
        case ENC_MODE_VOLUME:
        case ENC_MODE_LAST:
            oled_write_P(PSTR("ENC \020 VOLUME\n"),    false);
            break;
    }
#else
    oled_write_P(PSTR("\n"), false);
#endif

    // Host Keyboard Layer Status
    oled_write_P(PSTR("\n"), false);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY_ES:
            oled_write_P(PSTR("L00 \020 QWERTY (ES)\n"),  false);
            break;
        case _COLEMAK_ES:
            oled_write_P(PSTR("L00 \020 COLEMAK (ES)\n"), false);
            break;
        case _SYMBOL:
            oled_write_P(PSTR("L01 \020 SYMBOLS\n"),      false);
            break;
        case _FN_NUMPAD:
            oled_write_P(PSTR("L02 \020 FN / NUMPAD\n"),  false);
            break;
        case _NAVIGATION:
            oled_write_P(PSTR("L03 \020 NAVIGATION\n"),   false);
            break;
        case _GIT_CMDS:
            oled_write_P(PSTR("L04 \020 GIT COMMANDS\n"), false);
            break;
        case _SETTINGS:
            oled_write_P(PSTR("L05 \020 SETTINGS\n"),     false);
            break;
    }

    // Host Keyboard Locked Modifiers Status
    oled_write_P((osl_state & MOD_MASK_SHIFT) ? PSTR("LCK ")  : PSTR("    ") , false);
    oled_write_P((osl_state & MOD_MASK_CTRL)  ? PSTR("LCK ")  : PSTR("    ") , false);
    oled_write_P((osl_state & MOD_MASK_ALT)   ? PSTR("LCK ")  : PSTR("    ") , false);
    oled_write_P(                                               PSTR("    ") , false);
    oled_write_P((caps_lock)                  ? PSTR(" CAPS") : PSTR("     "), false);

    // Host Keyboard Modifiers Status
    oled_write_P(((mod_state | osm_state) & MOD_MASK_SHIFT) ? PSTR("SHF ")  : PSTR("    ") , false);
    oled_write_P(((mod_state | osm_state) & MOD_MASK_CTRL)  ? PSTR("CTR ")  : PSTR("    ") , false);
    oled_write_P(((mod_state | osm_state) & MOD_MASK_ALT)   ? PSTR("ALT ")  : PSTR("    ") , false);
    oled_write_P(((mod_state | osm_state) & MOD_MASK_GUI)   ? PSTR("GUI ")  : PSTR("    ") , false);
    oled_write_P((ins_state)                                ? PSTR("  INS") : PSTR("  OWR"), false);
}

static void render_settings(void) {
#ifdef RGBLIGHT_ENABLE
    char rgb_str[4];

    oled_write_P(PSTR("\n\n"), false);

    oled_write_P(PSTR("\020H: "), false);
    itoa(rgblight_get_hue(), rgb_str, 10);
    oled_write_ln(rgb_str, false);

    oled_write_P(PSTR("\020S: "), false);
    itoa(rgblight_get_sat(), rgb_str, 10);
    oled_write_ln(rgb_str, false);

    oled_write_P(PSTR("\020V: "), false);
    itoa(rgblight_get_val(), rgb_str, 10);
    oled_write_ln(rgb_str, false);
#else
    oled_write_P(PSTR("\n\n\n\n\n"), false);
#endif

    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY_ES:
            oled_write_ln_P(PSTR("        \020QWERTY (ES)") , false);
            break;
        case _COLEMAK_ES:
            oled_write_P   (PSTR("        \020COLEMAK (ES)"), false);
            break;
    }

#ifdef RGBLIGHT_ENABLE
    oled_write_ln_P(PSTR("  RGB      DEFAULT"), false);
    oled_write_ln_P(PSTR("SETTINGS    LAYER "), false);
#else
    oled_write_ln_P(PSTR("           DEFAULT"), false);
    oled_write_ln_P(PSTR("            LAYER "), false);
#endif
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

void oled_task_user(void) {
    if (is_keyboard_master()) {  // Main screen: Renders keyboard state (layer, modifiers) / RGB settings
        if (get_highest_layer(layer_state) != _SETTINGS) {
            render_status();
        } else {
            render_settings();
        }
    } else {                     // Auxiliar screen: Renders Kyria logo with scroll
        render_kyria_logo();
        oled_scroll_right();
    }
}
#endif

/*
 * ENCODER FUNCTIONS
 */
#ifdef ENCODER_ENABLE
void encoder_cycle_mode(bool up) {
    if (enc_mode == 0 && !up) {
        enc_mode = ENC_MODE_LAST - 1;
    } else {
        enc_mode = (enc_mode + (up ? +1 : -1)) % ENC_MODE_LAST;
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    // Select encoder mode
    switch (enc_mode) {
        case ENC_MODE_CHAR_LINE:
            // Left Encoder: Character Left/Right. Right Encoder: Line Up/Down.
            tap_code(!clockwise ? (index == 0 ? KC_LEFT : KC_UP): (index == 0 ? KC_RGHT : KC_DOWN));
            break;
        case ENC_MODE_WORD_PAGE:
            // Left Encoder: Word Left/Right. Right Encoder: Page Up/Down.
            tap_code16(!clockwise ? (index == 0 ? C(KC_LEFT) : KC_PGUP): (index == 0 ? C(KC_RGHT) : KC_PGDN));
            break;
        case ENC_MODE_TABBING:
            // Left Encoder: Navigation Tabbing. Right Encoder: Editor Tabbing.
            tap_code16(!clockwise ? (index == 0 ? S(C(KC_TAB)) : C(KC_PGUP)): (index == 0 ? C(KC_TAB) : C(KC_PGDN)));
            break;
        case ENC_MODE_VOLUME:
        case ENC_MODE_LAST:
            // Volume control
            tap_code(clockwise ? KC_VOLU : KC_VOLD);
            break;
    }

    return true;
}
#endif
