#include "keymap_common.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = { /* Qwerty */
  {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_KP_MINUS, KC_KP_PLUS, KC_KP_PLUS, KC_KP_ENTER, KC_KP_ENTER},
  {KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_KP_ASTERISK, KC_KP_9, KC_KP_6,    KC_KP_3,  KC_KP_DOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_KP_SLASH,    KC_KP_8, KC_KP_5,  KC_KP_2, KC_KP_0},
  {BL_STEP, KC_LCTL, KC_LALT, KC_LGUI, KC_NO, KC_SPC,  KC_SPC,  KC_NUMLOCK,   KC_KP_7, KC_KP_4, KC_KP_1,  KC_KP_0}
                                                // Space is repeated to accommadate for both spacebar wiring positions
}
};

const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) 
{
  // MACRODOWN only works in this function
    switch(id) {
      case 0:
        return MACRODOWN(T(CM_T), END);
      break;
    } 
    return MACRO_NONE;
};