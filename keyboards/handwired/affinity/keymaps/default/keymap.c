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
#define LIGHTSHOW_DELAY 150

#include "msgeq7.h"

enum layer { DEFAULT, RAISE };
enum custom_keycode { LED_MODE = SAFE_RANGE };
enum lightshow_pattern { LEVELMETER, LEVELMETER_PEAK, LEVELMETER2, LEVELMETER3, PARTY, PARTY2 };

enum lightshow_pattern current_pattern = LEVELMETER;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [DEFAULT] = LAYOUT(
    KC_7, KC_8, KC_9, KC_MINS,
    KC_4, KC_5, KC_6, KC_PLUS,
    KC_1, KC_2, KC_3, KC_ENT,
    KC_0, KC_DOT, KC_TAB, MO(RAISE)
  ),
  [RAISE] = LAYOUT(
    RESET, KC_NO, KC_NO, LED_MODE,
    KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
   case LED_MODE:
    if (record->event.pressed) {
      current_pattern = current_pattern == LEVELMETER ? (
        LEVELMETER_PEAK
      ) : current_pattern == LEVELMETER_PEAK ? (
        LEVELMETER2
      ) : current_pattern == LEVELMETER2 ? (
        LEVELMETER3
      ) : current_pattern == LEVELMETER3 ? (
        PARTY
      ) : current_pattern == PARTY ? (
        PARTY2
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

/* ---- utilities */

static inline int _map (int val, int sfrom, int sto, int dfrom, int dto, bool bound) {
  if (val < sfrom) return (bound ? 0 : dfrom);
  else if (val > sto) return (bound ? 0 : dto);
  else return (val - sfrom) * (dto - dfrom) / (sto - sfrom) + dfrom;
}

static inline float _exp_ave (int val, float ave, int window_size) {
  float alpha = (float)2 / (1 + (window_size));
  return val * alpha + ave * (1 - alpha);
}

static inline float _max (float a, float b) { return a > b ? a : b; }

#define THRESHOLD_WINDOW 30
bool _kick_detect (int *values) {
  static int lastvalue, threshold;

  threshold = _exp_ave(values[0] + values[1], threshold, THRESHOLD_WINDOW);

  /* if (values[0] + values[1] - lastvalue > THRESHOLD / 2) { */
  if (values[0] + values[1] - _max(threshold, lastvalue) > THRESHOLD / 3) {
    lastvalue = values[0] + values[1];
    return true;
  } else {
    lastvalue = values[0] + values[1];
    return false;
  }
}

/* ---- lightshow patterns */

/* 4-band levelmeter */
void process_lightshow_levelmeter (int *values, bool peak) {
  /* r1 */
  sethsv(80, 255, _map(values[0] + values[1], THRESHOLD * 2, 1023 * 2, 0, 96, peak), &led[3]);
  sethsv(80, 255, _map(values[2] + values[2], THRESHOLD * 2, 1023 * 2, 0, 96, peak), &led[2]);
  sethsv(80, 255, _map(values[3] + values[4], THRESHOLD * 2, 1023 * 2, 0, 96, peak), &led[1]);
  sethsv(80, 255, _map(values[5] + values[6], THRESHOLD * 2, 1023 * 2, 0, 96, peak), &led[0]);
  /* r2 */
  sethsv(100, 255, _map(values[0] + values[1], THRESHOLD, THRESHOLD * 2, 0, 96, peak), &led[7]);
  sethsv(100, 255, _map(values[2] + values[2], THRESHOLD, THRESHOLD * 2, 0, 96, peak), &led[6]);
  sethsv(100, 255, _map(values[3] + values[4], THRESHOLD, THRESHOLD * 2, 0, 96, peak), &led[5]);
  sethsv(100, 255, _map(values[5] + values[6], THRESHOLD, THRESHOLD * 2, 0, 96, peak), &led[4]);
  /* r3 */
  sethsv(120, 255, _map(values[0] + values[1], THRESHOLD / 2, THRESHOLD, 0, 96, peak), &led[11]);
  sethsv(120, 255, _map(values[2] + values[2], THRESHOLD / 2, THRESHOLD, 0, 96, peak), &led[10]);
  sethsv(120, 255, _map(values[3] + values[4], THRESHOLD / 2, THRESHOLD, 0, 96, peak), &led[9]);
  sethsv(120, 255, _map(values[5] + values[6], THRESHOLD / 2, THRESHOLD, 0, 96, peak), &led[8]);
  /* r4 */
  sethsv(140, 255, _map(values[0] + values[1], THRESHOLD / 4, THRESHOLD / 2, 0, 96, peak), &led[15]);
  sethsv(140, 255, _map(values[2] + values[2], THRESHOLD / 4, THRESHOLD / 2, 0, 96, peak), &led[14]);
  sethsv(140, 255, _map(values[3] + values[4], THRESHOLD / 4, THRESHOLD / 2, 0, 96, peak), &led[13]);
  sethsv(140, 255, _map(values[5] + values[6], THRESHOLD / 4, THRESHOLD / 2, 0, 96, peak), &led[12]);
}

/* 4-band levelmeter x 2 */
void process_lightshow_levelmeter2 (int *values, bool peak) {
  /* r1 */
  setrgb(
    _map(values[0], THRESHOLD / 8, THRESHOLD / 4, 0, 96, peak),
    0,
    _map(values[3], THRESHOLD, 1023, 0, 96, peak),
    &led[3]
  );
  setrgb(
    _map(values[0], THRESHOLD / 4, THRESHOLD / 2, 0, 96, peak),
    0,
    _map(values[3], THRESHOLD / 2, THRESHOLD, 0, 96, peak),
    &led[2]
  );
  setrgb(
    _map(values[0], THRESHOLD / 2, THRESHOLD, 0, 96, peak),
    0,
    _map(values[3], THRESHOLD / 4, THRESHOLD / 2, 0, 96, peak),
    &led[1]
  );
  setrgb(
    _map(values[0], THRESHOLD, 1023, 0, 96, peak),
    0,
    _map(values[3], THRESHOLD / 8, THRESHOLD / 4, 0, 96, peak),
    &led[0]
  );
  /* r2 */
  setrgb(
    _map(values[1], THRESHOLD / 8, THRESHOLD / 4, 0, 96, peak),
    0,
    _map(values[4], THRESHOLD, 1023, 0, 96, peak),
    &led[7]
  );
  setrgb(
    _map(values[1], THRESHOLD / 4, THRESHOLD / 2, 0, 96, peak),
    0,
    _map(values[4], THRESHOLD / 2, THRESHOLD, 0, 96, peak),
    &led[6]
  );
  setrgb(
    _map(values[1], THRESHOLD / 2, THRESHOLD, 0, 96, peak),
    0,
    _map(values[4], THRESHOLD / 4, THRESHOLD / 2, 0, 96, peak),
    &led[5]
  );
  setrgb(
    _map(values[1], THRESHOLD, 1023, 0, 96, peak),
    0,
    _map(values[4], THRESHOLD / 8, THRESHOLD / 4, 0, 96, peak),
    &led[4]
  );
  /* r3 */
  setrgb(
    _map(values[2], THRESHOLD / 8, THRESHOLD / 4, 0, 96, peak),
    0,
    _map(values[5], THRESHOLD, 1023, 0, 96, peak),
    &led[11]
  );
  setrgb(
    _map(values[2], THRESHOLD / 4, THRESHOLD / 2, 0, 96, peak),
    0,
    _map(values[5], THRESHOLD / 2, THRESHOLD, 0, 96, peak),
    &led[10]
  );
  setrgb(
    _map(values[2], THRESHOLD / 2, THRESHOLD, 0, 96, peak),
    0,
    _map(values[5], THRESHOLD / 4, THRESHOLD / 2, 0, 96, peak),
    &led[9]
  );
  setrgb(
    _map(values[2], THRESHOLD, 1023, 0, 96, peak),
    0,
    _map(values[5], THRESHOLD / 8, THRESHOLD / 4, 0, 96, peak),
    &led[8]
  );
  /* r4 */
  setrgb(
    _map(values[3], THRESHOLD / 8, THRESHOLD / 4, 0, 96, peak),
    0,
    _map(values[6], THRESHOLD, 1023, 0, 96, peak),
    &led[15]
  );
  setrgb(
    _map(values[3], THRESHOLD / 4, THRESHOLD / 2, 0, 96, peak),
    0,
    _map(values[6], THRESHOLD / 2, THRESHOLD, 0, 96, peak),
    &led[14]
  );
  setrgb(
    _map(values[3], THRESHOLD / 2, THRESHOLD, 0, 96, peak),
    0,
    _map(values[6], THRESHOLD / 4, THRESHOLD / 2, 0, 96, peak),
    &led[13]
  );
  setrgb(
    _map(values[3], THRESHOLD, 1023, 0, 96, peak),
    0,
    _map(values[6], THRESHOLD / 8, THRESHOLD / 4, 0, 96, peak),
    &led[12]
  );
}

/* 7-band small levelmeter */
void process_lightshow_levelmeter3 (int *values, bool peak) {
  /* r1 */
  sethsv(0, 255, _map(values[0], THRESHOLD / 2, 1023, 0, 96, peak), &led[3]);
  sethsv(40, 255, _map(values[1], THRESHOLD / 2, 1023, 0, 96, peak), &led[2]);
  sethsv(80, 255, _map(values[2], THRESHOLD / 2, 1023, 0, 96, peak), &led[1]);
  sethsv(120, 255, _map(values[3], THRESHOLD / 2, 1023, 0, 96, peak), &led[0]);
  /* r2 */
  sethsv(0, 255, _map(values[0], THRESHOLD / 8, THRESHOLD / 2, 0, 96, peak), &led[7]);
  sethsv(40, 255, _map(values[1], THRESHOLD / 8, THRESHOLD / 2, 0, 96, peak), &led[6]);
  sethsv(80, 255, _map(values[2], THRESHOLD / 8, THRESHOLD / 2, 0, 96, peak), &led[5]);
  sethsv(120, 255, _map(values[3], THRESHOLD / 8, THRESHOLD / 2, 0, 96, peak), &led[4]);
  /* r3 */
  sethsv(120, 255, _map(values[3], THRESHOLD / 2, 1023, 0, 96, peak), &led[11]);
  sethsv(160, 255, _map(values[4], THRESHOLD / 2, 1023, 0, 96, peak), &led[10]);
  sethsv(200, 255, _map(values[5], THRESHOLD / 2, 1023, 0, 96, peak), &led[9]);
  sethsv(240, 255, _map(values[6], THRESHOLD / 2, 1023, 0, 96, peak), &led[8]);
  /* r4 */
  sethsv(120, 255, _map(values[3], THRESHOLD / 8, THRESHOLD / 2, 0, 96, peak), &led[15]);
  sethsv(160, 255, _map(values[4], THRESHOLD / 8, THRESHOLD / 2, 0, 96, peak), &led[14]);
  sethsv(200, 255, _map(values[5], THRESHOLD / 8, THRESHOLD / 2, 0, 96, peak), &led[13]);
  sethsv(240, 255, _map(values[6], THRESHOLD / 8, THRESHOLD / 2, 0, 96, peak), &led[12]);
}

void process_lightshow_party (int *values) {
  static int hue;

  /* rotate hue iff a kick is detected */
  if (_kick_detect(values)) {
    hue = (hue + 199) % 256;
  }

  /* set brightness */
  int val = 0;
  for (int i = 0; i < 7; i++) {
    val += values[i] / (4 * 7); /* 7 * 1024 => 256 */
  }

  /* scroll old plots */
  for (int col = 0; col < 2; col++) {
    /* col0, col1 */
    for (int row = 3; row >= 0; row--) {
      LED_TYPE *src = &led[(row - 1) * 4 + col];
      setrgb(src->r, src->g, src->b, &led[row * 4 + col]);
    }
    /* col2, col3 */
    for (int row = 0; row < 3; row++) {
      LED_TYPE *src = &led[(row + 1) * 4 + (col + 2)];
      setrgb(src->r, src->g, src->b, &led[row * 4 + (col + 2)]);
    }
  }

  /* push new plots */
  for (int col = 0; col < 2; col++) {
    sethsv(hue, 255, val, &led[0 * 4 + col]);
    sethsv(hue, 255, val, &led[3 * 4 + (col + 2)]);
  }
}

void process_lightshow_party2 (int *values) {
  int blue = 0, red = 0, green = 0, kick = 0;

  for (int i = 0; i < 2; i++) blue += values[i] / (4 * 2 * 2);  /* 2 * 1024 => 128 */
  for (int i = 2; i < 4; i++) red += values[i] / (4 * 2 * 2);   /* 2 * 1024 => 128 */
  for (int i = 4; i < 7; i++) green += values[i] / (4 * 3 * 2); /* 3 * 1024 => 128 */
  kick = _kick_detect(values) ? 127 : 0;

  for(int row = 0; row < 4; row++) {
    if (row % 2 == 0) {
      setrgb(0, 0, blue, &led[row * 4 + 3]);
      setrgb(red, 0, 0, &led[row * 4 + 2]);
      setrgb(0, green, 0, &led[row * 4 + 1]);
      setrgb(kick, kick, kick, &led[row * 4 + 0]);
    } else {
      setrgb(0, 0, blue, &led[row * 4 + 0]);
      setrgb(red, 0, 0, &led[row * 4 + 1]);
      setrgb(0, green, 0, &led[row * 4 + 2]);
      setrgb(kick, kick, kick, &led[row * 4 + 3]);
    }
  }
}

int values[7];
void matrix_scan_user (void) {
  static int delay = 0;
  if (!delay) {
    msgeq7_read(values);
    if (current_pattern == LEVELMETER) {
      process_lightshow_levelmeter(values, false);
    } else if (current_pattern == LEVELMETER_PEAK) {
      process_lightshow_levelmeter(values, true);
    } else if (current_pattern == LEVELMETER2) {
      process_lightshow_levelmeter2(values, false);
    } else if (current_pattern == LEVELMETER3) {
      process_lightshow_levelmeter3(values, false);
    } else if (current_pattern == PARTY) {
      process_lightshow_party(values);
    } else if (current_pattern == PARTY2) {
      process_lightshow_party2(values);
    }
    ws2812_setleds(led, 16);
    delay = LIGHTSHOW_DELAY;
  } else {
    delay--;
  }
}
