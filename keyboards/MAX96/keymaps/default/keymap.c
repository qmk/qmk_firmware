#include "MAX96.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = KEYMAP( /* Base */
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_GRV,  KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
  KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_ENT,  KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RSFT, KC_UP,   KC_P1,   KC_P2,   KC_P3,   KC_PENT,
  KC_LCTL, MO(1),   KC_LALT, KC_LGUI, KC_ENT,  KC_SPC,  KC_SPC,  KC_BSPC, KC_RGUI, KC_RALT, KC_RCTL, DF(1), KC_LEFT, KC_DOWN, KC_RGHT, KC_P0,   KC_PDOT, KC_PENT 
),
[1] = KEYMAP( \
  KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_MINS, KC_EQL,  KC_GRV,  KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
  KC_TAB,  RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, RGB_TOG, RGB_MOD, RGB_HUI,   KC_PPLS,
  KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_ENT,  RGB_HUD, RGB_SAI, RGB_SAD,   KC_PPLS,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, RESET, KC_UP,   KC_P1,   RGB_VAI, RGB_VAD,   KC_PENT,
  KC_LCTL, KC_TRNS, KC_LALT, KC_LGUI, KC_ENT,  KC_SPC,  KC_SPC,  KC_BSPC, KC_RGUI, KC_RALT, KC_RCTL,KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_P0,  KC_PDOT, KC_PENT
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