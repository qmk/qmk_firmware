#include QMK_KEYBOARD_H

#define BASE 0
#define SYMB 1
#define ETC 2

enum macro_id {
    TEENSY,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT(
    KC_Q,          KC_W,    KC_D,     KC_F,           KC_K,                                              KC_J,             KC_U,            KC_R,     KC_L,     KC_SCLN,
    LT(ETC,KC_A),  KC_S,    KC_E,     KC_T,           KC_G,                                              KC_Y,             KC_N,            KC_I,     KC_O,     KC_H,
    SFT_T(KC_Z),   KC_X,    KC_C,     KC_V,           KC_B,                                              KC_P,             KC_M,            KC_COMM,  KC_DOT,   SFT_T(KC_SLSH),
    KC_GRV,        KC_DEL,  KC_LALT,  GUI_T(KC_TAB),  LT(SYMB,KC_BSPC),  CTL_T(KC_ESC),  SFT_T(KC_ENT),  LT(SYMB,KC_SPC),  GUI_T(KC_LEFT),  KC_DOWN,  KC_UP,    LCAG_T(KC_RGHT)
  ),

  [SYMB] = LAYOUT(
    KC_EXLM,  KC_AT,    KC_LCBR,  KC_RCBR,  KC_PIPE,                      KC_EQL,   KC_7,  KC_8,   KC_9,    KC_PLUS,
    KC_HASH,  KC_DLR,   KC_LPRN,  KC_RPRN,  KC_BSLS,                      KC_MINS,  KC_4,  KC_5,   KC_6,    KC_QUOT,
    KC_PERC,  KC_CIRC,  KC_LBRC,  KC_RBRC,  KC_ASTR,                      KC_UNDS,  KC_1,  KC_2,   KC_3,    KC_DQUO,
    KC_TILD,  KC_AMPR,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_0,  KC_NO,  KC_DOT,  KC_TRNS
  ),

  [ETC] = LAYOUT(
    RESET,         KC_NO,  KC_NO,    KC_NO,    KC_PGUP,                      KC_VOLU,  KC_F7,  KC_F8,  KC_F9,   KC_HOME,
    LT(ETC,KC_A),  KC_NO,  KC_NO,    KC_NO,    KC_PGDN,                      KC_VOLD,  KC_F4,  KC_F5,  KC_F6,   KC_END,
    KC_NO,         KC_NO,  KC_NO,    KC_NO,    KC_DEL,                       KC_MUTE,  KC_F1,  KC_F2,  KC_F3,   KC_INS,
    KC_TRNS,       KC_NO,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_NO,  KC_NO,  KC_NO,   KC_NO
  ),
};

const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch(id) {
    case TEENSY:
      break;
  }
  return MACRO_NONE;
};
