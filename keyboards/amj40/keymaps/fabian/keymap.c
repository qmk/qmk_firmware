#include "amj40.h"

#undef KEYMAP
#define KEYMAP( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b,  \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,  \
    k30, k31, k32, k33, k34, k35,                k39, k3a, k3b  \
) { \
    {k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b}, \
    {k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b}, \
    {k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b}, \
    {k30, k31, k32, k33, k34, k35, XXX, XXX, XXX, k39, k3a, k3b} \
}

#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define TCTLESC CTL_T(KC_ESC)
#define TSFTBSP SFT_T(KC_BSPC) 
#define TSFTENT SFT_T(KC_ENT)


#define _BASE 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3


enum custom_keycodes {
  BASE = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = KEYMAP( \
        KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_BSPC, \
        TCTLESC,  KC_A,    KC_S,    KC_D,    KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
        TSFTBSP,  KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, TSFTENT, \
        F(2),     KC_LCTL, KC_LALT, KC_LGUI,         F(0),           F(1),            KC_RGUI, KC_RALT, KC_RCTL \
    ),
    [_LOWER] = KEYMAP( \
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
        KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,S(KC_NUHS),S(KC_NUBS),KC_HOME, KC_END, _______, \
        _______, _______, _______, _______,          _______,          KC_LEFT,          KC_DOWN, KC_UP,   KC_RGHT \
    ),
    [_RAISE] = KEYMAP( \
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
        KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______, \
        BL_STEP, _______, _______, _______,          _______,         _______,          KC_VOLD, KC_VOLU, KC_MPLY \
    ),
    [_ADJUST] = KEYMAP( \
        RESET  , _______, _______, _______, _______, _______, _______, _______, _______, KC_P7,    KC_P8,    KC_P9, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_P4,    KC_P5,    KC_P6, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_P1,    KC_P2,    KC_P3, \
        _______, _______, _______, _______,          _______,          _______,          KC_P0,    KC_PDOT,  KC_COMM \
    ),
};


enum function_id {
    LAUNCH,
    RGBLED_TOGGLE,
};


const uint16_t PROGMEM fn_actions[] = {
        [0]  = ACTION_LAYER_TAP_KEY(_LOWER, KC_SPC),
        [1]  = ACTION_LAYER_TAP_KEY(_RAISE, KC_SPC),
        [2]  = ACTION_LAYER_TAP_KEY(_ADJUST, KC_LGUI),
};


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    return MACRO_NONE;
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
