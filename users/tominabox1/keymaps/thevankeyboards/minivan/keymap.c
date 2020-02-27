#include QMK_KEYBOARD_H
#include "tominabox1.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT_arrow_wrapper(
    KC_ESC, _______________COLEMAK1____________________, KC_BSPC,
    KC_CTLTB,  _______________HOMEROW_MOD_________________, KC_QUOT,
    KC_LSFT,   _______________COLEMAK3____________________, KC_RSFT,
    KC_DEL, KC_LCTL, KC_LGUI, KC_LALT, KC_NUM_SPC,  KC_NUM_SPC,  KC_NAV_ENT, MO(_FKEY), KC_NO, MO(_FKEY)
  ),

  [_NUM_SYM] = LAYOUT_arrow_wrapper(
    KC_GRV,  __________________NUM_1____________________, KC_BSPC,
    KC_TILD, __________________NUM_2____________________, KC_PIPE,
    KC_DEL,  KC_NO, __________________NUM_3____________________, KC_DOT, KC_SLSH, KC_RSFT,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [_NAV] = LAYOUT_arrow_wrapper(
    KC_NO, ___________________NAV1____________________, KC_NO,
    KC_NO,___________________NAV2____________________, KC_NO,
    KC_LTOG,   ___________________NO______________________, KC_NO,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [_FKEY] = LAYOUT_arrow_wrapper(
    RESET,___________________FKEY1___________________, KC_F11,
    KC_NO,  ___________________NO______________________, KC_NO,
    KC_NO,   ___________________NO______________________, KC_NO,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),
};

#ifdef RGBLIGHT_ENABLE
const uint8_t RGBLED_BREATHING_INTERVALS[] PROGMEM = {100, 30, 5, 1};

void keyboard_post_init_user(void) {
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
  // Init the LEDs to a static color
  setrgb(0, 0, 0, (LED_TYPE *)&led[0]);
  setrgb(0, 0, 0, (LED_TYPE *)&led[1]);
  setrgb(0, 0, 0, (LED_TYPE *)&led[2]);
  rgblight_set();
}

uint32_t layer_state_set_keymap(uint32_t state){
  uint8_t led0r = 0; uint8_t led0g = 0; uint8_t led0b = 0;
  uint8_t led1r = 0; uint8_t led1g = 0; uint8_t led1b = 0;
  if (layer_state_cmp(state, _NUM_SYM)) {
    led0r = 25;
    led0g = 25;
  }
  if (layer_state_cmp(state, _NAV)) {
    led1g = 25;
    led1b = 25;
  }

  if (layer_state_cmp(state, _FKEY)) {
    led0b = 25;
    led0r = 25;
    led1b = 25;
    led1r = 25;
  }
  
  setrgb(led0r, led0g, led0b, (LED_TYPE *)&led[0]);
  setrgb(led1r, led1g, led1b, (LED_TYPE *)&led[1]);
  rgblight_set();

  return state;
}

bool led_update_kb(led_t led_state){
  if(led_state.caps_lock){
    rgblight_set_effect_range(2, 1);
    rgblight_sethsv_noeeprom(180, 200, 150);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_set();
  } else{
    rgblight_set_effect_range(2, 1);
    rgblight_sethsv_noeeprom(180, 200, 0);
    rgblight_set();
  }
  return true;
}
#endif //RGBLIGHT_ENABLE
