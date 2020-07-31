/* Copyright 2020 kuenhlee
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
#ifndef TKL_DURGOD_K320
#error TKL_DURGOD_K320 not defined, recheck config.h
#endif

#include "durgod_k320.h"
#include "bootloader_defs.h"

#define LED_CAPS_LOCK   C9
#define LED_SCROLL_LOCK A8
#define LED_WIN_LOCK    A9
#define LED_MR_LOCK     A10

/* Function Prototype */
void off_all_leds(void);

/* Private Functions */

void off_all_leds(void) {
  writePinHigh(LED_CAPS_LOCK);
  writePinHigh(LED_SCROLL_LOCK);
  writePinHigh(LED_WIN_LOCK);
  writePinHigh(LED_MR_LOCK);
}

void bootmagic_lite(void) {
    matrix_scan();
    wait_ms(DEBOUNCE * 3u);
    matrix_scan();

    if (matrix_get_row(BOOTMAGIC_LITE_ROW) & (1u << BOOTMAGIC_LITE_COLUMN)) {
      // Jump to bootloader.
      bootloader_jump();
    }
}

void matrix_init_kb(void) {
  // put your keyboard start-up code here
  // runs once when the firmware starts up
  led_init_ports();
	bootmagic_lite();
  off_all_leds();
  matrix_init_user();
}

void matrix_scan_kb(void) {
  // put your looping keyboard code here
  // runs every cycle (a lot)

  matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  // put your per-action keyboard code here
  // runs for every action, just before processing by the firmware
  
  return process_record_user(keycode, record);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);

    if (res) {
        writePin(LED_CAPS_LOCK, !led_state.caps_lock);
        writePin(LED_SCROLL_LOCK, !led_state.scroll_lock);
    }

    return res;
}

void led_init_ports(void) {
  setPinOutput(LED_CAPS_LOCK);
  writePinLow(LED_CAPS_LOCK);
  setPinOutput(LED_SCROLL_LOCK);
  writePinLow(LED_SCROLL_LOCK);
  setPinOutput(LED_WIN_LOCK);
  writePinLow(LED_WIN_LOCK);
  setPinOutput(LED_MR_LOCK);
  writePinLow(LED_MR_LOCK);
}
