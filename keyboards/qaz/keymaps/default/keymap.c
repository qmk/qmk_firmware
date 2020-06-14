#include QMK_KEYBOARD_H

enum layers{
  _BASE,
  _NUM_SYM,
  _NAV
};

enum custom_keycodes{
  RGBRST = SAFE_RANGE,
};

#define KC_NUM_SPC LT(_NUM_SYM, KC_SPC)
#define KC_GA LGUI_T(KC_A)
#define KC_AS LALT_T(KC_S)
#define KC_CD LCTL_T(KC_D)
#define KC_SF LSFT_T(KC_F)
#define KC_SJ RSFT_T(KC_J)
#define KC_CK RCTL_T(KC_K)
#define KC_AL RALT_T(KC_L)
#define KC_GSCLN RGUI_T(KC_SCLN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_qaz(
    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,    KC_I,   KC_O,     KC_P,
   KC_GA,  KC_AS,  KC_CD,  KC_SF,   KC_G,   KC_H,  KC_SJ,   KC_CK,  KC_AL, KC_ENT,
    KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M, KC_DOT, KC_COMMA,
  KC_LCTL, KC_LALT, KC_LGUI, KC_SPACE, KC_SPACE, KC_RALT, KC_RGUI, KC_RCTL
  ),

};
