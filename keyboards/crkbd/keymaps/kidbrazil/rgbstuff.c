#include QMK_KEYBOARD_H
#include "enums.h"
// External vars from keymap
extern bool user_led_enabled;
extern int current_color;

// [RGB Matrix Helpers] ----------------------------------------------------//
// This function is set to limit the HUE's to just the ones I like and which
// best match the cases I 3D print for my boards.
void set_crkbd_color(int input_color) {
    if (user_led_enabled) {
       switch(input_color) {
          case _GREEN:
              rgb_matrix_set_color_all(RGB_GREEN);
              current_color = _GREEN;
              break;
          case _GOLD:
              rgb_matrix_set_color_all(RGB_GOLD);
              current_color = _GOLD;
              break;
          case _GOLDENROD:
              rgb_matrix_set_color_all(RGB_GOLDENROD);
              current_color = _GOLDENROD;
              break;
          case _RED:
              rgb_matrix_set_color_all(RGB_RED);
              current_color = _RED;
              break;
          case _PURPLE:
              rgb_matrix_set_color_all(RGB_PURPLE);
              current_color = _PURPLE;
              break;
          default:
              break;
       }
    }
}

int handle_crkbd_color_step( int step ) {
    int output_color = step;
    // Handle wrapping of out of bounds values
    if ( output_color + current_color < _GREEN ) {
        output_color = _GREEN;
    } else if ( output_color + current_color > _PURPLE ) {
        output_color = _PURPLE;
    } else {
        output_color = output_color + current_color;
    }
    return output_color;
}


