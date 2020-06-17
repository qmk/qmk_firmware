/* Copyright 2019 zk-phi
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
#include QMK_KEYBOARD_H

#define NOISE_FLOOR 50          /* 0 - 2048 */
#define THRESHOLD 800           /* 0 - 2048 */

#include "msgeq7.h"

enum layer { DEFAULT };
enum custom_keycode { LED_MODE = SAFE_RANGE };
enum lightshow_pattern { LEVELMETER, PARTY };

enum lightshow_pattern pattern = LEVELMETER;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [DEFAULT] = LAYOUT(
    KC_7, KC_8, KC_9, LED_MODE,
    KC_4, KC_5, KC_6, KC_PLUS,
    KC_1, KC_2, KC_3, KC_ENT,
    KC_0, KC_0, KC_DOT, RESET
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
   case LED_MODE:
    if (record->event.pressed) {
      pattern = pattern == LEVELMETER ? (
        PARTY
      ) : (
        LEVELMETER
      );
    }
    return false;
  }
  return true;
}

void keyboard_post_init_user (void) {
  msgeq7_init();
}

int _map (int val, int sfrom, int sto, int dfrom, int dto) {
  if (val < sfrom) return dfrom;
  else if (val > sto) return dto;
  else return (val - sfrom) * (dto - dfrom) / (sto - sfrom) + dfrom;
}

void process_lightshow_levelmeter (int *values) {
  /* r1 */
  sethsv(80, 255, _map(values[0] + values[0], THRESHOLD * 2, 1024 * 2, 0, 96), &led[3]);
  sethsv(80, 255, _map(values[1] + values[2], THRESHOLD * 2, 1024 * 2, 0, 96), &led[2]);
  sethsv(80, 255, _map(values[3] + values[4], THRESHOLD * 2, 1024 * 2, 0, 96), &led[1]);
  sethsv(80, 255, _map(values[5] + values[6], THRESHOLD * 2, 1024 * 2, 0, 96), &led[0]);
  /* r2 */
  sethsv(100, 255, _map(values[0] + values[0], THRESHOLD, THRESHOLD * 2, 0, 96), &led[7]);
  sethsv(100, 255, _map(values[1] + values[2], THRESHOLD, THRESHOLD * 2, 0, 96), &led[6]);
  sethsv(100, 255, _map(values[3] + values[4], THRESHOLD, THRESHOLD * 2, 0, 96), &led[5]);
  sethsv(100, 255, _map(values[5] + values[6], THRESHOLD, THRESHOLD * 2, 0, 96), &led[4]);
  /* r3 */
  sethsv(120, 255, _map(values[0] + values[0], THRESHOLD / 2, THRESHOLD, 0, 96), &led[11]);
  sethsv(120, 255, _map(values[1] + values[2], THRESHOLD / 2, THRESHOLD, 0, 96), &led[10]);
  sethsv(120, 255, _map(values[3] + values[4], THRESHOLD / 2, THRESHOLD, 0, 96), &led[9]);
  sethsv(120, 255, _map(values[5] + values[6], THRESHOLD / 2, THRESHOLD, 0, 96), &led[8]);
  /* r4 */
  sethsv(140, 255, _map(values[0] + values[0], THRESHOLD / 4, THRESHOLD / 2, 0, 96), &led[15]);
  sethsv(140, 255, _map(values[1] + values[2], THRESHOLD / 4, THRESHOLD / 2, 0, 96), &led[14]);
  sethsv(140, 255, _map(values[3] + values[4], THRESHOLD / 4, THRESHOLD / 2, 0, 96), &led[13]);
  sethsv(140, 255, _map(values[5] + values[6], THRESHOLD / 4, THRESHOLD / 2, 0, 96), &led[12]);
  /* flush */
  ws2812_setleds(led, 16);
}

void process_lightshow_party (int *values) {
  static int lastkickvalue, hue;

  if (values[0] + values[0] - lastkickvalue > THRESHOLD / 2) {
    hue = (hue + 199) % 256;
  }
  lastkickvalue = values[0] + values[0];

  int val = 0;
  for (int i = 0; i < 7; i++) {
    val += values[i] / (4 * 7); /* 7 * 1024 => 256 */
  }

  for (int col = 0; col < 2; col++) {
    /* c0, c1 */
    for (int row = 3; row >= 0; row--) {
      LED_TYPE *src = &led[(row - 1) * 4 + col];
      setrgb(src->r, src->g, src->b, &led[row * 4 + col]);
    }
    /* c2, c3 */
    for (int row = 0; row < 3; row++) {
      LED_TYPE *src = &led[(row + 1) * 4 + (col + 2)];
      setrgb(src->r, src->g, src->b, &led[row * 4 + (col + 2)]);
    }
  }
  for (int col = 0; col < 2; col++) {
    sethsv(hue, 255, val, &led[0 * 4 + col]);
    sethsv(hue, 255, val, &led[3 * 4 + (col + 2)]);
  }

  ws2812_setleds(led, 16);
}

int values[7];
void matrix_scan_user (void) {
  static int delay = 0;
  if (!delay) {
    msgeq7_read(values);
    if (pattern == LEVELMETER) {
      process_lightshow_levelmeter(values);
    } else if (pattern == PARTY) {
      process_lightshow_party(values);
    }
    delay = 150;
  } else {
    delay--;
  }
}
