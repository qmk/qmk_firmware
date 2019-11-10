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
#include "flutterby.h"
#include "config.h"
#include "lib/lufa/LUFA/Drivers/Peripheral/TWI.h"
#include "matrix.h"
#include "print.h"
#include "timer.h"
#include "util.h"
#include "wait.h"
#include "pincontrol.h"
#include "mousekey.h"
#include "outputselect.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#endif
#include "suspend.h"
#ifdef ADAFRUIT_BLE_ENABLE
#include "adafruit_ble.h"
#endif
#include <util/atomic.h>
#include <string.h>

// The keyboard matrix is attached to the following pins:
// thumbstick X: A0 - PF7
// thumbstick Y: A1 - PF6
// row0: A2 - PF5
// row1: A3 - PF4
// row2: A4 - PF1
// row3: A5 - PF0
// col0-15:   sx1509
static const uint8_t row_pins[MATRIX_ROWS] = {F5, F4, F1, F0};
#if DEBOUNCING_DELAY > 0
static bool debouncing;
static matrix_row_t matrix_debouncing[MATRIX_ROWS];
#endif
/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];

// matrix power saving
#define MATRIX_POWER_SAVE       600000 // 10 minutes
static uint32_t matrix_last_modified;

#define ENABLE_BLE_MODE_LEDS 0

#ifdef DEBUG_MATRIX_SCAN_RATE
static uint32_t scan_timer;
static uint32_t scan_count;
#endif

static inline void select_row(uint8_t row) {
  uint8_t pin = row_pins[row];

  pinMode(pin, PinDirectionOutput);
  digitalWrite(pin, PinLevelLow);
}

static inline void unselect_row(uint8_t row) {
  uint8_t pin = row_pins[row];

  digitalWrite(pin, PinLevelHigh);
  pinMode(pin, PinDirectionInput);
}

static void unselect_rows(void) {
  for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
    unselect_row(x);
  }
}

#if 0
static void select_rows(void) {
  for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
    select_row(x);
  }
}
#endif

void matrix_power_down(void) {
#if defined(ADAFRUIT_BLE_ENABLE) && defined(AdafruitBlePowerPin)
  adafruit_ble_power_enable(false);
#elif defined(ADAFRUIT_BLE_ENABLE) && ADAFRUIT_BLE_ENABLE_MODE_LEDS
  adafruit_ble_set_mode_leds(false);
#endif
}

#include "LUFA/Drivers/Peripheral/ADC.h"

void matrix_power_up(void) {
  flutterby_led_enable(true);

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

#if defined(ADAFRUIT_BLE_ENABLE) && defined(AdafruitBlePowerPin)
  adafruit_ble_power_enable(true);
  adafruit_ble_enable_keyboard();
#elif defined(ADAFRUIT_BLE_ENABLE) && ADAFRUIT_BLE_ENABLE_MODE_LEDS
  adafruit_ble_set_mode_leds(true);
#endif

#ifdef MOUSEKEY_ENABLE
  // Turn on the ADC for reading the thumbstick
  ADC_Init(ADC_SINGLE_CONVERSION | ADC_PRESCALE_32);
  ADC_SetupChannel(6); // Y
  ADC_SetupChannel(7); // X
#endif
  flutterby_blink_led(3);
}

void matrix_init(void) {
  TWI_Init(TWI_BIT_PRESCALE_1, TWI_BITLENGTH_FROM_FREQ(1, 400000));
  sx1509_init();

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

  current_matrix[current_row] = sx1509_read();

  unselect_row(current_row);

  return last_row_value != current_matrix[current_row];
}

static uint8_t matrix_scan_raw(void) {
  if (!sx1509_make_ready()) {
    return 0;
  }

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

#ifdef MOUSEKEY_ENABLE
static enum ThumbStickMode thumbstick_mode = ThumbStickMovesPointer;

enum ThumbStickMode flutterby_thumbstick_get_mode(void) {
  return thumbstick_mode;
}

void flutterby_thumbstick_set_mode(enum ThumbStickMode mode) {
  if (thumbstick_mode == mode) {
    return;
  }
  thumbstick_mode = mode;

  // Clear state to avoid getting stuck if the mode is changed
  // while the stick is not centered
  mousekey_set_xyvh(0, 0, 0, 0);
  mousekey_send();
}


#define StickMax 832
#define StickMin 160
#define StickCenter 512
#define StickSlop 64  // Dead band around the middle

// Take an input in the range 0-1024 and return a value in the
// range -127 to 127.
// [0   160    512     832    1024]
//      [-127    0     127]
static int8_t map_value(int32_t v) {
  v -= StickCenter;

  int sign = 1;
  if (v < 0) {
    sign = -1;
    v = -v;
  }

  if (v < StickSlop) {
    // It's within the dead band, so treat it as zero
    return 0;
  }


  int32_t maximum = thumbstick_mode == ThumbStickMovesPointer
                       ? mk_max_speed
                       : mk_wheel_max_speed;
  //dprintf("v=%d, max=%d product=%d\n", (int)v, (int)maximum, (int)(v * maximum));
  return (sign * maximum * v) / 320;
}

static void thumbstick_read(uint8_t chanmask, int8_t *value, int8_t *last_value,
                            bool *dirty) {
  *value = map_value(ADC_GetChannelReading(ADC_REFERENCE_AVCC | chanmask));

  if (*value != *last_value) {
    *last_value = *value;
    *dirty = true;
  }
}

void process_thumbstick(void) {
  // Cache the prior read to avoid over-reporting mouse movement
  static int8_t last_x = 0;
  static int8_t last_y = 0;
  int8_t x;
  int8_t y;

  if (where_to_send() == OUTPUT_BLUETOOTH) {
    // We currently send this too frequently, so disable it for
    // the moment to avoid accidentally choking up the hardware
    return;
  }

  bool dirty = false;
  thumbstick_read(ADC_CHANNEL7, &x, &last_x, &dirty);
  thumbstick_read(ADC_CHANNEL6, &y, &last_y, &dirty);

  if (dirty || x || y) {
    if (thumbstick_mode == ThumbStickMovesPointer) {
      mousekey_set_xyvh(x, -y, 0, 0);
    } else {
      mousekey_set_xyvh(0, 0, -y, x);
    }
    mousekey_send();
  }
}

#endif

uint8_t matrix_scan(void) {
  if (!matrix_scan_raw()) {
    return 0;
  }

  // Try to manage battery power a little better than the default scan.
  // If the user is idle for a while, turn off some things that draw
  // power.
#if 0
  if (timer_elapsed32(matrix_last_modified) > MATRIX_POWER_SAVE) {
    matrix_power_down();

    // Turn on all the rows; we're going to read the columns in
    // the loop below to see if we got woken up.
    select_rows();

    while (true) {
      suspend_power_down();

      // See if any keys have been pressed.
      if (!sx1509_read()) {
        continue;
      }

      // Wake us up
      matrix_last_modified = timer_read32();
      suspend_wakeup_init();
      matrix_power_up();

      // Wake the host up, if appropriate.
      if (USB_DeviceState == DEVICE_STATE_Suspended &&
          USB_Device_RemoteWakeupEnabled) {
        USB_Device_SendRemoteWakeup();
      }
      break;
    }
  }
#endif

#ifdef MOUSEKEY_ENABLE
  process_thumbstick();
#endif

  matrix_scan_quantum();
  return 1;
}

void matrix_print(void) {
  print("\nr/c 0123456789ABCDEF\n");

  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    phex(row);
    print(": ");
    print_bin_reverse16(matrix_get_row(row));
    print("\n");
  }
}

// Controls the Red LED attached to arduino pin 13
void flutterby_led_enable(bool on) {
  digitalWrite(C7, on ? PinLevelHigh : PinLevelLow);
}

void flutterby_blink_led(int times) {
  while (times--) {
    _delay_ms(50);
    flutterby_led_enable(true);
    _delay_ms(150);
    flutterby_led_enable(false);
  }
}
