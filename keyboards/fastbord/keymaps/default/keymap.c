#include "fastbord.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = KEYMAP( /* Base */
  KC_M, KC_A, KC_X, KC_SPC, KC_I, KC_S, KC_SPC, KC_T,   KC_H,   KC_E, KC_SPC, KC_B, \
  KC_E, KC_S, KC_T, KC_SPC, KC_A, KC_N, KC_D,   KC_SPC, KC_T,   KC_H, KC_E,   KC_SPC, \
  KC_F, KC_A, KC_S, KC_T,   KC_E, KC_S, KC_T,   KC_SPC, KC_B,   KC_U, KC_I,   KC_L, \
  KC_D, KC_E, KC_R, KC_SPC, KC_I, KC_N, KC_SPC, KC_R,   KC_SLSH, KC_M, KC_K,   KC_ENT \ 
),
};

const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};


void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {

}