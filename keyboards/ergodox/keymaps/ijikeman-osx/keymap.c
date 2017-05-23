#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"


#define BASE 0 // default layer
#define RAIS 1 // raise layer
#define LOWR 2 // lower layer
#define SHIF 3 // shitit layer
#define BA40 4 // 40% basic keys
#define LO40 5 // 40% Lower keys
#define RA40 6 // 40% Raise keys

#define MACRO_SHIFTIT_MOVE         10
#define MACRO_SHIFTIT_LUP         11
#define MACRO_SHIFTIT_LDOWN         12
#define MACRO_SHIFTIT_RUP         13
#define MACRO_SHIFTIT_RDOWN         14
#define MACRO_SHIFTIT_LEFT         15
#define MACRO_SHIFTIT_RIGHT         16
#define MACRO_SHIFTIT_UP         17
#define MACRO_SHIFTIT_DOWN         18
#define MACRO_SHIFTIT_FULL         19
#define MACRO_ZERO_ZERO           20

#define MACRO_TMUX_ESC        30
#define MACRO_TMUX_LANG        31
#define MACRO_TMUX_BRC         32
#define MACRO_TMUX_MINUS         33

#define M_SH_LU   M(MACRO_SHIFTIT_LUP)
#define M_SH_LD   M(MACRO_SHIFTIT_LDOWN)
#define M_SH_RU   M(MACRO_SHIFTIT_RUP)
#define M_SH_RD   M(MACRO_SHIFTIT_RDOWN)
#define M_SH_L   M(MACRO_SHIFTIT_LEFT)
#define M_SH_R   M(MACRO_SHIFTIT_RIGHT)
#define M_SH_U   M(MACRO_SHIFTIT_UP)
#define M_SH_D   M(MACRO_SHIFTIT_DOWN)
#define M_SH_FL   M(MACRO_SHIFTIT_FULL)
#define M_SH_MV   M(MACRO_SHIFTIT_MOVE)
#define M_TESC   M(MACRO_TMUX_ESC)
#define M_TLANG   M(MACRO_TMUX_LANG)
#define M_BRC   M(MACRO_TMUX_BRC)
#define M_MINUS   M(MACRO_TMUX_MINUS)
#define M_00   M(MACRO_ZERO_ZERO)

#define PUSH_TIME 100

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | `~     |   1! |   2@ |   3# |   4$ |   5% |      |           |      |   6^  |   7& |   8* |   9( |   0) | -_(=+)|
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  | [{ ]}  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LCtrl  |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |  ;:   | Enter |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,< |   .> |   /? |   '"   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |  Esc |LANG2 | Alt  |  Cmd |LOWER |                           |RAISE |  \|  |      |LANG1 |      |
 *   `----------------------------------'                            `--------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 | Spc  | SHFIT|----- |       |------|        | BS   |
 *                                 |      |      | RESET|       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
        KC_GRV,         KC_1,         KC_2,       KC_3,       KC_4,       KC_5,     KC_NO,
        KC_TAB,         KC_Q,         KC_W,       KC_E,       KC_R,       KC_T,     KC_NO,
        KC_LCTL,        KC_A,         KC_S,       KC_D,       KC_F,       KC_G,
        KC_LSFT,        KC_Z,         KC_X,       KC_C,       KC_V,       KC_B,     KC_NO,
        KC_ESC,         KC_LANG2,        KC_LALT,    KC_LGUI, LT(2,KC_NO),
                                                  KC_NO,      KC_NO,
                                                              KC_NO,
                                 KC_SPC,     LT(3,KC_NO),     RESET,

        // right hand
        KC_NO,        KC_6,         KC_7,       KC_8,       KC_9,        KC_0,      M_MINUS,
        KC_NO,        KC_Y,         KC_U,       KC_I,       KC_O,        KC_P,      M_BRC,
                      KC_H,         KC_J,       KC_K,       KC_L,        KC_SCLN,   KC_ENT,
        KC_NO,        KC_N,         KC_M,       KC_COMM,    KC_DOT,      KC_SLSH,   KC_QUOT,
        LT(1,KC_NO),  KC_BSLS,      KC_NO,      KC_LANG1,      KC_NO,
        KC_NO,        KC_NO,
        KC_NO,
        TG(4),        KC_NO, KC_BSPC
    ),

/* Keymap 1: Raise layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | `~     |   1! |   2@ |   3# |   4$ |   5% |      |           |      |  6^  |   7& |   8* |   9( |   0) | -_(=+) |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                         |      |      |      |      |      |
 *   `----------------------------------'                         `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 |      |      |----- |       |------|        |      |
 *                                 |      |      |      |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */
// RAISE LAYER
[RAIS] = KEYMAP(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,KC_TRNS, 
       KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,     KC_5,   KC_TRNS, 
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, 
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,KC_TRNS, 
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,     KC_TRNS,    KC_TRNS,
       KC_TRNS,   KC_6,      KC_7,      KC_8,      KC_9,        KC_0,       M_MINUS,
                  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,     KC_TRNS,    KC_TRNS,
       KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,     KC_TRNS,    KC_TRNS,
                             KC_TRNS,   KC_TRNS,   KC_TRNS,     KC_TRNS,    KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),

/* Keymap 2: Lower Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |  F1  |  F2  |  F3  |  F4  |  F5  | F6   |           |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |   F12  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 *  |        |      | BTN1 | MsUp | BTN2 |      |      |           |      |      | UNDO |      | REDO |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 *  |        |      |MsLeft|MsDown|MsRght|      |------|           |------| LEFT | DOWN | UP   |RIGHT |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 *  |        |      |WheelU|      |WheelD|      |      |           |      |      | CP   | CUT  | PST  |      |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |      |      |      |      |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// LOWER LAYER
[LOWR] = KEYMAP(
       // left hand
       KC_TRNS,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,
       KC_TRNS,   KC_NO,    KC_BTN1,  KC_MS_U,  KC_BTN2,  KC_NO,    KC_TRNS,
       KC_TRNS,   KC_NO,    KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_NO,
       KC_TRNS,   KC_NO,    KC_WH_D,  KC_NO,    KC_WH_U,  KC_NO,    KC_TRNS,
       KC_TRNS,   KC_NO,    KC_TRNS,  KC_TRNS,    KC_TRNS,
                                      KC_TRNS,  KC_TRNS,
                                                KC_TRNS,
                             KC_TRNS, KC_TRNS,  KC_TRNS,
       // right hand
       KC_F6,     KC_F7,     KC_F8,     KC_F9,      KC_F10,      KC_F11,   KC_F12,
       KC_TRNS,   KC_NO,     LGUI(KC_Z),KC_NO,     LGUI(KC_Y),   KC_NO,    KC_TRNS,
                  KC_LEFT,   KC_DOWN,   KC_UP,      KC_RIGHT,    KC_NO,    KC_TRNS,
       KC_TRNS,   KC_NO,     LGUI(KC_C),LGUI(KC_X),LGUI(KC_V),   KC_NO,    KC_TRNS,
                  KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,     KC_TRNS,
       KC_TRNS,   KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_DELETE
),

// SHIFTIT LAYER
[SHIF] = KEYMAP(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,
       KC_TRNS, KC_TRNS, M_SH_LU, M_SH_U, M_SH_RU, KC_TRNS,KC_TRNS,
       KC_TRNS, KC_TRNS, M_SH_L, M_SH_FL, M_SH_R,  KC_TRNS,
       KC_TRNS, KC_TRNS, M_SH_LD, M_SH_D, M_SH_RD, M_SH_MV,KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,
                KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,
                         KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),

/* Keymap 0: 40% Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | `~     |   1! |   2@ |   3# |   4$ |   5% |  6^  |           |  6^  |   7& |   8* |   9( |   0) |   -_ |   =+   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  | [{ ]}  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LCtrl  |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |  ;:   | Enter |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,< |   .> |   /? |   '"   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |  Esc | LANG2| Alt  |  Cmd | Spc  |                         |  BS  |  \|  |      |      |LANG1 |      |
 *   `----------------------------------'                         `----------------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | PGDN | PGUP |       | LEFT | RIGHT|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | UP   |        |      |
 *                                 | Fn(1)|Fn(2) |-----|        |------|  Fn(3) | LANG |
 *                                 |      |      | End  |       | DOWN |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BA40] = KEYMAP(  // layer 3 : default
        KC_NO,          KC_NO,        KC_NO,      KC_NO,      KC_NO,      KC_NO,    KC_NO,
        KC_TAB,         KC_Q,         KC_W,       KC_E,       KC_R,       KC_T,     KC_NO,
        KC_LCTL,        KC_A,         KC_S,       KC_D,       KC_F,       KC_G,
        KC_LSFT,        KC_Z,         KC_X,       KC_C,       KC_V,       KC_B,     KC_NO,
        KC_ESC,         KC_LANG2,        KC_LALT,    KC_LGUI, LT(5,KC_NO),
                                                  KC_TRNS,    KC_TRNS,
                                                              KC_TRNS,
                                      KC_SPC,     LGUI(KC_SPC),     KC_TRNS,

        // right hand
        KC_NO,        KC_NO,        KC_NO,      KC_NO,      KC_NO,       KC_NO,   KC_NO,
        KC_NO,        KC_Y,         KC_U,       KC_I,       KC_O,        KC_P,    M_BRC,
                      KC_H,         KC_J,       KC_K,       KC_L,        KC_SCLN, KC_ENT,
        KC_NO,        KC_N,         KC_M,       KC_COMM,    KC_DOT,      KC_SLSH, KC_QUOT,
        LT(6,KC_NO),  KC_LEFT,      KC_DOWN,    KC_UP,      KC_RIGHT,
        KC_TRNS,        KC_TRNS,
        KC_TRNS,
        TG(4),        KC_NO,        KC_BSPC
    ),

[LO40] = KEYMAP(  // layer 4 : default
        KC_TRNS,        KC_TRNS,      KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,  KC_TRNS,
        KC_TRNS,        S(KC_1),      S(KC_2),    S(KC_3),    S(KC_4),    S(KC_5),  KC_TRNS,
        KC_TRNS,        KC_TRNS,      KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,        KC_TRNS,      KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,  KC_TRNS,
        KC_TRNS,        KC_TRNS,      KC_TRNS,    KC_TRNS,    KC_TRNS,
                                                   KC_TRNS,    KC_TRNS,
                                                               KC_TRNS,
                                      KC_TRNS,     KC_TRNS,    KC_TRNS,

        // right hand
        KC_TRNS,        KC_TRNS,      KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_TRNS,   KC_TRNS,
        KC_TRNS,        S(KC_6),      S(KC_7),    S(KC_8),    S(KC_9),     S(KC_0),   S(M_MINUS),
                        KC_TRNS,      KC_TRNS,    S(KC_EQL),  S(KC_RBRC),  S(KC_LBRC),S(KC_BSLS),
        KC_TRNS,        KC_TRNS,      KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_TRNS,   KC_TRNS,
        KC_TRNS,        KC_TRNS,      KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,        KC_TRNS,
        KC_TRNS,
        KC_TRNS,        KC_TRNS,        KC_TRNS
    ),

[RA40] = KEYMAP(  // layer 5 : default
        KC_TRNS,        KC_TRNS,      KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,  KC_TRNS,
        KC_TRNS,        KC_1,         KC_2,       KC_3,       KC_4,       KC_5,     KC_TRNS,
        KC_TRNS,        KC_TRNS,      KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,        KC_TRNS,      KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,  KC_TRNS,
        KC_TRNS,        KC_TRNS,      KC_TRNS,    KC_TRNS,    KC_TRNS,
                                                   KC_TRNS,    KC_TRNS,
                                                               KC_TRNS,
                                      KC_TRNS,     KC_TRNS,    KC_TRNS,

        // right hand
        KC_TRNS,        KC_TRNS,      KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_TRNS,   KC_TRNS,
        KC_TRNS,        KC_6,         KC_7,       KC_8,       KC_9,        KC_0,      KC_MINUS,
                        KC_TRNS,      S(KC_MINS), S(KC_EQL),  S(KC_RBRC),  S(KC_LBRC),S(KC_BSLS),
        KC_TRNS,        KC_TRNS,      KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_TRNS,   KC_TRNS,
        KC_TRNS,        KC_TRNS,      KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,        KC_TRNS,
        KC_TRNS,
        KC_TRNS,        KC_TRNS,        KC_TRNS
    ),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(RAIS)                // FN1 - Momentary Layer 1 (Symbols)
};

static uint16_t key_timer;
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
        case 1:
        if (record->event.pressed) { // For resetting EEPROM
          eeconfig_init();
        }
        break;
        case MACRO_SHIFTIT_MOVE:
        if (record->event.pressed) {
          return MACRO(D(LCTL), D(LALT), D(LGUI), T(N), U(LCTL), U(LALT), U(LGUI), END);
        }
        break;
        case MACRO_SHIFTIT_FULL:
        if (record->event.pressed) {
          return MACRO(D(LCTL), D(LALT), D(LGUI), T(M), U(LCTL), U(LALT), U(LGUI), END);
        }
        break;
        case MACRO_SHIFTIT_RUP:
        if (record->event.pressed) {
          return MACRO(D(LCTL), D(LALT), D(LGUI), T(2), U(LCTL), U(LALT), U(LGUI), END);
        }
        break;
        case MACRO_SHIFTIT_LUP:
        if (record->event.pressed) {
          return MACRO(D(LCTL), D(LALT), D(LGUI), T(1), U(LCTL), U(LALT), U(LGUI), END);
        }
        break;
        case MACRO_SHIFTIT_LDOWN:
        if (record->event.pressed) {
          return MACRO(D(LCTL), D(LALT), D(LGUI), T(3), U(LCTL), U(LALT), U(LGUI), END);
        }
        break;
        case MACRO_SHIFTIT_RDOWN:
        if (record->event.pressed) {
          return MACRO(D(LCTL), D(LALT), D(LGUI), T(4), U(LCTL), U(LALT), U(LGUI), END);
        }
        break;
        case MACRO_SHIFTIT_LEFT:
        if (record->event.pressed) {
          return MACRO(D(LCTL), D(LALT), D(LGUI), T(5), U(LCTL), U(LALT), U(LGUI), END);
        }
        case MACRO_SHIFTIT_RIGHT:
        if (record->event.pressed) {
          return MACRO(D(LCTL), D(LALT), D(LGUI), T(6), U(LCTL), U(LALT), U(LGUI), END);
        }
        break;
        break;
        case MACRO_SHIFTIT_UP:
        if (record->event.pressed) {
          return MACRO(D(LCTL), D(LALT), D(LGUI), T(7), U(LCTL), U(LALT), U(LGUI), END);
        }
        break;
        case MACRO_SHIFTIT_DOWN:
        if (record->event.pressed) {
          return MACRO(D(LCTL), D(LALT), D(LGUI), T(8), U(LCTL), U(LALT), U(LGUI), END);
        }
        break;
        case MACRO_TMUX_ESC:
        if (record->event.pressed) {
          key_timer = timer_read();
        } else {
          if (timer_elapsed(key_timer) >= PUSH_TIME) {
            return MACRO(T(ESC), END);
          } else {
            return MACRO(T(GRV), END);
          }
        }
        break;
        case MACRO_TMUX_BRC:
        if (record->event.pressed) {
          key_timer = timer_read();
        } else {
          if (timer_elapsed(key_timer) >= PUSH_TIME) {
            return MACRO(T(RBRC), END);
          } else {
            return MACRO(T(LBRC), END);
          }
        }
        break;
        case MACRO_TMUX_LANG:
        if (record->event.pressed) {
          key_timer = timer_read();
        } else {
          if (timer_elapsed(key_timer) >= PUSH_TIME) {
            return MACRO(D(LGUI), T(SPC), U(LGUI), END);
          } else {
            return MACRO(END);
          }
        }
        break;
        case MACRO_TMUX_MINUS:
        if (record->event.pressed) {
          key_timer = timer_read();
        } else {
          if (timer_elapsed(key_timer) >= PUSH_TIME) {
            return MACRO(T(EQL), END);
          } else {
            return MACRO(T(MINUS), END);
          }
        }
        break;
        case MACRO_ZERO_ZERO:
        if (record->event.pressed) {
          SEND_STRING("00");
        }
        break;
      }
      return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};
