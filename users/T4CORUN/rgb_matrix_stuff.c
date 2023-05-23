#include "rgb_matrix_stuff.h"

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max){

  switch(get_highest_layer(layer_state)) {
    case _NUMBER:
      rgb_matrix_set_color(LED_NUMBER, RGB_AZURE);
      break;
    case _NAVIGATION:
      rgb_matrix_set_color(LED_NAVIGATION, RGB_AZURE);
      for(uint8_t i=0; i < NUM_DPADKEYS; i++) {
        rgb_matrix_set_color(dpad_LED[i], RGB_PURPLE);
      }
      break;
    case _FUNCTION:
      rgb_matrix_set_color(LED_FUNCTION, RGB_AZURE);
      break;
    case _ADJUST:
      rgb_matrix_set_color(LED_ADJUST, RGB_AZURE);
      switch (get_highest_layer(default_layer_state)) {
        case _DEFAULT_LAYER_1:
          rgb_matrix_set_color(LED_QWERTY, RGB_GREEN);
          break;
        case _DEFAULT_LAYER_2:
          rgb_matrix_set_color(LED_COLEMAKDH, RGB_GREEN);
          break;
        case _DEFAULT_LAYER_3:
          rgb_matrix_set_color(LED_GAME, RGB_GREEN);
          break;
      }
      break;
    case _MOUSE:
      rgb_matrix_set_color(LED_MOUSE, RGB_AZURE);
      break;
    case _GAMENUMBER:
      rgb_matrix_set_color(LED_GAMENUMBER, RGB_AZURE);
      break;
    default:
      switch (get_highest_layer(default_layer_state)) {
        case _DEFAULT_LAYER_1:
        case _DEFAULT_LAYER_2:
          break;
        case _DEFAULT_LAYER_3:
          rgb_matrix_set_color(LED_GAME, RGB_GREEN);
          for(uint8_t i=0; i < NUM_DPADKEYS; i++) {
            rgb_matrix_set_color(dpad_LED[i], RGB_RED);
          }
          break;
      }
      break;
  }

  if (host_keyboard_led_state().caps_lock) {
    rgb_matrix_set_color(LED_CAPSLOCK, RGB_CYAN);
  } 
  
  if (host_keyboard_led_state().scroll_lock) {
    rgb_matrix_set_color(LED_SCRLOCK, RGB_CYAN);
  } 

  return false;
}


bool process_record_user_rgb_matrix(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case KC_LSFT:
    case SHFT_F:
    case SHFT_J:
    case SHFT_T:
    case SHFT_N: {
      if (record->event.pressed) {
        if (get_mods() & MOD_MASK_SHIFT) {
          for(uint8_t i=0; i < NUM_SHIFTKEYS; i++) {
            rgb_matrix_set_color(shift_LED[i], RGB_WHITE);
          }  
        }
      }
    }
  }
  return true;
}