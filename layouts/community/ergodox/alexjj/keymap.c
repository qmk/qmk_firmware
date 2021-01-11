#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys
#define UNIC 3 // unicode entry layer

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   ESC  |  1!  |  2@  |  3#  |  4$  |  5%  |  6^  |           |  7&  |  8*  |  9(  |  0)  |  -_  |  +=  |  BkSp  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |  {   |           |   }  |   Y  |   U  |   I  |   O  |   P  |  |\    |
 * |--------+------+------+------+------+------|  [   |           |   ]  |------+------+------+------+------+--------|
 * | Win    |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |  :;  |  '"    |
 * |--------+------+------+------+------+------| Home |           | End  |------+------+------+------+------+--------|
 * | LShift |Z/Alt |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  | Alt  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |LCtrl | COPY | PASTE| Left | Right|                                       | Down |  Up  |Hyper |  `~  | RCtrl |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *   Hyper = Ctrl+Super+Alt+Shift         | ~L3  |  F5  |       |  F2  | ~L2  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | PgUp |       | Ins  |      |      |
 *                                 | Enter| BkSp |------|       |------| ~L1  |Space |
 *                                 |      |      | PgDn |       | Del  |      |      |
 *                                 `--------------------'       `--------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_ESC,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   KC_6,
        KC_TAB,         KC_Q,         KC_W,   KC_E,   KC_R,   KC_T,   KC_LBRC,
        KC_LGUI,        KC_A,         KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSFT,        ALT_T(KC_Z),  KC_X,   KC_C,   KC_V,   KC_B,   KC_HOME,
        KC_LCTRL,       LCTL(KC_C), LCTL(KC_V),  KC_LEFT,KC_RGHT,
                                                      TT(UNIC),  KC_F5,
                                                              KC_PGUP,
                                               KC_ENT,KC_BSPC,KC_PGDN,
        // right hand
             KC_7,     KC_8,   KC_9,   KC_0,   KC_MINS,   KC_EQL,        KC_BSPC,
             KC_RBRC,  KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,             KC_BSLS,
                       KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,
             KC_END,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,   KC_RSFT,
             KC_DOWN,KC_UP, ALL_T(KC_NO),KC_GRV,   KC_RCTRL,
             KC_F2, TT(MDIA),
             KC_INS,
             KC_DEL,TT(SYMB), KC_SPC
    ),
/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |PrintScr|
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |   £  |      |      |      |                                       |      |    . |   0  |   =  |Alt+F4|
 *   `----------------------------------'                                       `----------------------------------'
 *              ↑                         ,-------------.       ,-------------.
 *           THERE!                       |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *    CAD = Ctrl + Alt + Delete    |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       | CAD  |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
       // left hand
       KC_TRNS,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,
       KC_TRNS,KC_EXLM,KC_AT,  KC_LCBR,KC_RCBR,KC_PIPE,KC_TRNS,
       KC_TRNS,KC_HASH,KC_DLR, KC_LPRN,KC_RPRN,KC_GRV,
       KC_TRNS,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD,KC_TRNS,
       KC_TRNS,M(3),KC_TRNS,KC_TRNS,KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_F7, KC_F8,   KC_F9,  KC_F10,   KC_F11,   KC_F12,  KC_PSCR,
       KC_TRNS, KC_UP,   KC_7,   KC_8,    KC_9,    KC_ASTR, KC_TRNS,
                KC_DOWN, KC_4,   KC_5,    KC_6,    KC_PLUS, KC_TRNS,
       KC_TRNS, KC_AMPR, KC_1,   KC_2,    KC_3,    KC_BSLS, KC_TRNS,
                         KC_TRNS,KC_DOT,  KC_0,    KC_EQL,  LALT(KC_F4),
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       LCTL(LALT(KC_DEL)), KC_TRNS, KC_TRNS
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | TEENSY |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolDn |VolUp | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = LAYOUT_ergodox(
       RESET, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                          KC_VOLD, KC_VOLU, KC_MUTE, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
),
/* Keymap 3: Unicode Entry
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  Alt   |  1   |   2  |  3   |  4   |   5  |  6   |           |   7  |  8   |   9  |  0   |  +   |  +   |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  Alt   |      |      |   E  |      |      |      |           |      |      |   7  |   8  |  9   |  +   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  Alt   |   A  |      |   D  |   F  |      |------|           |------|      |   4  |   5  |  6   |  +   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  Alt   |      |      |   C  |      |   B  |      |           |      |      |   1  |   2  |  3   |  +   |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Alt  |  Alt | Alt  |      |      |                                       |   0  |   0  |  0   |  +   |       |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *      WINDOWS ONLY SETUP!!              | ~L3  |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |  Alt |  Alt |------|       |------|  Alt | Alt  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[UNIC] = LAYOUT_ergodox(  // layer 3 : Unicode Entry
        // left hand
       KC_LALT,       KC_P1,      KC_P2,      KC_P3,  KC_P4,     KC_P5,   KC_P6,
      KC_LALT,       KC_TRNS,    KC_TRNS,    KC_E,   KC_TRNS,   KC_TRNS, KC_TRNS,
      KC_LALT,       KC_A,       KC_TRNS,    KC_D,   KC_F,      KC_TRNS,
      KC_LALT,       KC_TRNS,    KC_TRNS,    KC_C,   KC_TRNS,   KC_B,    KC_TRNS,
      KC_LALT,       KC_LALT,    KC_LALT,    KC_TRNS,KC_TRNS,
                                                     KC_TRNS,   KC_TRNS,
                                                                KC_TRNS,
                                             KC_LALT,KC_LALT,   KC_TRNS,
        // right hand
           KC_P7,    KC_P8,     KC_P9,   KC_P0,   KC_PPLS,KC_PPLS,      KC_TRNS,
           KC_TRNS,  KC_TRNS,   KC_P7,   KC_P8,   KC_P9,  KC_PPLS,      KC_TRNS,
                     KC_TRNS,   KC_P4,   KC_P5,   KC_P6,  KC_PPLS,      KC_TRNS,
           KC_TRNS,  KC_TRNS,   KC_P1,   KC_P2,   KC_P3,  KC_PPLS,      KC_TRNS,
                                KC_P0,   KC_P0,   KC_P0,  KC_PPLS,      KC_TRNS,
           KC_TRNS, KC_TRNS,
           KC_TRNS,
           KC_TRNS,KC_LALT, KC_LALT
                  ),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          register_code(KC_RSFT);
        } else {
          unregister_code(KC_RSFT);
        }
      case 3: // this would trigger when you hit a key mapped as M(3)
        if (record->event.pressed) {
          return MACRO( I(255), D(LALT), T(P1), T(P5), T(P6), U(LALT), END  );
      }
        break;
      }
    return MACRO_NONE;
};

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
        case 3:
            ergodox_right_led_3_on();
            break;
        default:
            // none
            break;
    }

};
