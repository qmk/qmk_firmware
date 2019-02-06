#include QMK_KEYBOARD_H

#define _NP 0
#define _BL  1
#define _MP 2

//Tap Dance Config
enum {
  TD_A_B = 0,
  TD_C_D
};

qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap Enter for A, twice for B
  [TD_A_B] = ACTION_TAP_DANCE_DOUBLE(KC_A,KC_B),
  // Other declarations would go here, separated by commas, if you have them
  [TD_C_D] = ACTION_TAP_DANCE_DOUBLE(KC_C,KC_D)
};


/* Note the Enter and Plus(+) key only need the second key
 * in the sequence to work, if only the first is set then it
 * will not work.
 *
 * for the zero (0) key, the upper level key needs to be set
*/
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty
 * ,----------------------------------------------.
 * |      |   1  |   4  |   7  | NUM  | ESC       |
 * |  0   +------+------+------+------+-----------|
 * |      |   2  |   5  |   8  |   /  | TAB       |---,
 * |------+------+------+------+------+-----------|USB|
 * |  DOT |   3  |   6  |   9  |   *  | BS        |---'
 * |------+------+------+------+------+-----------|
 * |     Enter   |      +      |   -  | TO(_BL)   |
 * `----------------------------------------------'
 */

[_NP] = LAYOUT_numpad_6x4( \
  KC_KP_0,     KC_KP_1,     KC_KP_4,    KC_KP_7,    KC_NUMLOCK,     KC_ESC,    \
  KC_NO,       KC_KP_2,     KC_KP_5,    KC_KP_8,    KC_KP_SLASH,    KC_TAB,    \
  KC_KP_DOT,   KC_KP_3,     KC_KP_6,    KC_KP_9,    KC_KP_ASTERISK, KC_BSPACE, \
  KC_KP_ENTER, KC_KP_ENTER, KC_KP_PLUS, KC_PLUS,    KC_KP_MINUS,    TO(_BL)    \
),
/* Backlight
 * ,----------------------------------------------------.
 * | BL_BRTG |        |         |        |   | //////// |
 * |---------+--------+---------+--------+---+----------|
 * |         | BL_OFF | BL_TOGG | BL_ON  |   | TO(_MP)  |---,
 * |---------+--------+---------+--------+---+----------|USB|
 * |         |        |         |        |   | //////// |---'
 * |---------+--------+---------+--------+---+----------|
 * | BL_DEC  | BL_DEC | BL_INC  | BL_INC |   | //////// |
 * `----------------------------------------------------'
 */
[_BL] = LAYOUT_numpad_6x4( \
  BL_BRTG, _______, _______, _______, _______, KC_NO,   \
  _______, BL_OFF,  BL_TOGG, BL_ON,   _______, TO(_MP), \
  _______, _______, _______, _______, _______, KC_NO,   \
  BL_DEC,  BL_DEC,  BL_INC,  BL_INC,  _______, KC_NO    \
),
/* Macropad
 * ,----------------------------------------------------.
 * |         |        |         |        |   | TO(_NP)  |
 * |         +--------+---------+--------+---+----------|
 * |         |        |         |        |   | //////   |---,
 * |---------+--------+---------+--------+---+----------|USB|
 * |         |        |         |        |   |          |---'
 * |---------+--------+---------+--------+---+----------|
 * |     TD(A,B)      |      TD(C,D)     |   |          |
 * `----------------------------------------------------'
 */
/* Note the Enter and Plus(+) key only need the second key
 * in the sequence to work, if only the first is set then it
 * will not work.
 *
 * for the zero (0) key, the lower level key needs to be set
*/
[_MP] = LAYOUT_numpad_6x4( \
  TD(TD_C_D), KC_NO, KC_NO, KC_NO, KC_NO, TO(_NP),                     \
  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                            \
  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                            \
  KC_NO, TD(TD_A_B), KC_NO, TD(TD_C_D),  KC_NO, KC_NO                  \
)
};

uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
    case _NP:
        backlight_set(1);
        break;
    case _BL:
        backlight_set(0);
        break;
    case _MP:
        backlight_set(1);
        break;

    default: //  for any other layers, or the default layer
        backlight_set(0);
        break;
    }
  return state;
}
