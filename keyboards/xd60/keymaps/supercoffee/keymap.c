#include "xd60.h"
#include "action_layer.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // 0: Base Layer
  LAYOUT_ALL(
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,  KC_NO,    \
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,    KC_LBRC,  KC_RBRC,           KC_BSLS,   \
      KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN, KC_QUOT,  KC_NO,             KC_ENT,    \
      KC_LSFT, KC_NO,   KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,  KC_NO, KC_RSHIFT,  KC_NO,      \
      KC_LCTL, KC_LGUI, KC_LALT,                          KC_SPC,                          F(0),    KC_RALT,  KC_NO, KC_RGUI,    KC_RCTL),

  // 1: Function Layer
  LAYOUT_ALL(
      KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,   KC_F6,   KC_F7,   KC_F8,  KC_F9,  KC_F10, KC_F11,   KC_F12,  KC_F13,   KC_F14,    \
      KC_NO,   KC_NO,   KC_UP,   KC_END,  KC_NO,  KC_NO,   KC_CALC, KC_PGUP, KC_NO, KC_NO,    KC_NO,  KC_NO,    KC_NO,             KC_DEL,    \
      KC_NO,   KC_LEFT, KC_DOWN, KC_RIGHT,KC_NO,  KC_NO,   KC_HOME, KC_PGDN, KC_NO,  KC_NO,   KC_NO,  KC_PGUP,  KC_NO,             KC_ENT,    \
      KC_LSFT, KC_NO,   KC_NO,   KC_DEL,  BL_STEP,KC_NO,   KC_NO,   KC_VOLD, KC_VOLU,KC_MUTE, KC_NO,  KC_PGDN,  KC_RSFT, KC_NO,    KC_NO,      \
      KC_LCTL, KC_LGUI, KC_LALT,                           KC_SPC,                            F(0),   KC_RALT,  KC_NO, KC_RGUI,    KC_RCTL),

};

// Custom Actions
const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1),  // to Fn overlay
};

// Macros
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {

  // MACRODOWN only works in this function
  switch(id) {
    case 0:
      if (record->event.pressed) { register_code(KC_RSFT); }
      else { unregister_code(KC_RSFT); }
      break;
  }

  return MACRO_NONE;
};

// Loop
void matrix_scan_user(void) {
  // Empty
};
