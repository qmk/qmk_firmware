#include QMK_KEYBOARD_H

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Numpad
 * ,-----------------------------------------------------------------------------------.
 * |   0  |   1  |   4  |   7  |  Esc | NLCK |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   ,  |   2  |   5  |   8  |   /  | Down |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   .  |   3  |   6  |   9  |   *  | Up   |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |    Enter    |   +  |   -  |   ?  | Tab  |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[0] = LAYOUT_ortho_4x12( \
    KC_KP_0,     KC_KP_1,     KC_KP_4,    KC_KP_7,     KC_ESC,         KC_NLCK, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, \
    KC_COMMA,    KC_KP_2,     KC_KP_5,    KC_KP_8,     KC_KP_SLASH,    KC_DOWN, KC_NO, KC_A, KC_B, KC_C, KC_D, KC_NO, \
    KC_KP_DOT,   KC_KP_3,     KC_KP_6,    KC_KP_9,     KC_KP_ASTERISK, KC_UP,   KC_NO, KC_E, KC_F, KC_G, KC_H, KC_NO, \
    KC_KP_ENTER, KC_NO,       KC_KP_PLUS, KC_KP_MINUS, KC_QUESTION,    KC_TAB,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO \
)

};

