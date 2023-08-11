/* Copyright 2021 Chris Tanaka <https://github.com/christanaka>
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

#include "bongo_graphics.h"
#include QMK_KEYBOARD_H

#define _IDLE_FRAMES         5
#define _PREP_FRAMES         1
#define _TAP_FRAMES          2
#define _ANIM_BYTES          512   // Number of bytes in array (max is 1024)
#define _IDLE_FRAME_DURATION 175
#define _TAP_FRAME_DURATION  75
#define _PREP_TIMEOUT        750

enum anim_states
{
    Idle,
    Prep,
    Tap
};

static uint8_t anim_state = Idle;
static uint8_t anim_duration = _IDLE_FRAME_DURATION;
static uint32_t anim_timer = 0;

static uint8_t idle_frame = 0;
static uint8_t tap_frame = 0;

static uint32_t prep_timer = 0;

// Decompress and write a precompressed bitmap frame to the OLED.
// Documentation and python compression script available at:
// https://github.com/nullbitsco/squeez-o
#ifdef USE_OLED_BITMAP_COMPRESSION
static void oled_write_compressed_P(const char* input_block_map, const char* input_block_list) {
    uint16_t block_index = 0;
    for (uint16_t i = 0; i < NUM_OLED_BYTES; i++) {
        uint8_t bit          = i % 8;
        uint8_t map_index    = i / 8;
        uint8_t _block_map   = (uint8_t)pgm_read_byte_near(input_block_map + map_index);
        uint8_t nonzero_byte = (_block_map & (1 << bit));
        if (nonzero_byte) {
            const char data = (const char)pgm_read_byte_near(input_block_list + block_index++);
            oled_write_raw_byte(data, i);
        } else {
            const char data = (const char)0x00;
            oled_write_raw_byte(data, i);
        }
    }
}
#endif

static void animate(uint8_t x, uint8_t y) {
  oled_set_cursor(x, y);

  // Update frame
  switch (anim_state) {
    case Idle:
      idle_frame = (idle_frame + 1) % _IDLE_FRAMES;
      #ifdef USE_OLED_BITMAP_COMPRESSION
          oled_write_compressed_P(idle_block_map[abs(1 - idle_frame)], idle[abs(1 - idle_frame)]);
      #else
          oled_write_raw_P(idle[abs(1 - idle_frame)], sizeof(idle[abs(1 - idle_frame)]));
      #endif
      break;
    case Prep:
      #ifdef USE_OLED_BITMAP_COMPRESSION
          oled_write_compressed_P(prep_block_map[0], prep[0]);
      #else
          oled_write_raw_P(prep[0], sizeof(prep[0]));
      #endif
      break;
    case Tap:
      tap_frame = (tap_frame + 1) % _TAP_FRAMES;
      #ifdef USE_OLED_BITMAP_COMPRESSION
          oled_write_compressed_P(tap_block_map[abs(1 - tap_frame)], tap[abs(1 - tap_frame)]);
      #else
          oled_write_raw_P(tap[abs(1 - tap_frame)], sizeof(tap[abs(1 - tap_frame)]));
      #endif
      break;
    default:
      break;
  }
}

void bongo_render(uint8_t x, uint8_t y) {
  if (timer_elapsed32(anim_timer) > anim_duration) {
    anim_timer = timer_read32();
    animate(x, y);
  }

  if (anim_state == Prep && timer_elapsed32(prep_timer) > _PREP_TIMEOUT) {
    anim_state = Idle;
    anim_duration = _IDLE_FRAME_DURATION;
  }
}

void bongo_process_record(keyrecord_t *record) {
  if (record->event.pressed) {
    anim_state = Tap;
    anim_duration = _TAP_FRAME_DURATION;
  } else {
    if (anim_state == Tap) {
      anim_state = Prep;
      prep_timer = timer_read32();
    }
  }
}
