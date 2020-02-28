
#include QMK_KEYBOARD_H
#include "quantum.h"
#include "tominabox1.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_brutal_wrap(
	KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_QUOTE,
	_______________HOMEROW_MOD_________________,
	_______________COLEMAK3____________________,
    KC_NAV_ENT, KC_NUM_SPC, KC_NAV_ENT
  ),

  [_NUM_SYM] = LAYOUT_brutal_wrap(
	__________________NUM_1____________________,
	__________________NUM_2____________________,
	KC_BSLS, __________________NUM_3____________________, KC_DOT, KC_GRV,
    KC_TRNS,   KC_TRNS,  KC_TRNS
  ),

  [_NAV] = LAYOUT_brutal(
    RESET,  KC_NO,  KC_NO, KC_NO, KC_NO,  KC_NO,  KC_PGDN,    KC_UP,  KC_PGUP,    KC_SCLN,
    SPONGEBOB,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_HOME,  KC_LEFT,  KC_DOWN,  KC_RGHT,   KC_END,
    AESTHETIC,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,  KC_COMM,   KC_DOT,  KC_BSLS,
    KC_TRNS,   KC_TRNS,  KC_TRNS
  ),
};

#ifdef RGBLIGHT_ENABLE
const uint8_t RGBLED_BREATHING_INTERVALS[] PROGMEM = {100, 30, 5, 1};

void keyboard_post_init_user(void) {
  // rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
  // Init the LEDs to a static color
  // rgblight_sethsv_at(0, 0, 0, 0);
  // rgblight_sethsv_at(0, 0, 0, 1);
  // rgblight_sethsv_at(0, 0, 0, 2);
  setrgb(0, 0, 0, (LED_TYPE *)&led[0]);
  setrgb(0, 0, 0, (LED_TYPE *)&led[1]);
  setrgb(0, 0, 0, (LED_TYPE *)&led[2]);
  rgblight_set();
}

uint32_t layer_state_set_keymap(uint32_t state){
  // uint8_t led0r = 0; uint8_t led0g = 0; uint8_t led0b = 0;
  // uint8_t led1r = 0; uint8_t led1g = 0; uint8_t led1b = 0;
  if (layer_state_cmp(state, _NUM_SYM)) {
    // led0r = 100;
    // led0g = 200;
    rgblight_setrgb_at(100, 200, 0, 0);
  }
  if (layer_state_cmp(state, _NAV)) {
    // led1g = 50;
    // led1b = 50;
    rgblight_setrgb_at(0, 50, 50, 1);
  }

  if (layer_state_cmp(state, _BASE)) {
    rgblight_setrgb_at(0, 0, 0, 0);
    rgblight_setrgb_at(0, 0, 0, 1);
  }

  // setrgb(led0r, led0g, led0b, (LED_TYPE *)&led[0]);
  // setrgb(led1r, led1g, led1b, (LED_TYPE *)&led[1]);
  rgblight_set();

  return state;
}

bool led_update_kb(led_t led_state){
  if(led_state.caps_lock){
      rgblight_setrgb_at(10, 10, 0, 2);
      rgblight_set();
  } else{
      rgblight_sethsv_at(0, 0, 0, 2);
      rgblight_set();
  }
    return true;
}
//
// void led_set_user(uint8_t usb_led){
//   if(usb_led & (1<<USB_LED_CAPS_LOCK)){
//     rgblight_set_effect_range(2, 1);
//     rgblight_sethsv_noeeprom(180, 200, 150);
//     rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
//     rgblight_set();
//   } else{
//     rgblight_set_effect_range(2, 1);
//     rgblight_sethsv_noeeprom(180, 200, 0);
//     rgblight_set();
//   }
// }
#endif //RGBLIGHT_ENABLE
