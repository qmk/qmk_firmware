#include "layers.h"
#include "simple_visualizer.h"
#include "util.h"

static void get_visualizer_layer_and_color(visualizer_state_t *state) {
  uint8_t layer = biton32(state->status.layer);

  // Go from highest to lowest layer to get the right text/color combination.
  switch (layer) {
    // #AEB2F4 / hsv(65.71%, 28.69%, 95.69%)
    case FKEYS:
      // #F4AEDC / hsv(89.05%, 28.69%, 95.69%)
      state->layer_text       = "FUNCTION KEYS";
      state->target_lcd_color = LCD_COLOR(228, 73, 245);
      break;
    case US_1:
      // #F4B993 / hsv(6.53%, 39.75%, 95.69%)
      state->layer_text       = "QWERTY";
      state->target_lcd_color = LCD_COLOR(17, 102, 245);
      break;
    case NEO_6:
      // #F4E393 / hsv(13.75%, 39.75%, 95.69%)
      state->layer_text       = "NEO: 6";
      state->target_lcd_color = LCD_COLOR(35, 102, 245);
      break;
    case NEO_5:
      // #C6F493 / hsv(24.57%, 39.75%, 95.69%)
      state->layer_text       = "NEO: 5";
      state->target_lcd_color = LCD_COLOR(63, 102, 245);
      break;
    case NEO_4:
      // #8EEBC9 / hsv(43.91%, 39.57%, 92.16%)
      state->layer_text       = "NEO: 4";
      state->target_lcd_color = LCD_COLOR(112, 101, 189);
      break;
    case NEO_3:
      // #93D2F4 / hsv(55.84%, 39.75%, 95.69%)
      state->layer_text       = "NEO: 3";
      state->target_lcd_color = LCD_COLOR(143, 102, 245);
      break;
    default:
      // #EEEEEE / hsv(0%, 0%, 93%)
      state->layer_text       = "NEO: 1";
      state->target_lcd_color = LCD_COLOR(0, 0, 255);
      break;
  }
}
