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

rgb_led g_rgb_leds[DRIVER_LED_TOTAL] = {
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
    {{0|(0<<4)},    {0,  0}, 4},
    {{0|(1<<4)},    {16,  0}, 4},
    {{0|(2<<4)},    {32,  0}, 4},
    {{0|(3<<4)},    {48,  0}, 4},
    {{0|(4<<4)},    {64,  0}, 4},
    {{0|(5<<4)},    {80,  0}, 4},
	{{0|(6<<4)},    {96,  0}, 4},
    {{0|(7<<4)},    {112,  0}, 4},
    {{0|(8<<4)},    {128,  0}, 4},
    {{0|(9<<4)},    {144,  0}, 4},
    {{0|(10<<4)},   {160,  0}, 4},
    {{0|(11<<4)},   {176,  0}, 4},
    {{0|(12<<4)},   {192,  0}, 4},
    {{0|(13<<4)},   {224,  0}, 4},
    {{1|(0<<4)},    {0,  16}, 4},
    {{1|(1<<4)},    {16,  16}, 4},
    {{1|(2<<4)},    {32,  16}, 4},
    {{1|(3<<4)},    {48,  16}, 4},
    {{1|(4<<4)},    {64,  16}, 4},
    {{1|(5<<4)},    {80,  16}, 4},
	{{1|(6<<4)},    {96,  16}, 4},
    {{1|(7<<4)},    {112,  16}, 4},
    {{1|(8<<4)},    {128,  16}, 4},
    {{1|(9<<4)},    {144,  16}, 4},
    {{1|(10<<4)},   {160,  16}, 4},
    {{1|(11<<4)},   {176,  16}, 4},
    {{1|(12<<4)},   {192,  16}, 4},
    {{2|(0<<4)},    {0,  32}, 1},
    {{2|(1<<4)},    {16,  32}, 4},
    {{2|(2<<4)},    {32,  32}, 4},
    {{2|(3<<4)},    {48,  32}, 4},
    {{2|(4<<4)},    {64,  32}, 4},
    {{2|(5<<4)},    {80,  32}, 4},
    {{2|(6<<4)},    {96,  32}, 4},
    {{2|(7<<4)},    {112,  32}, 4},
    {{2|(8<<4)},    {128,  32}, 4},
    {{2|(9<<4)},    {144,  32}, 4},
    {{2|(10<<4)},   {160,  32}, 4},
    {{2|(11<<4)},   {176,  32}, 4},
    {{2|(12<<4)},   {192,  32}, 4},
	{{2|(13<<4)},   {224,  32}, 4},
    {{3|(0<<4)},    {0,  48}, 1},
    {{3|(1<<4)},    {16,  48}, 4},
    {{3|(2<<4)},    {32,  48}, 4},
    {{3|(3<<4)},    {48,  48}, 4},
    {{3|(4<<4)},    {64,  48}, 4},
    {{3|(5<<4)},    {80,  48}, 4},
    {{3|(6<<4)},    {96,  48}, 4},
    {{3|(7<<4)},    {112,  48}, 4},
    {{3|(8<<4)},    {128,  48}, 4},
    {{3|(9<<4)},    {144,  48}, 4},
    {{3|(10<<4)},   {160,  48}, 4},
    {{3|(11<<4)},   {176,  48}, 4},
    {{3|(13<<4)},   {224,  48}, 1},
    {{4|(0<<4)},    {0,  64}, 1},
    {{4|(1<<4)},    {16,  64}, 1},
    {{4|(2<<4)},    {32,  64}, 1},
    {{4|(5<<4)},    {80,  64}, 4},
    {{4|(10<<4)},   {160,  64}, 1},
    {{4|(11<<4)},   {176,  64}, 1},
    {{4|(12<<4)},   {192,  64}, 1},
    {{4|(13<<4)},   {224,  64}, 1},
};

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
