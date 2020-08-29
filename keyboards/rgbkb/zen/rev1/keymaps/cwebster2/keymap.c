#include QMK_KEYBOARD_H


enum layer_number {
    _QWERTY = 0,
    _SYMBOLS,
    _NAV
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    SYMBOLS,
    NAV
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


  /* Qwerty
   * ,-----------------------------------------.             .-----------------------------------------.
   * | GRV  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |   \  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Bksp |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  "   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |             |   N  |   M  |   ,  |   .  |   /  |Shift |
   * |------+------+------+------+------+------+------..-----+------+------+------+------+------+------|
   * | MO2  | GUI  | Alt  |RGBTOG| ESC  |Space | CTRL || GUI |Enter | left | down | up   | right| MO1  |
   * `------------------------------------------------''-----------------------------------------------'
   */


  [_QWERTY] = LAYOUT( \
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,                     KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,                     KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
    KC_BSPC, KC_A,    KC_S,    KC_D,    KC_F,   KC_G,                     KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,                     KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
    MO(2),   KC_LGUI, KC_LALT, RGB_TOG, TT(2), KC_SPC, LCTL_T(KC_ESC), LGUI_T(KC_BSPC), KC_ENT, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, MO(1)    \
  ),




  [_SYMBOLS] = LAYOUT( \
    KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
    KC_TRNS, RGB_RMOD, RGB_VAI, KC_TRNS, KC_LBRC, KC_RBRC,                   KC_RBRC, KC_PGUP, KC_UP,   KC_PGDN, KC_INS,  KC_HOME, \
    KC_TRNS, RGB_RMOD, RGB_VAD, KC_TRNS, KC_LCBR, KC_RCBR,                   KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL,  KC_END,  \
    KC_LSFT, RGB_SPD,  RGB_SPI, KC_TRNS, KC_MINS, KC_EQL,                    NK_TOGG, KC_TRNS, KC_TRNS, KC_MPLY, KC_MPRV, KC_MNXT, \
    KC_LCTL, KC_LGUI,  KC_LALT, RGB_MOD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MUTE, KC_VOLU, KC_TRNS  \
  ),


	[_NAV] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO)
};
