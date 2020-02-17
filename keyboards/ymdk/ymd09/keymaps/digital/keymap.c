#include QMK_KEYBOARD_H

enum custom_keycodes {
  QUITZOOM = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT(KC_MPRV, KC_MNXT, KC_MPLY,
               KC_KP_4, LT(1, KC_KP_5), KC_KP_6,
               QUITZOOM, KC_KP_2, KC_KP_3),

  [1] = LAYOUT(RGB_RMOD, RGB_VAI, RGB_MOD,
               RGB_HUI, KC_TRNS, RGB_SAI,
               RGB_HUD, RGB_VAD, RESET),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QUITZOOM:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT("q"));
        _delay_ms(1000);
        register_code(KC_ENT);
      } else {
      }
      break;

  }
  return true;
};
