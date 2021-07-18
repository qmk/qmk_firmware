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
    wait_ms(DEBOUNCING_DELAY);
    wait_ms(DEBOUNCING_DELAY);
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

const mbi_led g_mbi_leds[DRIVER_LED_TOTAL] = {
    { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 3 }, { 0, 4 }, { 0, 5 }, { 0, 6 }, { 0, 7 }, { 0, 8 }, { 0, 9 }, { 0, 10 }, { 0, 11 }, { 0, 12 }, { 0, 13 },
    { 1, 0 }, { 1, 1 }, { 1, 2 }, { 1, 3 }, { 1, 4 }, { 1, 5 }, { 1, 6 }, { 1, 7 }, { 1, 8 }, { 1, 9 }, { 1, 10 }, { 1, 11 }, { 1, 12 },
    { 2, 0 }, { 2, 1 }, { 2, 2 }, { 2, 3 }, { 2, 4 }, { 2, 5 }, { 2, 6 }, { 2, 7 }, { 2, 8 }, { 2, 9 }, { 2, 10 }, { 2, 11 }, { 2, 12 }, { 2, 13 },
    { 3, 0 }, { 3, 1 }, { 3, 2 }, { 3, 3 }, { 3, 4 }, { 3, 5 }, { 3, 6 }, { 3, 7 }, { 3, 8 }, { 3, 9 }, { 3, 10 }, { 3, 11 }, { 3, 12 },
    { 4, 0 }, { 4, 1 }, { 4, 2 },                     { 4, 5 },                                         { 4, 10 }, { 4, 11 }, { 4, 12 }, { 4, 13 }
};

//rgb_led g_rgb_leds[DRIVER_LED_TOTAL] = {
led_config_t g_led_config = { {
/**
 * RGB Layout
 * 
 *  0_0,  0_1,  0_2,  0_3,  0_4,  0_5,  0_6,  0_7,  0_8,  0_9, 0_10, 0_11, 0_12, 0_13
 *  1_0,  1_1,  1_2,  1_3,  1_4,  1_5,  1_6,  1_7,  1_8,  1_9, 1_10, 1_11, 1_12, ----
 *  2_0,  2_1,  2_2,  2_3,  2_4,  2_5,  2_6,  2_7,  2_8,  2_9, 2_10, 2_11, 2_12, 2_13
 *  3_0,  3_1,  3_2,  3_3,  3_4,  3_5,  3_6,  3_7,  3_8,  3_9, 3_10, 3_11, 3_12, ----
 *  4_0,  4_1,  4_2,  ---,  ---,  4_5,  ---,  ---,  ---,  ---, 4_10, 4_11, 4_12, 4_13
 * 
 */
	// Key Matrix to LED Index
	{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 },
	{ 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, NO_LED },
	{ 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40 },
	{ 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, NO_LED, 53 },
	{ 54, 55, 56, NO_LED, NO_LED, 57, NO_LED, NO_LED, NO_LED, NO_LED, 58, 59, 60, 61 }
}, {
	// Esc, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, -, =, Backspace
	{ 0, 0 }, { 16, 0 }, { 32, 0 }, { 48, 0 }, { 64, 0 }, {80, 0 }, { 96, 0 }, { 112, 0 }, { 128, 0 }, { 144, 0 }, {160, 0 }, {176, 0 }, { 192, 0 }, { 224, 0 },
	// Tab, Q, W, E, R, T, Y, U, I, O, P, [, ]
	{ 0, 16 }, { 16, 16 }, { 32, 16 }, { 48, 16 }, { 64, 16 }, {80, 16 }, { 96, 16 }, { 112, 16 }, { 128, 16 }, { 144, 16 }, {160, 16 }, {176, 16 }, { 192, 16 },
	// Caps Lock, A, S, D, F, G, H, J, K, L, ;, ', #, Enter
	{ 0, 32 }, { 16, 32 }, { 32, 32 }, { 48, 32 }, { 64, 32 }, {80, 32 }, { 96, 32 }, { 112, 32 }, { 128, 32 }, { 144, 32 }, {160, 32 }, {176, 32 }, { 192, 32 }, { 224, 32 },
	// Shift, \, Z, X, C, V, B, N, M, ,, ., /, Shift
	{ 0, 48 }, { 16, 48 }, { 32, 48 }, { 48, 48 }, { 64, 48 }, {80, 48 }, { 96, 48 }, { 112, 48 }, { 128, 48 }, { 144, 48 }, {160, 48 }, {176, 48 }, { 224, 48 },
	// Ctrl, Win, Alt, Space, AltGr, Win, Fn, Ctrl
	{ 0, 64 }, { 16, 64 }, { 32, 64 }, {80, 64 }, {160, 64 }, {176, 64 }, { 192, 64 }, { 224, 64 }
}, {
	4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
	5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
	5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,
	5, 5, 5, 4, 5, 5, 5, 5
	
} }; 
	
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
