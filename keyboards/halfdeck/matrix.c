/*
Copyright 2016-2018 Wez Furlong

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
#if defined(__AVR__)
#include <avr/io.h>
#endif
#include <stdbool.h>

#include "debug.h"
#include "halfdeck.h"
#include "config.h"
#include "i2c.h"
#include "matrix.h"
#include "mousekey.h"
#include "print.h"
#include "timer.h"
#include "util.h"
#include "wait.h"
//#include "pincontrol.h"
#include "mousekey.h"
//#include "outputselect.h"
#include "lufa.h"
#include "suspend.h"
#include <util/atomic.h>
#include <string.h>
#if TOUCHPAD_IS_CIRQUE
#include "pinnacle.h"
#else
#include "proxsense.h"
#endif

// row0   a2   PF5
// row1   a3   PF4
// row4   a4   PF1
// row3   a5   PF0
// row2   0/rx PD2
// cs     1/tx PD3
// col0   13   PC7
// col2   12   PD6
// col4   11   PB7
// col5   10   PB6
// col3   9    PB5
// col1   6    PD7
// row5   5    PC6


#define DEBOUNCING_DELAY 5

static const uint8_t row_pins[] = {F5, F4, D2, F0, F1, C6};
static const uint8_t col_pins[] = {C7, D7, D6, B5, B7, B6};
#if DEBOUNCING_DELAY > 0
static bool debouncing;
static matrix_row_t matrix_debouncing[MATRIX_ROWS];
#endif
/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];

// matrix power saving
static uint32_t matrix_last_modified;

#ifdef DEBUG_MATRIX_SCAN_RATE
static uint32_t scan_timer;
static uint32_t scan_count;
#endif

#if ENABLE_TOUCHPAD
static bool trackpad_up = false;
static uint16_t retry_trackpad = 0;
static bool trackpad_last_empty = false;
#endif

static inline void select_row(uint8_t row) {
  uint8_t pin = row_pins[row];

  setPinOutput(pin);
  writePinLow(pin);
  sx1509_select_row(row);
}

static inline void unselect_row(uint8_t row) {
  uint8_t pin = row_pins[row];

  writePinHigh(pin);
  setPinInput(pin);
}

static void unselect_rows(void) {
  sx1509_unselect_rows();
  for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
    unselect_row(x);
  }
}

void matrix_power_down(void) {
}

void matrix_power_up(void) {
  halfdeck_led_enable(true);

#if ENABLE_TOUCHPAD
  if (!trackpad_up) {
    trackpad_up = trackpad_init();
  }
#endif

  unselect_rows();

  memset(matrix, 0, sizeof(matrix));
#if DEBOUNCING_DELAY > 0
  memset(matrix_debouncing, 0, sizeof(matrix_debouncing));
#endif

  matrix_last_modified = timer_read32();
#ifdef DEBUG_MATRIX_SCAN_RATE
  scan_timer = timer_read32();
  scan_count = 0;
#endif

  halfdeck_blink_led(3);
}

void matrix_init(void) {
  twi_init(200000UL);
  sx1509_init();

  for (uint8_t col = 0; col < MATRIX_COLS/2; col++) {
    setPinInput(col_pins[col]);
    writePinHigh(col_pins[col]); // enable pullup
  }

  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    setPinOutput(row_pins[row]);
    writePinHigh(row_pins[row]);
  }

  matrix_power_up();
}

bool matrix_is_on(uint8_t row, uint8_t col) {
  return (matrix[row] & ((matrix_row_t)1 << col));
}

matrix_row_t matrix_get_row(uint8_t row) { return matrix[row]; }

static bool read_cols_on_row(matrix_row_t current_matrix[],
                             uint8_t current_row) {
  // Store last value of row prior to reading
  matrix_row_t last_row_value = current_matrix[current_row];

  // Select row and wait for row selection to stabilize
  select_row(current_row);
  _delay_us(30);

  uint16_t bits = 0;

  // Read the columns from the LHS
  for (uint8_t col = 0; col < MATRIX_COLS/2; col++) {
    if (!readPin(col_pins[col])) {
      bits |= 1 << (col + 6);
    }
  }

  // Read the columns from the LHS
  bits |= sx1509_read_b(current_row);

  current_matrix[current_row] = bits;

  unselect_row(current_row);

  return last_row_value != current_matrix[current_row];
}

static uint8_t matrix_scan_raw(void) {
#if 0
  debug_matrix = true;
  debug_keyboard = true;
#endif
  sx1509_make_ready();

  for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
    bool matrix_changed = read_cols_on_row(
#if DEBOUNCING_DELAY > 0
        matrix_debouncing,
#else
        matrix,
#endif
        current_row);

    if (matrix_changed) {
#if DEBOUNCING_DELAY > 0
      debouncing = true;
#endif
      matrix_last_modified = timer_read32();
    }
  }

#ifdef DEBUG_MATRIX_SCAN_RATE
  scan_count++;

  uint32_t timer_now = timer_read32();
  if (TIMER_DIFF_32(timer_now, scan_timer)>1000) {
    print("matrix scan frequency: ");
    pdec(scan_count);
    print("\n");

    scan_timer = timer_now;
    scan_count = 0;
  }
#endif

#if DEBOUNCING_DELAY > 0
  if (debouncing &&
      (timer_elapsed32(matrix_last_modified) > DEBOUNCING_DELAY)) {
    memcpy(matrix, matrix_debouncing, sizeof(matrix));
    debouncing = false;
  }
#endif

  return 1;
}

#if ENABLE_TOUCHPAD
void process_trackpad(void) {
  struct TrackpadData data;

  // If we failed to initialize the trackpad at the start it
  // could be either that the trackpad is not installed, or
  // possibly that the TRRS cable connecting the two halves
  // was not plugged or was too long.  Rather than spinning
  // forever on startup, try to re-init the trackpad every
  // so often.
  if (!trackpad_up) {
    if (retry_trackpad--) {
      return;
    }

    trackpad_up = trackpad_init();
    if (!trackpad_up) {
      retry_trackpad = 1000;
      return;
    }
  }

  if (!trackpad_get_data(&data)) {
    mousekey_clear();
    return;
  }

  struct TrackpadData empty;
  memset(&empty, 0, sizeof(empty));
  // is this is an empty record?
  if (memcmp(&empty, &data, sizeof(data)) == 0) {
    if (trackpad_last_empty) {
      // We sent one last time, so there is no need to update
      // and flush (incurring latency overhead) this time
      return;
    }
    trackpad_last_empty = true;
  } else {
    trackpad_last_empty = false;
  }

#if 1
  // Feed the touchpad data into the mouse report
#if TOUCHPAD_IS_CIRQUE
  mousekey_set_xyvh(data.xDelta, -data.yDelta, data.wheel, 0);
#else
  mousekey_set_xyvh(data.xDelta, -data.yDelta, data.yWheel, data.xWheel);
#endif
  if (data.buttons & 1) {
    mousekey_on(KC_MS_BTN1);
  } else {
    mousekey_off(KC_MS_BTN1);
  }
  if (data.buttons & 2) {
    mousekey_on(KC_MS_BTN2);
  } else {
    mousekey_off(KC_MS_BTN2);
  }
  if (data.buttons & 4) {
    mousekey_on(KC_MS_BTN3);
  } else {
    mousekey_off(KC_MS_BTN3);
  }

  // and ensure that the host has sampled this before we continue,
  // as we can potentially update our state more frequently than
  // the host will poll us.
  mousekey_send();
#endif
}
#endif

uint8_t matrix_scan(void) {
#if ENABLE_TOUCHPAD
  process_trackpad();
#endif
  if (!matrix_scan_raw()) {
    return 0;
  }

  matrix_scan_kb();
  return 1;
}

void matrix_print(void) {
  print("\nr/c 0123456789ABCDEF\n");

  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    print_hex8(row);
    print(": ");
    print_bin_reverse16(matrix_get_row(row));
    print("\n");
  }
}

// Controls the Red LED attached to arduino pin 13
void halfdeck_led_enable(bool on) {
  // C7 (pin 13) is used as a column input, so this is turned off
#if 0
  digitalWrite(C7, on ? PinLevelHigh : PinLevelLow);
#endif
}

void halfdeck_blink_led(int times) {
#if 0
  while (times--) {
    _delay_ms(50);
    halfdeck_led_enable(true);
    _delay_ms(150);
    halfdeck_led_enable(false);
  }
#endif
}
