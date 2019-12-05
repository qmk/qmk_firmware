#include QMK_KEYBOARD_H
#include "tominabox1.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT_arrow_wrapper(
    __________________MINIVAN1_________________,
    __________________MINIVAN2_________________,
    __________________MINIVAN3_________________,
    __________________MINIVAN4_________________
  ),

  [_LOWER] = LAYOUT_arrow_wrapper(
    _________________LOWER_1___________________,
    _________________LOWER_2___________________,
    __________________MININUM3_________________,
    __________________MININUM4_________________
  ),

  [_RAISE] = LAYOUT_arrow_wrapper(
    ___________________NAV1____________________,
    ___________________NAV2____________________,
    ___________________RVAN_3__________________,
    ___________________RVAN_4__________________
  ),

  [_ADJUST] = LAYOUT_arrow_wrapper(
    ___________________ADJST1__________________,
    ___________________ADJST2__________________,
    ___________________ADJVAN3_________________,
    __________________MINIVAN4_________________
  ),

  [_FKEY] = LAYOUT_arrow_wrapper(
    ___________________FKEY1___________________,
    ___________________FKEY2___________________,
    ___________________FVAN_3__________________,
    __________________MINIVAN4_________________
  ),
};

const uint8_t RGBLED_BREATHING_INTERVALS[] PROGMEM = {100, 30, 5, 1};

void keyboard_post_init_user(void) {
  #ifdef RGBLIGHT_ENABLE
  // Set up RGB effects on _only_ the third LED (index 2)
  rgblight_set_effect_range(2, 1);
  // Set LED effects to breathing mode in a tealish blue color
  rgblight_sethsv_noeeprom(180, 200, 150);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);

  // Init the first two LEDs to a static color
  setrgb(0, 0, 0, (LED_TYPE *)&led[0]);
  setrgb(0, 0, 0, (LED_TYPE *)&led[1]);
  rgblight_set();
  #endif //RGBLIGHT_ENABLE
}

uint32_t layer_state_set_keymap(uint32_t state){
  #ifdef RGBLIGHT_ENABLE
  uint8_t led0r = 0; uint8_t led0g = 0; uint8_t led0b = 0;
  uint8_t led1r = 0; uint8_t led1g = 0; uint8_t led1b = 0;
  if (layer_state_cmp(state, _LOWER)) {
    led0r = 25;
    led0g = 25;
  }
  if (layer_state_cmp(state, _RAISE)) {
    led1g = 25;
    led1b = 25;
  }

  if (layer_state_cmp(state, _FKEY)) {
    led0b = 25;
    led0r = 25;
    led1b = 25;
    led1r = 25;
  }
  if (layer_state_cmp(state, _ADJUST)) {
    led1r = 0;
    led1b = 25;
  }
  setrgb(led0r, led0g, led0b, (LED_TYPE *)&led[0]);
  setrgb(led1r, led1g, led1b, (LED_TYPE *)&led[1]);
  rgblight_set();

  #endif //RGBLIGHT_ENABLE
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
