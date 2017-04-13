#include "miuni32.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] ={
       {KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_BSPC},
       {KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_RSFT, KC_ENT},
       {KC_Z,   KC_X,   KC_C,   KC_V,   KC_V,  KC_SPC, KC_B,   KC_N,   KC_M ,  MO(1), KC_RCTL}
     },
[1] ={
       {KC_PGUP,  KC_UP,    KC_PGDN,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_DEL},
       {KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_TRNS,  KC_HOME,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_END,   KC_TRNS},
       {RGB_TOG,  RGB_HUI,  RGB_HUD,  RGB_SAI,  KC_TRNS,  RGB_SAD,  RGB_VAI,  RGB_VAD, KC_TRNS, KC_TRNS, RGB_MOD},
     }
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
