#include QMK_KEYBOARD_H

#define _NP 0
#define _BL  1
#define _MP 2

enum custom_keycodes {
  NP = SAFE_RANGE,
  BL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty
 * ,-----------------------------------------.
 * |   0  |   1  |   4  |   7  | NUM  | ESC  |
 * |------+------+------+------+------+------|
 * |   .  |   2  |   5  |   8  |   /  | TAB  |---,
 * |------+------+------+------+------+------|USB|
 * |  DOT |   3  |   6  |   9  |   *  | BS   |---'
 * |------+------+------+------+------+------|
 * | Enter| Enter|   +  |   +  |   -  | FN   |
 * `-----------------------------------------'
 */
[_NP] = LAYOUT( \
  KC_KP_0,     KC_KP_1,     KC_KP_4,    KC_KP_7,    KC_NUMLOCK,     KC_ESC,    \
  KC_DOT,      KC_KP_2,     KC_KP_5,    KC_KP_8,    KC_KP_SLASH,    KC_TAB,    \
  KC_KP_DOT,   KC_KP_3,     KC_KP_6,    KC_KP_9,    KC_KP_ASTERISK, KC_BSPACE, \
  KC_KP_ENTER, KC_ENTER, KC_KP_PLUS, KC_PLUS, KC_KP_MINUS,    TO(_BL)     \
),
/* Qwerty
 * ,---------------------------------------------.
 * | BL_BRTG |        |         |        |   |   |
 * |---------+--------+---------+--------+---+---|
 * |         | BL_OFF | BL_TOGG | BL_ON  |   |   |---,
 * |---------+--------+---------+--------+---+---|USB|
 * |         |        |         |        |   |   |---'
 * |---------+--------+---------+--------+---+---|
 * | BL_DEC  | BL_DEC | BL_INC  | BL_INC |   |   |
 * `---------------------------------------------'
 */
[_BL] = LAYOUT( \
  BL_BRTG, _______, _______, _______, _______, KC_NO, \
  _______, BL_OFF,  BL_TOGG, BL_ON,   _______, TO(_NP), \
  _______, _______, _______, _______, _______, TO(_MP), \
  BL_DEC,  BL_DEC,  BL_INC,  BL_INC,  _______, _______  \
),
/* Qwerty
 * ,---------------------------------------------.
 * | BL_BRTG |        |         |        |   |   |
 * |-------+--------+---------+--------+---+---|
 * |         | BL_OFF | BL_TOGG | BL_ON  |   |   |---,
 * |---------+--------+---------+--------+---+---|USB|
 * |         |        |         |        |   |   |---'
 * |---------+--------+---------+--------+---+---|
 * | BL_DEC  | BL_DEC | BL_INC  | BL_INC |   |   |
 * `---------------------------------------------'
 */
[_MP] = LAYOUT( \
  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TO(_NP), \
  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TO(_BL),  \
  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  \
  KC_A, KC_A, KC_NO, KC_NO,  KC_NO, KC_NO  \
)
};
