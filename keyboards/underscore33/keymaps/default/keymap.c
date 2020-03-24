
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
  [_BASE] = LAYOUT_33_SPLIT_SPACE(
    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,    KC_I,   KC_O,     KC_P,
   KC_GA,  KC_AS,  KC_CD,  KC_SF,   KC_G,   KC_H,  KC_SJ,   KC_CK,  KC_AL, KC_GSCLN,
    KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M, KC_COMM, KC_DOT,  KC_SLSH,
                 KC_LCTL, KC_LALT, KC_NUM_SPC, MO(_NAV), KC_RGUI
  ),

  [_NUM_SYM] = LAYOUT_33_SPLIT_SPACE(
       KC_1,     KC_2,     KC_3,     KC_4,      KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,
    KC_EXLM,    KC_AT,  KC_HASH,   KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR, KC_EQUAL,  KC_MINS,
    KC_BSLS,  KC_LCBR,  KC_LBRC,  KC_LPRN,   KC_UNDS,  KC_RPRN,  KC_RBRC,  KC_RCBR,   KC_DOT,   KC_GRV,
                  KC_TRNS,   KC_TRNS,  KC_TRNS, KC_TRNS,   KC_TRNS
  ),

  [_NAV] = LAYOUT_33_SPLIT_SPACE(
      RESET,   RGBRST,  AG_NORM,  AG_SWAP,  DEBUG,   KC_GRV,  KC_PGDN,    KC_UP,  KC_PGUP,  KC_SCLN,
    RGB_TOG,  RGB_HUI,  RGB_SAI,  RGB_VAI,  KC_NO,  KC_HOME,  KC_LEFT,  KC_DOWN,  KC_RGHT,   KC_END,
    RGB_MOD,  RGB_HUD,  RGB_SAD,  RGB_VAD,  KC_NO,  KC_MINS,    KC_RO,  KC_COMM,   KC_DOT,  KC_BSLS,
                   KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,   KC_TRNS
  ),
};
