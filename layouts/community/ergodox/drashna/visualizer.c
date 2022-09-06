/*
Copyright 2017 Fred Sundvik

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "./simple_visualizer.h"
#include "util.h"
#include "drashna.h"
#include "rgblight_list.h"

#define LCD_COLOR_wrapper(...) LCD_COLOR(__VA_ARGS__)
// This function should be implemented by the keymap visualizer
// Don't change anything else than state->target_lcd_color and state->layer_text as that's the only thing
// that the simple_visualizer assumes that you are updating
// Also make sure that the buffer passed to state->layer_text remains valid until the previous animation is
// stopped. This can be done by either double buffering it or by using constant strings
static void get_visualizer_layer_and_color(visualizer_state_t* state) {

  switch(get_highest_layer(state->status.layer|default_layer_state)) {
    case _LOWER:
      state->layer_text = "Lower";
      state->target_lcd_color = LCD_COLOR_wrapper(HSV_GREEN);
      break;
    case _RAISE:
      state->layer_text = "Raise";
      state->target_lcd_color = LCD_COLOR_wrapper(HSV_YELLOW);
      break;
    case _ADJUST:
      state->layer_text = "Adjust";
      state->target_lcd_color = LCD_COLOR_wrapper(HSV_RED);
      break;
    case _MACROS:
      state->layer_text = "Macros";
      state->target_lcd_color = LCD_COLOR_wrapper(HSV_ORANGE);
      break;
    case _MEDIA:
      state->layer_text = "Media";
      state->target_lcd_color = LCD_COLOR_wrapper(HSV_CHARTREUSE);
      break;
    case _GAMEPAD:
      state->layer_text = "Game";
      state->target_lcd_color = LCD_COLOR_wrapper(HSV_ORANGE);
      break;
    case _QWERTY:
      state->layer_text = "QWERTY";
      state->target_lcd_color = LCD_COLOR_wrapper(HSV_CYAN);
      break;
    case _WORKMAN:
      state->layer_text = "Workman";
      state->target_lcd_color = LCD_COLOR_wrapper(HSV_GOLDENROD);
      break;
    case _DVORAK:
      state->layer_text = "Dvorak";
      state->target_lcd_color = LCD_COLOR_wrapper(HSV_SPRINGGREEN);
      break;
    case _COLEMAK:
      state->layer_text = "Colemak";
      state->target_lcd_color = LCD_COLOR_wrapper(HSV_MAGENTA);
      break;      break;
    default:
      state->layer_text = "NONE";
      state->target_lcd_color = LCD_COLOR_wrapper(HSV_RED);
      break;
  }
}
