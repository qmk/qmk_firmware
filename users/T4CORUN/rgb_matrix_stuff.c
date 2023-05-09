#include "rgb_matrix_stuff.h"

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max){

  switch(get_highest_layer(layer_state)) {
    case _NUMBER:
      rgb_matrix_set_color(LED_NUMBER, RGB_AZURE);
      break;
    case _NAVIGATION:
      rgb_matrix_set_color(LED_NAVIGATION, RGB_AZURE);
      for(uint8_t i=0; i < NUM_LEDSPLIT; i++) {
        rgb_matrix_set_color(i, RGB_DARKORANGE);
      }
      for(uint8_t i=0; i < NUM_DPADKEYS; i++) {
        rgb_matrix_set_color(dpad_LED[i], RGB_AZURE);
      }
      break;
    case _FUNCTION:
      rgb_matrix_set_color(LED_FUNCTION, RGB_AZURE);
      break;
    case _ADJUST:
      rgb_matrix_set_color(LED_ADJUST, RGB_AZURE);
      break;
    case _MOUSE:
      for(uint8_t i=0; i < NUM_MOUSEKEYS; i++) {
        rgb_matrix_set_color(mouse_LED[i], RGB_AZURE);
      }
#   if defined(MOUSEKEY_ENABLE)
      for(uint8_t i=0; i < NUM_DPADKEYS; i++) {
        rgb_matrix_set_color(dpad_LED[i], RGB_AZURE);
      }
#   endif //MOUSEKEY_ENABLE
      break;
    case _GAMENUMBER:
      rgb_matrix_set_color(LED_GAMENUMBER, RGB_BLUE);
      break;
    default:
      switch (get_highest_layer(default_layer_state)) {
        case _DEFAULT_LAYER_1:
        case _DEFAULT_LAYER_2:
          break;
        case _DEFAULT_LAYER_3:
          rgb_matrix_set_color(LED_GAMENUMBER, RGB_BLUE);
          for(uint8_t i=0; i < NUM_DPADKEYS; i++) {
            rgb_matrix_set_color(dpad_LED[i], RGB_RED);
          }
          break;
      }
      break;
  }

  for(uint8_t i=0; i < NUM_OFFLED; i++) {
    rgb_matrix_set_color(off_LED[i], RGB_OFF);
  }

  if (host_keyboard_led_state().caps_lock) {
    rgb_matrix_set_color(LED_CAPSLOCK, RGB_CYAN);
  } 
  
  if (host_keyboard_led_state().scroll_lock) {
    rgb_matrix_set_color(LED_SCRLOCK, RGB_CYAN);
  } 

  return false;
}
