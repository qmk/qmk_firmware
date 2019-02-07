#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  RGB_FF0000,
  RGB_00FF00,
  RGB_0000FF,
  RGB_FFFFFF,
  RGB_TOGGLE,
  LED1,
  LED2,
  LED3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT_ergodox(
        RGB_TOGGLE, RGB_FF0000, RGB_00FF00, RGB_0000FF, RGB_FFFFFF, KC_5, KC_LPRN,
        KC_GRAVE,   KC_A,       KC_B,       KC_C,       KC_D,       KC_E, KC_EXLM,
        KC_HASH,    KC_J,       KC_K,       KC_L,       KC_M,       KC_N,
        KC_AMPR,    KC_T,       KC_U,       KC_V,       KC_W,       KC_X, KC_DLR,
        KC_PIPE,    KC_R,       KC_PLUS,    KC_LCBR,    KC_RCBR,

                                            KC_F, KC_G,
                                                  KC_H,
                                     KC_P,  KC_O, KC_I,



                                               // RIGHT HAND
                                               KC_RPRN,       KC_6, KC_7, KC_8,    KC_9,   KC_0,    KC_MINS,
                                               KC_AT,         KC_F, KC_G, KC_H,    KC_I,   KC_COLN, KC_BSLS,
                                                              KC_O, KC_P, KC_Q,    KC_R,   KC_S,    KC_QUOT,
                                               LSFT(KC_COMM), KC_Y, KC_Z, KC_COMM, KC_DOT, KC_SLSH, KC_ASTR,
                                                              KC_A, KC_B, KC_C,    KC_D,   KC_PIPE,

                                               LED1, KC_E,
                                               LED2,
                                               LED3, KC_J, KC_K
    )
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

bool status_led1_on = false, status_led2_on = false, status_led3_on = false;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case RGB_FF0000:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          EZ_RGB(0xff0000UL);
          register_code(KC_1); unregister_code(KC_1);
        #endif
      }
      return false;
      break;
    case RGB_00FF00:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          EZ_RGB(0x00ff00UL);
          register_code(KC_2); unregister_code(KC_2);
        #endif
      }
      return false;
      break;
    case RGB_0000FF:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          EZ_RGB(0x0000ffUL);
          register_code(KC_3); unregister_code(KC_3);
        #endif
      }
      return false;
      break;
    case RGB_FFFFFF:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          EZ_RGB(0xffffffUL);
          register_code(KC_4); unregister_code(KC_4);
        #endif
      }
      return false;
      break;
    case RGB_TOGGLE:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_toggle();
          register_code(KC_EQL); unregister_code(KC_EQL);
        #endif
      }
      return false;
      break;
    case LED1:
      if (record->event.pressed) {
        if(status_led1_on) {
        ergodox_right_led_1_off();
        status_led1_on = false;
        } else {
        ergodox_right_led_1_on();
        status_led1_on = true;
        }
      }
      return false;
      break;
    case LED2:
      if (record->event.pressed) {
        if(status_led2_on) {
        ergodox_right_led_2_off();
        status_led2_on = false;
        } else {
        ergodox_right_led_2_on();
        status_led2_on = true;
        }
      }
      return false;
      break;
    case LED3:
      if (record->event.pressed) {
        if(status_led3_on) {
        ergodox_right_led_3_off();
        status_led3_on = false;
        } else {
        ergodox_right_led_3_on();
        status_led3_on = true;
        }
      }
      return false;
      break;
  }
  return true;
}
