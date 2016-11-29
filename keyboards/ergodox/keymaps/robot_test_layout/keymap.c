#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  RGB_FF0000,
  RGB_00FF00,
  RGB_0000FF,
  RGB_FFFFFF,
  RGB_TOGGLE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = KEYMAP(
    RGB_TOGGLE,RGB_FF0000,RGB_00FF00,RGB_0000FF,RGB_FFFFFF,RGB_TOGGLE,KC_6,
    KC_A,KC_Q,KC_W,KC_E,KC_R,KC_T,KC_E,KC_A,KC_A,KC_S,KC_D,KC_F,KC_G,KC_A,KC_Z,KC_X,KC_C,KC_V,KC_B,KC_L,KC_Z,KC_QUOTE,KC_N,KC_U,KC_C,KC_E,KC_8,KC_9,KC_Y,KC_COMMA,KC_6,KC_7,KC_6,KC_7,KC_8,KC_9,KC_0,KC_MINUS,KC_J,KC_Y,KC_U,KC_I,KC_O,KC_P,KC_BSLASH,KC_H,KC_J,KC_K,KC_L,KC_J,KC_K,KC_Z,KC_N,KC_M,KC_COMMA,KC_DOT,KC_E,KC_QUOTE,KC_8,KC_7,KC_LBRACKET,KC_RBRACKET,KC_H,KC_9,KC_7,KC_8,KC_7,KC_6,KC_9),
};

const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_TAP_TOGGLE(1)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
      }
    return MACRO_NONE;
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case RGB_FF0000:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          EZ_RGB(0xff0000);
          register_code(KC_A); unregister_code(KC_A);
        #endif
      }
      return false;
      break;
    case RGB_00FF00:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          EZ_RGB(0x00ff00);
          register_code(KC_B); unregister_code(KC_B);
        #endif
      }
      return false;
      break;
    case RGB_0000FF:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          EZ_RGB(0x0000ff);
          register_code(KC_C); unregister_code(KC_C);
        #endif
      }
      return false;
      break;
    case RGB_FFFFFF:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          EZ_RGB(0xffffff);
          register_code(KC_D); unregister_code(KC_D);
        #endif
      }
      return false;
      break;
    case RGB_TOGGLE:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_toggle();
          register_code(KC_F); unregister_code(KC_F);
        #endif
      }
      return false;
      break;
  }
  return true;
}

void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        case 3:
            ergodox_right_led_3_on();
            break;
        case 4:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            break;
        case 5:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
            break;
        case 6:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        case 7:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        default:
            break;
    }

};
