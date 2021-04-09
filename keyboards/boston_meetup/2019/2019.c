/* Copyright 2019 ishtob
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "2019.h"
#include "qwiic.h"
#include "action_layer.h"
#include "haptic.h"

#ifdef RGB_MATRIX_ENABLE
#include "rgb_matrix.h"

led_config_t g_led_config = { {
  {   5, NO_LED, NO_LED,   0 },
  { NO_LED, NO_LED, NO_LED, NO_LED },
  {   4, NO_LED, NO_LED,   1 },
  {   3, NO_LED, NO_LED,   2 }
}, {
    { 188,  16 }, { 187,  48 }, { 149,  64 }, { 112,  64 }, {  37,  48 }, {  38,  16 }
}, {
    4, 4, 4, 4, 4, 4
} };
#endif

uint8_t *o_fb;

uint16_t counterst = 0;



#ifdef QWIIC_MICRO_OLED_ENABLE

/* screen off after this many milliseconds */
#include "timer.h"
#define ScreenOffInterval 60000 /* milliseconds */
static uint16_t last_flush;

volatile uint8_t led_numlock = false;
volatile uint8_t  led_capslock = false;
volatile uint8_t  led_scrolllock = false;

static uint8_t layer;
static bool queue_for_send = false;
static uint8_t encoder_value = 32;

__attribute__ ((weak))
void draw_ui(void) {
  clear_buffer();
  last_flush = timer_read();
  send_command(DISPLAYON);

/* Boston MK title is 55 x 10 pixels */
#define NAME_X 0
#define NAME_Y 0

  draw_string(NAME_X + 1, NAME_Y + 2, "BOSTON MK", PIXEL_ON, NORM, 0);

/* Layer indicator is 41 x 10 pixels */
#define LAYER_INDICATOR_X 60
#define LAYER_INDICATOR_Y 0

  draw_string(LAYER_INDICATOR_X + 1, LAYER_INDICATOR_Y + 2, "LAYER", PIXEL_ON, NORM, 0);
  draw_rect_filled_soft(LAYER_INDICATOR_X + 32, LAYER_INDICATOR_Y + 1, 9, 9, PIXEL_ON, NORM);
  draw_char(LAYER_INDICATOR_X + 34, LAYER_INDICATOR_Y + 2, layer + 0x30, PIXEL_ON, XOR, 0);

/* Matrix display is 12 x 12 pixels */
#define MATRIX_DISPLAY_X 8
#define MATRIX_DISPLAY_Y 16

  for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
    for (uint8_t y = 0; y < MATRIX_COLS; y++) {
      draw_pixel(MATRIX_DISPLAY_X + y + y + 2, MATRIX_DISPLAY_Y + x + x + 2,(matrix_get_row(x) & (1 << y)) > 0, NORM);
      draw_pixel(MATRIX_DISPLAY_X + y + y + 3, MATRIX_DISPLAY_Y + x + x + 2,(matrix_get_row(x) & (1 << y)) > 0, NORM);
      draw_pixel(MATRIX_DISPLAY_X + y + y + 2, MATRIX_DISPLAY_Y + x + x + 3,(matrix_get_row(x) & (1 << y)) > 0, NORM);
      draw_pixel(MATRIX_DISPLAY_X + y + y + 3, MATRIX_DISPLAY_Y + x + x + 3,(matrix_get_row(x) & (1 << y)) > 0, NORM);

    }
  }
  draw_rect_soft(MATRIX_DISPLAY_X, MATRIX_DISPLAY_Y, 12, 12, PIXEL_ON, NORM);
  /* hadron oled location on thumbnail */
  draw_rect_filled_soft(MATRIX_DISPLAY_X + 5, MATRIX_DISPLAY_Y + 2, 6, 2, PIXEL_ON, NORM);
/*
  draw_rect_soft(0, 13, 64, 6, PIXEL_ON, NORM);
  draw_line_vert(encoder_value, 13, 6, PIXEL_ON, NORM);

*/

/* Mod display is 41 x 16 pixels */
#define MOD_DISPLAY_X 60
#define MOD_DISPLAY_Y 20

  uint8_t mods = get_mods();
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

/* Lock display is 23 x 32 */
#define LOCK_DISPLAY_X 104
#define LOCK_DISPLAY_Y 0

  if (led_numlock == true) {
    draw_rect_filled_soft(LOCK_DISPLAY_X, LOCK_DISPLAY_Y, 5 + (3 * 6), 9, PIXEL_ON, NORM);
    draw_string(LOCK_DISPLAY_X + 3, LOCK_DISPLAY_Y + 1, "NUM", PIXEL_OFF, NORM, 0);
  } else if (led_numlock == false) {
    draw_string(LOCK_DISPLAY_X + 3, LOCK_DISPLAY_Y + 1, "NUM", PIXEL_ON, NORM, 0);
  }
  if (led_capslock == true) {
    draw_rect_filled_soft(LOCK_DISPLAY_X + 0, LOCK_DISPLAY_Y + 11, 5 + (3 * 6), 9, PIXEL_ON, NORM);
    draw_string(LOCK_DISPLAY_X + 3, LOCK_DISPLAY_Y + 11 +1, "CAP", PIXEL_OFF, NORM, 0);
  } else if (led_capslock == false) {
    draw_string(LOCK_DISPLAY_X + 3, LOCK_DISPLAY_Y + 11 +1, "CAP", PIXEL_ON, NORM, 0);
  }

  if (led_scrolllock == true) {
    draw_rect_filled_soft(LOCK_DISPLAY_X + 0, LOCK_DISPLAY_Y + 22, 5 + (3 * 6), 9, PIXEL_ON, NORM);
    draw_string(LOCK_DISPLAY_X + 3, LOCK_DISPLAY_Y + 22 +1, "SCR", PIXEL_OFF, NORM, 0);
  } else if (led_scrolllock == false) {
    draw_string(LOCK_DISPLAY_X + 3, LOCK_DISPLAY_Y + 22 +1, "SCR", PIXEL_ON, NORM, 0);
  }
  send_buffer();
}

void led_set_user(uint8_t usb_led) {
    if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
      if (led_numlock == false){led_numlock = true;}
    } else {
      if (led_numlock == true){led_numlock = false;}
    }
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
      if (led_capslock == false){led_capslock = true;}
    } else {
      if (led_capslock == true){led_capslock = false;}
    }
    if (IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK)) {
      if (led_scrolllock == false){led_scrolllock = true;}
    } else {
      if (led_scrolllock == true){led_scrolllock = false;}
    }
}

uint32_t layer_state_set_kb(uint32_t state) {
  state = layer_state_set_user(state);
  layer = biton32(state);
  queue_for_send = true;
  return state;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  queue_for_send = true;
  return process_record_user(keycode, record);
}

void encoder_update_kb(uint8_t index, bool clockwise) {
  encoder_value = (encoder_value + (clockwise ? 1 : -1)) % 64;
  queue_for_send = true;
}

#endif

void matrix_init_kb(void) {
  queue_for_send = true;
	matrix_init_user();
}

void matrix_scan_kb(void) {
if (queue_for_send) {
#ifdef QWIIC_MICRO_OLED_ENABLE
   draw_ui();
#endif
   queue_for_send = false;
  }
#ifdef QWIIC_MICRO_OLED_ENABLE
  if (timer_elapsed(last_flush) > ScreenOffInterval) {
  send_command(DISPLAYOFF);      /* 0xAE */
  }
#endif
  if (counterst == 0) {
    //testPatternFB(o_fb);
  }
  counterst = (counterst + 1) % 1024;
  //rgblight_task();
	matrix_scan_user();
}
