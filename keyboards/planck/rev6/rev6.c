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

void draw_ui(void) {
  clear_buffer();
  draw_string(0, 2, "LAYER", PIXEL_ON, NORM, 0);
  draw_rect_filled_soft(32, 0, 11, 11, PIXEL_ON, NORM);
  draw_char(35, 2, layer + 0x30, PIXEL_ON, XOR, 0);

  // for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
  //   for (uint8_t y = 0; y < MATRIX_COLS; y++) {
  //     if (x < 4)
  //       draw_pixel(0 + y, 11 + x, (matrix_get_row(x) & (1 << y)) > 0, NORM);
  //     else
  //       draw_pixel(6 + y, 7 + x, (matrix_get_row(x) & (1 << y)) > 0, NORM);
  //   }
  // }

  uint8_t mods = get_mods();
  if (mods & MOD_LSFT) {
    draw_rect_filled_soft(0, 12, 5 + (1 * 6), 11, PIXEL_ON, NORM);
    draw_string(3, 14, "S", PIXEL_OFF, NORM, 0);
  } else {
    draw_string(3, 14, "S", PIXEL_ON, NORM, 0);
  }
  if (mods & MOD_LCTL) {
    draw_rect_filled_soft(10, 12, 5 + (1 * 6), 11, PIXEL_ON, NORM);
    draw_string(13, 14, "C", PIXEL_OFF, NORM, 0);
  } else {
    draw_string(13, 14, "C", PIXEL_ON, NORM, 0);
  }
  if (mods & MOD_LALT) {
    draw_rect_filled_soft(20, 12, 5 + (1 * 6), 11, PIXEL_ON, NORM);
    draw_string(23, 14, "A", PIXEL_OFF, NORM, 0);
  } else {
    draw_string(23, 14, "A", PIXEL_ON, NORM, 0);
  }
  if (mods & MOD_LGUI) {
    draw_rect_filled_soft(30, 12, 5 + (1 * 6), 11, PIXEL_ON, NORM);
    draw_string(33, 14, "G", PIXEL_OFF, NORM, 0);
  } else {
    draw_string(33, 14, "G", PIXEL_ON, NORM, 0);
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
