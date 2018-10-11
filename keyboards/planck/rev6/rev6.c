/* Copyright 2018 Jack Humbert <jack.humb@gmail.com>
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
#include "rev6.h"
#include "qwiic.h"
#include "action_layer.h"
#include "matrix.h"

#ifdef QWIIC_MICRO_OLED_ENABLE

static uint8_t layer;
static bool queue_for_send = false;
static uint8_t encoder_value = 32;

void draw_ui(void) {
  clear_buffer();
  draw_string(0, 2, "LAYER", PIXEL_ON, NORM, 0);
  draw_rect_filled_soft(32, 0, 11, 11, PIXEL_ON, NORM);
  draw_char(35, 2, layer + 0x30, PIXEL_ON, XOR, 0);

#define MATRIX_DISPLAY_X 46
#define MATRIX_DISPLAY_Y 1

  for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
    for (uint8_t y = 0; y < MATRIX_COLS; y++) {
      if (x < 4)
        draw_pixel(MATRIX_DISPLAY_X + 2 + y, MATRIX_DISPLAY_Y + 2 + x, (matrix_get_row(x) & (1 << y)) > 0, NORM);
      else
        draw_pixel(MATRIX_DISPLAY_X + 8 + y, MATRIX_DISPLAY_Y - 2 + x, (matrix_get_row(x) & (1 << y)) > 0, NORM);
    }
  }
  draw_rect_soft(MATRIX_DISPLAY_X, MATRIX_DISPLAY_Y, 16, 8, PIXEL_ON, NORM);


  draw_rect_soft(0, 13, 64, 6, PIXEL_ON, NORM);
  draw_line_vert(encoder_value, 13, 6, PIXEL_ON, NORM);


#define MOD_DISPLAY_X 0
#define MOD_DISPLAY_Y 22

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

  send_buffer();
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
#ifdef QWIIC_MICRO_OLED_ENABLE
  queue_for_send = true;
#endif
	matrix_init_user();
}

void matrix_scan_kb(void) {
#ifdef QWIIC_MICRO_OLED_ENABLE
  if (queue_for_send) {
   draw_ui();
   queue_for_send = false;
  }
#endif
	matrix_scan_user();
}

#ifdef QWIIC_JOYSTIIC_ENABLE
void joystiic_trigger_kb(uint8_t trigger, bool active) {
  switch (trigger) {
    case JOYSTIIC_LEFT: active ? register_code(KC_L) : unregister_code(KC_L); break;
    case JOYSTIIC_RIGHT: active ? register_code(KC_R) : unregister_code(KC_R); break;
    case JOYSTIIC_UP: active ? register_code(KC_U) : unregister_code(KC_U); break;
    case JOYSTIIC_DOWN: active ? register_code(KC_D) : unregister_code(KC_D); break;
    case JOYSTIIC_PRESS: active ? register_code(KC_P) : unregister_code(KC_P); break;
  }
}
#endif
