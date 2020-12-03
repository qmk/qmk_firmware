/* Copyright 2019 /u/KeepItUnder
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
#include "one2mini.h"

/**
 * @brief   Board-specific bootmagic code.
 * @details We want to avoid entering bootloader without holding two keys.
 *          In this case the Ducky originals - "D" and "L".
 *          These are D {2,3} and L {2,9}
 *          We also need to avoid debounce by scanning twice with delay.
 */
void bootmagic_lite(void) {
    matrix_scan();
    wait_ms(DEBOUNCE*2);
    matrix_scan();

    uint8_t valMatrixRow = 0U;

    valMatrixRow = matrix_get_row(2);

    if ( ( valMatrixRow & (1<<3) ) &&
      ( valMatrixRow & (1<<9) ) ) {
      // Jump to bootloader.
      bootloader_jump();
    }

    valMatrixRow = matrix_get_row(3);

    if ( ( valMatrixRow & (1<<2) ) &&
      ( valMatrixRow & (1<<3) ) ) {
      // Jump to bootloader.
      bootloader_jump();
    }
}

/**
 * @brief   RGB Matrix LED layout
 * @details We need a layout for ISO and ANSI
 */
#define USB_LED_CAPSLOCK_INDEX 28  /* Location of CAPS LOCK led in matrix */

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
	//bootmagic_lite();
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

void led_set_kb(uint8_t usb_led) {
	// put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

	led_set_user(usb_led);
}
