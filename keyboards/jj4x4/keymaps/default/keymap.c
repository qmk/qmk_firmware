#include QMK_KEYBOARD_H


#define _QWERTY 0


enum custom_keycodes {
  QWERTY = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty
 * ,---------------------------.
 * |   A  |   B  |   C  |  D   |
 * +------+------+------+------|
 * |   E  |   F  |   G  |  H   |
 * +------+------+------+------|
 * |   I  |   J  |   K  |  L   |
 * +------+------+------+------|
 * |   M  |   N  |   O  |  P   |
 * ----------------------------'
 */
[_QWERTY] = LAYOUT_ortho_4x4( \
  KC_A,    KC_B,    KC_C,   KC_D, \
  KC_E,    KC_F,    KC_G,   KC_H, \
  KC_I,    KC_J,    KC_K,   KC_L, \
  KC_M,    KC_N,    KC_O,   KC_P  \
),
};

// Loop
void matrix_scan_user(void) {
  // Empty
};
