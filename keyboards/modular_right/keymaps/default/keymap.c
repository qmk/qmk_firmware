#include "modular_right.h"
//:) no fn implimented
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = KEYMAP( /* Base */
            KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL, KC_BSPC, \
    KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC,KC_BSLS, \
    KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT, KC_NO,  KC_ENT,  \
    KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,                 KC_RSFT, \
        KC_SPC,     KC_RALT,        KC_RGUI,     KC_RGUI,    KC_RCTL  \
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


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

