#include "rgbmatrix.h"

/*
Achieves the following
- layer tap key indicator when we are in layer
- Caps lock and scroll lock indicators when activated
- dpad backlight while in game mode
- mouse button backlight when in mouse layer
- modifier indicators when activated
- default layer indicator

Color preview

( 0, RGB_AZURE);
( 1, RGB_BLACK);
( 2, RGB_BLUE);
( 3, RGB_CHARTREUSE);
( 4, RGB_CORAL);
( 5, RGB_CYAN);
( 6, RGB_GOLD);
( 7, RGB_GOLDENROD);
( 8, RGB_GREEN);
( 9, RGB_MAGENTA);
( 10, RGB_ORANGE);
( 11, RGB_PINK);
( 14, RGB_PURPLE);
( 13, RGB_RED);
( 12, RGB_SPRINGGREEN);
( 32, RGB_TEAL);
( 29, RGB_TURQUOISE);
( 24, RGB_WHITE);
( 23, RGB_YELLOW);
*/



bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max){

  uint8_t current_layer = get_highest_layer(layer_state);
  uint8_t current_default_layer = get_highest_layer(default_layer_state);
  uint8_t current_mod = get_mods();

#if defined(ONESHOT_ENABLE)
  uint8_t current_osm = get_oneshot_mods();

  bool isShift = ( (current_mod & MOD_BIT(KC_LSFT)) || (current_osm & MOD_BIT(KC_LSFT)) );
  bool isCtrl  = ( (current_mod & MOD_BIT(KC_LCTL)) || (current_osm & MOD_BIT(KC_LCTL)) );
  bool isAlt   = ( (current_mod & MOD_BIT(KC_LALT)) || (current_osm & MOD_BIT(KC_LALT)) );
  bool isGUI   = ( (current_mod & MOD_BIT(KC_LGUI)) || (current_osm & MOD_BIT(KC_LGUI)) );
#else
  bool isShift = (current_osm & MOD_BIT(KC_LSFT));
  bool isCtrl  = (current_osm & MOD_BIT(KC_LCTL));
  bool isAlt   = (current_osm & MOD_BIT(KC_LALT));
  bool isGUI   = (current_osm & MOD_BIT(KC_LGUI));
#endif //ONESHOT_ENABLE


  switch(current_layer) {

    case _NUMBER:
      rgb_matrix_set_color(LED_NUMBER, RGB_AZURE);
      break;

    case _NAVIGATION:
      rgb_matrix_set_color(LED_NAVIGATION, RGB_AZURE);
      break;

    case _SYMBOL:
      rgb_matrix_set_color(LED_NUMBER, RGB_PURPLE);
      rgb_matrix_set_color(LED_NAVIGATION, RGB_PURPLE);
      break;

    case _CONFIG:
      rgb_matrix_set_color(LED_CONFIG_L, RGB_AZURE);
      rgb_matrix_set_color(LED_CONFIG_R, RGB_AZURE);

      switch (current_default_layer) {
        
        case _DEFAULT_LAYER_1:
          rgb_matrix_set_color(LED_QWERTY, RGB_PURPLE);
          break;
        
        case _DEFAULT_LAYER_2:
          rgb_matrix_set_color(LED_COLEMAKDH, RGB_PURPLE);
          break;
        
        case _DEFAULT_LAYER_3:
          rgb_matrix_set_color(LED_GAME, RGB_PURPLE);
          break;
      }
      break;

    case _MOUSE:
      rgb_matrix_set_color(LED_MOUSE, RGB_AZURE);
      
      rgb_matrix_set_color(LED_MOUSE_LB1, RGB_CORAL);
      rgb_matrix_set_color(LED_MOUSE_LB2, RGB_CORAL);
      rgb_matrix_set_color(LED_MOUSE_LB3, RGB_CORAL);

      rgb_matrix_set_color(LED_MOUSE_RB1, RGB_CORAL);
      rgb_matrix_set_color(LED_MOUSE_RB2, RGB_CORAL);
      rgb_matrix_set_color(LED_MOUSE_RB3, RGB_CORAL);
      rgb_matrix_set_color(LED_MOUSE_RB4, RGB_CORAL);
      rgb_matrix_set_color(LED_MOUSE_RB5, RGB_CORAL);
      break;

    case _GAMENUMBER:
      rgb_matrix_set_color(LED_GAMENUMBER, RGB_AZURE);
      break;

    default:
      switch (current_default_layer) {
        case _DEFAULT_LAYER_1:
        case _DEFAULT_LAYER_2:
          break;
        
        case _DEFAULT_LAYER_3:
          rgb_matrix_set_color(LED_DPAD_L, RGB_CORAL);
          rgb_matrix_set_color(LED_DPAD_R, RGB_CORAL);
          rgb_matrix_set_color(LED_DPAD_U, RGB_CORAL);
          rgb_matrix_set_color(LED_DPAD_D, RGB_CORAL);
          break;
      }
      break;
  }

  if(isShift){
    rgb_matrix_set_color(LED_SHIFT_T, RGB_GOLDENROD);
    rgb_matrix_set_color(LED_SHIFT_L, RGB_GOLDENROD);
    rgb_matrix_set_color(LED_SHIFT_R, RGB_GOLDENROD);
  }

  if(isCtrl){
    rgb_matrix_set_color(LED_CTRL_L, RGB_CORAL);
    rgb_matrix_set_color(LED_CTRL_R, RGB_CORAL);
  }

  if(isAlt){
    rgb_matrix_set_color(LED_ALT_L, RGB_PINK);
    rgb_matrix_set_color(LED_ALT_R, RGB_PINK);
  }

  if(isGUI){
    rgb_matrix_set_color(LED_GUI_L, RGB_WHITE);
    rgb_matrix_set_color(LED_GUI_R, RGB_WHITE);
  }

  if (host_keyboard_led_state().caps_lock) {
    rgb_matrix_set_color(LED_CAPSLOCK, RGB_GOLDENROD);
  }

  if (host_keyboard_led_state().scroll_lock) {
    rgb_matrix_set_color(LED_SCRLOCK, RGB_GOLDENROD);
  }

#if defined(CAPS_WORD_ENABLE)  
  if (is_caps_word_on()) {
    rgb_matrix_set_color(LED_CAPSLOCK, RGB_ORANGE);
  }
#endif //CAPS_WORD_ENABLE

  return false;
}