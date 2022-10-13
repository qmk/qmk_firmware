#include QMK_KEYBOARD_H

extern uint8_t is_master;

enum layer_names {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_ortho_4x12(
   KC_ESC, KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,             KC_Y,  KC_U,  KC_I, KC_O,   KC_P, KC_BSPC,
   KC_TAB, KC_A,  KC_S,  KC_D,  KC_F,  KC_G,             KC_H,  KC_J,  KC_K, KC_L,   SFT_T(KC_SCLN), KC_RGUI,
   KC_SPC, KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,             KC_N,  KC_M,  KC_RCTL, KC_DOT, KC_RALT, RGUI(KC_RSFT),
   KC_LGUI, KC_LALT, _______, _______, LOWER, KC_ENT,    KC_ENT, RAISE, _______, _______, _______, _______
   ),

  [_LOWER] =  LAYOUT_ortho_4x12(
   KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR,  KC_PERC,    KC_CIRC, KC_AMPR, KC_ASTR, RCMD(RALT(KC_O)), RCMD(RALT(KC_L)), _______,
   _______, KC_LT, KC_GT, KC_LPRN, KC_RPRN, KC_GRV,       KC_MINS, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_PIPE,
   KC_LALT, _______, _______, _______, KC_EQL, KC_QUES,   KC_UNDS, KC_PLUS, KC_COMM, _______, KC_SLSH, _______,
   _______, _______, _______, _______, _______, KC_TRNS,  KC_TRNS, KC_RGUI, _______, _______, _______, _______
   ),

  [_RAISE] = LAYOUT_ortho_4x12(
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  _______,
    _______, KC_COLN, KC_SCLN, KC_DQT, KC_QUOT, KC_BSLS,   KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______, _______,
    _______, _______, _______, _______, _______, _______,  ADJUST, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, KC_LGUI, KC_TRNS,  KC_TRNS, _______, _______, _______, _______, _______
    ),

  [_ADJUST] =  LAYOUT_ortho_4x12(
    RGB_VAI,   RGB_SAI, RGB_HUI,  RGB_MOD,  XXXXXXX,   RGB_TOG,    KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  XXXXXXX,
    RGB_VAD,   RGB_SAD, RGB_HUD,  RGB_RMOD, XXXXXXX,   XXXXXXX,    KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10,  XXXXXXX,
    KC_MUTE, KC_VOLD, KC_VOLU, KC_BRID, KC_BRIU,  QK_BOOT,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_LNG1,  KC_LNG2,
    _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, KC_INT2
    ),
};
