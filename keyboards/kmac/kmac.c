/* Copyright 2017-2019 Mathias Andersson <wraul@dbox.se>
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
#include "kmac.h"

#define CAPS_PIN B0
#define SCROLL_PIN E6
#define F_ROW_MASK 0b01
#define WASD_MASK 0b10

// Optional override functions below.
// You can leave any or all of these undefined.
// These are only required if you want to perform custom actions.

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up
    setPinOutput(CAPS_PIN);
    setPinOutput(SCROLL_PIN);

    matrix_init_user();
}

/*

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

*/

/* LED pin configuration
 * Scroll Lock: Low PE6
 * Caps Lock: Low PB0
 */
void led_set_kb(uint8_t usb_led) {
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        writePinLow(CAPS_PIN);
    } else {
        writePinHigh(CAPS_PIN);
    }

    if (IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK)) {
        writePinLow(SCROLL_PIN);
    } else {
        writePinHigh(SCROLL_PIN);
    }

    led_set_user(usb_led);
}

void backlight_init_ports(void) {
    setPinOutput(B1);
    setPinOutput(B2);
    setPinOutput(B3);
    setPinOutput(B4);
    setPinOutput(D7);
}

/* Backlight pin configuration
 * F-row: High PB1
 * W: Low PB4
 * A: Low PB2
 * S: Low PB3
 * D: Low PD7
 */
void backlight_set(uint8_t level) {
    // F-row
    if (level & F_ROW_MASK) {
        writePinHigh(B1);
    } else {
        writePinLow(B1);
    }

    // WASD
    if (level & WASD_MASK) {
        writePinLow(B2);
        writePinLow(B3);
        writePinLow(B4);
        writePinLow(D7);
    } else {
        writePinHigh(B2);
        writePinHigh(B3);
        writePinHigh(B4);
        writePinHigh(D7);
    }
}
