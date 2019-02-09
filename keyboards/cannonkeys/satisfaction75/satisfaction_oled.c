#include "satisfaction75.h"
#include "micro_oled.h"

__attribute__ ((weak))
void draw_ui() {
  uint8_t hour = last_minute / 60;
  uint16_t minute = last_minute % 60;

  if(encoder_mode == ENC_MODE_CLOCK_SET){
    hour = hour_config;
    minute = minute_config;
  }

  bool is_pm = (hour / 12) > 0;
  hour = hour % 12;
  if (hour == 0){
    hour = 12;
  }
  char hour_str[2] = "";
  char min_str[2] = "";

  sprintf(hour_str, "%02d", hour);
  sprintf(min_str, "%02d", minute);


  clear_buffer();
  last_flush = timer_read();
  send_command(DISPLAYON);

  uint8_t mods = get_mods();

/* Layer indicator is 41 x 10 pixels */
#define LAYER_INDICATOR_X 0
#define LAYER_INDICATOR_Y 0

  draw_string(LAYER_INDICATOR_X + 1, LAYER_INDICATOR_Y + 2, "LAYER", PIXEL_ON, NORM, 0);
  draw_rect_filled_soft(LAYER_INDICATOR_X + 32, LAYER_INDICATOR_Y + 1, 9, 9, PIXEL_ON, NORM);
  draw_char(LAYER_INDICATOR_X + 34, LAYER_INDICATOR_Y + 2, layer + 0x30, PIXEL_ON, XOR, 0);

#define ENCODER_INDICATOR_X 45
#define ENCODER_INDICATOR_Y 0
  draw_string(ENCODER_INDICATOR_X + 1, ENCODER_INDICATOR_Y + 2, "ENC", PIXEL_ON, NORM, 0);
  draw_rect_filled_soft(ENCODER_INDICATOR_X + 22, ENCODER_INDICATOR_Y + 1, 3 + (3 * 6), 9, PIXEL_ON, NORM);
  switch(encoder_mode){
    default:
    case ENC_MODE_VOLUME:
      draw_string(ENCODER_INDICATOR_X + 24, ENCODER_INDICATOR_Y + 2, "VOL", PIXEL_ON, XOR, 0);
      break;
    case ENC_MODE_MEDIA:
      draw_string(ENCODER_INDICATOR_X + 24, ENCODER_INDICATOR_Y + 2, "MED", PIXEL_ON, XOR, 0);
      break;
    case ENC_MODE_SCROLL:
      draw_string(ENCODER_INDICATOR_X + 24, ENCODER_INDICATOR_Y + 2, "SCR", PIXEL_ON, XOR, 0);
      break;
    case ENC_MODE_BRIGHTNESS:
      draw_string(ENCODER_INDICATOR_X + 24, ENCODER_INDICATOR_Y + 2, "BRT", PIXEL_ON, XOR, 0);
      break;
    case ENC_MODE_BACKLIGHT:
      draw_string(ENCODER_INDICATOR_X + 24, ENCODER_INDICATOR_Y + 2, "BKL", PIXEL_ON, XOR, 0);
      break;
    case ENC_MODE_CLOCK_SET:
      draw_string(ENCODER_INDICATOR_X + 24, ENCODER_INDICATOR_Y + 2, "CLK", PIXEL_ON, XOR, 0);
      break;
  }

/* Matrix display is 19 x 9 pixels */
#define MATRIX_DISPLAY_X 0
#define MATRIX_DISPLAY_Y 18

  for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
    for (uint8_t y = 0; y < MATRIX_COLS; y++) {
      draw_pixel(MATRIX_DISPLAY_X + y + 2, MATRIX_DISPLAY_Y + x + 2,(matrix_get_row(x) & (1 << y)) > 0, NORM);
    }
  }
  draw_rect_soft(MATRIX_DISPLAY_X, MATRIX_DISPLAY_Y, 19, 9, PIXEL_ON, NORM);
  /* hadron oled location on thumbnail */
  draw_rect_filled_soft(MATRIX_DISPLAY_X + 14, MATRIX_DISPLAY_Y + 2, 3, 1, PIXEL_ON, NORM);
/*
  draw_rect_soft(0, 13, 64, 6, PIXEL_ON, NORM);
  draw_line_vert(encoder_value, 13, 6, PIXEL_ON, NORM);

*/

/* Mod display is 41 x 16 pixels */
#define MOD_DISPLAY_X 30
#define MOD_DISPLAY_Y 18

  if (mods & MOD_LSFT) {
    draw_rect_filled_soft(MOD_DISPLAY_X + 0, MOD_DISPLAY_Y, 5 + (1 * 6), 11, PIXEL_ON, NORM);
    draw_string(MOD_DISPLAY_X + 3, MOD_DISPLAY_Y + 2, "S", PIXEL_OFF, NORM, 0);
  } else {
    draw_string(MOD_DISPLAY_X + 3, MOD_DISPLAY_Y + 2, "S", PIXEL_ON, NORM, 0);
  }
  if (mods & MOD_LCTL) {
    draw_rect_filled_soft(MOD_DISPLAY_X + 10, MOD_DISPLAY_Y, 5 + (1 * 6), 11, PIXEL_ON, NORM);
    draw_string(MOD_DISPLAY_X + 13, MOD_DISPLAY_Y + 2, "C", PIXEL_OFF, NORM, 0);
  } else {
    draw_string(MOD_DISPLAY_X + 13, MOD_DISPLAY_Y + 2, "C", PIXEL_ON, NORM, 0);
  }
  if (mods & MOD_LALT) {
    draw_rect_filled_soft(MOD_DISPLAY_X + 20, MOD_DISPLAY_Y, 5 + (1 * 6), 11, PIXEL_ON, NORM);
    draw_string(MOD_DISPLAY_X + 23, MOD_DISPLAY_Y + 2, "A", PIXEL_OFF, NORM, 0);
  } else {
    draw_string(MOD_DISPLAY_X + 23, MOD_DISPLAY_Y + 2, "A", PIXEL_ON, NORM, 0);
  }
  if (mods & MOD_LGUI) {
    draw_rect_filled_soft(MOD_DISPLAY_X + 30, MOD_DISPLAY_Y, 5 + (1 * 6), 11, PIXEL_ON, NORM);
    draw_string(MOD_DISPLAY_X + 33, MOD_DISPLAY_Y + 2, "G", PIXEL_OFF, NORM, 0);
  } else {
    draw_string(MOD_DISPLAY_X + 33, MOD_DISPLAY_Y + 2, "G", PIXEL_ON, NORM, 0);
  }

/* Lock display is 23 x 21 */
#define LOCK_DISPLAY_X 100
#define LOCK_DISPLAY_Y 0

  if (led_capslock == true) {
    draw_rect_filled_soft(LOCK_DISPLAY_X + 0, LOCK_DISPLAY_Y, 5 + (3 * 6), 9, PIXEL_ON, NORM);
    draw_string(LOCK_DISPLAY_X + 3, LOCK_DISPLAY_Y +1, "CAP", PIXEL_OFF, NORM, 0);
  } else if (led_capslock == false) {
    draw_string(LOCK_DISPLAY_X + 3, LOCK_DISPLAY_Y +1, "CAP", PIXEL_ON, NORM, 0);
  }

  if (led_scrolllock == true) {
    draw_rect_filled_soft(LOCK_DISPLAY_X + 0, LOCK_DISPLAY_Y + 11, 5 + (3 * 6), 9, PIXEL_ON, NORM);
    draw_string(LOCK_DISPLAY_X + 3, LOCK_DISPLAY_Y + 11 +1, "SCR", PIXEL_OFF, NORM, 0);
  } else if (led_scrolllock == false) {
    draw_string(LOCK_DISPLAY_X + 3, LOCK_DISPLAY_Y + 11 +1, "SCR", PIXEL_ON, NORM, 0);
  }

#define TIME_DISPLAY_X 82
#define TIME_DISPLAY_Y 22
  draw_string(TIME_DISPLAY_X, TIME_DISPLAY_Y, hour_str, PIXEL_ON, NORM, 0);
  draw_string(TIME_DISPLAY_X + 11, TIME_DISPLAY_Y, ":", PIXEL_ON, NORM, 0);
  draw_string(TIME_DISPLAY_X + 15, TIME_DISPLAY_Y, min_str, PIXEL_ON, NORM, 0);
  if(is_pm){
    draw_string(TIME_DISPLAY_X + 27, TIME_DISPLAY_Y, "pm", PIXEL_ON, NORM, 0);
  } else{
    draw_string(TIME_DISPLAY_X + 27, TIME_DISPLAY_Y, "am", PIXEL_ON, NORM, 0);
  }

  send_buffer();
}
