/* Copyright 2018 Yiancar
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
#include "xelusrgb60.h"
#include "config.h"

const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, C1_1,   C3_2,   C4_2}, //A1
    {0, C1_2,   C2_2,   C4_3}, //A2
    {0, C1_3,   C2_3,   C3_3}, //A3
    {0, C1_4,   C2_4,   C3_4}, //A4
    {0, C1_5,   C2_5,   C3_5}, //A5
    {0, C1_6,   C2_6,   C3_6}, //A6
    {0, C1_7,   C2_7,   C3_7}, //A7
    {0, C1_8,   C2_8,   C3_8}, //A8
    {0, C9_1,   C8_1,   C7_1}, //A9
    {0, C9_2,   C8_2,   C7_2}, //A10
    {0, C9_3,   C8_3,   C7_3}, //A11
    {0, C9_4,   C8_4,   C7_4}, //A12
    {0, C9_5,   C8_5,   C7_5}, //A13
    {0, C9_6,   C8_6,   C7_6}, //A14
    {0, C9_7,   C8_7,   C6_6}, //A15
    {0, C9_8,   C7_7,   C6_7}, //A16

    {0, C1_9,   C3_10,  C4_10}, //B1
    {0, C1_10,  C2_10,  C4_11}, //B2
    {0, C1_11,  C2_11,  C3_11}, //B3
    {0, C1_12,  C2_12,  C3_12}, //B4
    {0, C1_13,  C2_13,  C3_13}, //B5
    {0, C1_14,  C2_14,  C3_14}, //B6
    {0, C1_15,  C2_15,  C3_15}, //B7
    {0, C1_16,  C2_16,  C3_16}, //B8
    {0, C9_9,   C8_9,   C7_9},  //B9
    {0, C9_10,  C8_10,  C7_10}, //B10
    {0, C9_11,  C8_11,  C7_11}, //B11
    {0, C9_12,  C8_12,  C7_12}, //B12
    {0, C9_13,  C8_13,  C7_13}, //B13
    {0, C9_14,  C8_14,  C7_14}, //B14
    {0, C9_15,  C8_15,  C6_14}, //B15
    {0, C9_16,  C7_15,  C6_15}, //B16

    {1, C1_1,   C3_2,   C4_2}, //C1
    {1, C1_2,   C2_2,   C4_3}, //C2
    {1, C1_3,   C2_3,   C3_3}, //C3
    {1, C1_4,   C2_4,   C3_4}, //C4
    {1, C1_5,   C2_5,   C3_5}, //C5
    {1, C1_6,   C2_6,   C3_6}, //C6
    {1, C1_7,   C2_7,   C3_7}, //C7
    {1, C1_8,   C2_8,   C3_8}, //C8
    {1, C9_1,   C8_1,   C7_1}, //C9
    {1, C9_2,   C8_2,   C7_2}, //C10
    {1, C9_3,   C8_3,   C7_3}, //C11
    {1, C9_4,   C8_4,   C7_4}, //C12
    {1, C9_5,   C8_5,   C7_5}, //C13
    {1, C9_6,   C8_6,   C7_6}, //C14
    {1, C9_7,   C8_7,   C6_6}, //C15
    {1, C9_8,   C7_7,   C6_7}, //C16

    {1, C1_9,   C3_10,  C4_10}, //D1
    {1, C1_10,  C2_10,  C4_11}, //D2
    {1, C1_11,  C2_11,  C3_11}, //D3
    {1, C1_12,  C2_12,  C3_12}, //D4
    {1, C1_13,  C2_13,  C3_13}, //D5
    {1, C1_14,  C2_14,  C3_14}, //D6
    {1, C1_15,  C2_15,  C3_15}, //D7
    {1, C1_16,  C2_16,  C3_16}, //D8
    {1, C9_9,    C8_9,   C7_9},  //D9
    {1, C9_10,  C8_10,  C7_10}, //D10
    {1, C9_11,  C8_11,  C7_11}, //D11
    {1, C9_12,  C8_12,  C7_12}, //D12
    {1, C9_13,  C8_13,  C7_13}, //D13
    {1, C9_14,  C8_14,  C7_14}, //D14
    {1, C9_15,  C8_15,  C6_14}, //D15
    {1, C9_16,  C7_15,  C6_15}  //D16
};

const rgb_led g_rgb_leds[DRIVER_LED_TOTAL] = {
//original 
//  C7,  C6,  C5,  C4,  C3,  C2,  C1,  A7,  A6,  A5,  A4,  A3,  A2,  A1,
//  C8,  C9, C10, C11, C12, C13, C14,  A8,  A9, A10, A11, A12, A13, A15,
//  D4,  D5,  D6,  D7,  D8, C16, C15,  B5,  B6,  B7,  B8, A16, ---, A14,
//  D3, ---,  D1,  D9, D10, D11, D12,  B4,  B3,  B2,  B1,  B9, ---, B10,
// D16, D15, D14, ---, ---, ---, D13, ---, ---, ---, B14, B13, B12, B11

//new xelusrgb 60
// A16, A15, A14, A13, A12, A11, A10,  A9,  B1,  B2,  B3,  B4,  B5,  B6,  B7,
//  A7,  A6,  A5,  A4,  A3,  A2,  A1,  B9, B10, B11, B12, B13, B14, B15,
//  A8, C14, C13, C12, C11, C10,  C9,  D1,  D2,  D3,  D4,  D5,  B8,
// C15,  C5,  C4,  C3,  C2,  C1,  D9, D10, D11, D12,  D6,  D7, B16,
// C16,  C8,  C7, ---, ---, ---,  D6, ---, ---, D13, D14, D15, D16,  D8


/* {row | col << 4}
 *    |           {x=0..224, y=0..64}
 *    |              |            modifier
 *    |              |         | */
    {{1|(6<<4)},    {104, 16}, 0}, //A1
    {{1|(5<<4)},    {88 , 16}, 0}, //A2
    {{1|(4<<4)},    {72 , 16}, 0}, //A3
    {{1|(3<<4)},    {56 , 16}, 0}, //A4
    {{1|(2<<4)},    {40 , 16}, 0}, //A5
    {{1|(1<<4)},    {24 , 16}, 0}, //A6
    {{1|(0<<4)},    {4  , 16}, 1}, //A7
    {{2|(0<<4)},    {6  , 32}, 1}, //A8
    {{0|(7<<4)},    {112,  0}, 0}, //A9
    {{0|(6<<4)},    {96 ,  0}, 0}, //A10
    {{0|(5<<4)},    {80 ,  0}, 0}, //A11
    {{0|(4<<4)},    {64 ,  0}, 0}, //A12
    {{0|(3<<4)},    {48 ,  0}, 0}, //A13
    {{0|(2<<4)},    {32 ,  0}, 0}, //A14
    {{0|(1<<4)},    {16 ,  0}, 0}, //A15
    {{0|(0<<4)},    {0  ,  0}, 1}, //A16

    {{0|(8<<4)},    {128,  0}, 0}, //B1
    {{0|(9<<4)},    {144,  0}, 0}, //B2
    {{0|(10<<4)},   {160,  0}, 0}, //B3
    {{0|(11<<4)},   {176,  0}, 0}, //B4
    {{0|(12<<4)},   {192,  0}, 0}, //B5
    {{0|(13<<4)},   {208,  0}, 0}, //B6
    {{0|(14<<4)},   {224,  0}, 1}, //B7
    {{2|(10<<4)},   {214, 32}, 1}, //B8
    {{1|(7<<4)},    {120, 16}, 0}, //B9
    {{1|(8<<4)},    {136, 16}, 0}, //B10
    {{1|(9<<4)},    {152, 16}, 0}, //B11
    {{1|(10<<4)},   {168, 16}, 0}, //B12
    {{1|(11<<4)},   {184, 16}, 0}, //B13
    {{1|(12<<4)},   {200, 16}, 0}, //B14
	{{1|(13<<4)},   {219, 16}, 1}, //B15
	{{3|(12<<4)},   {224, 48}, 1}, //B16

    {{3|(5<<4)},    {100, 48}, 0}, //C1
    {{3|(4<<4)},    {84 , 48}, 0}, //C2
    {{3|(3<<4)},    {68 , 48}, 0}, //C3
    {{3|(2<<4)},    {52 , 48}, 0}, //C4
    {{3|(1<<4)},    {36 , 48}, 0}, //C5
    {{4|(6<<4)},    {102, 64}, 1}, //C6
    {{4|(2<<4)},    {42 , 64}, 1}, //C7
    {{4|(1<<4)},    {22 , 64}, 1}, //C8		
    {{2|(6<<4)},    {108, 32}, 0}, //C9
    {{2|(5<<4)},    {92 , 32}, 0}, //C10
    {{2|(4<<4)},    {76 , 32}, 0}, //C11
    {{2|(3<<4)},    {60 , 32}, 0}, //C12
    {{2|(2<<4)},    {44 , 32}, 0}, //C13
    {{2|(1<<4)},    {28 , 32}, 0}, //C14
    {{3|(0<<4)},    {10 , 48}, 1}, //C15
    {{4|(0<<4)},    {2  , 64}, 1}, //C16

    {{2|(7<<4)},    {124, 32}, 0}, //D1
    {{2|(8<<4)},    {140, 32}, 0}, //D2
    {{2|(9<<4)},    {156, 32}, 0}, //D3
    {{2|(10<<4)},   {172, 32}, 0}, //D4
    {{2|(11<<4)},   {188, 32}, 0}, //D5
    {{3|(10<<4)},   {180, 48}, 0}, //D6
    {{3|(11<<4)},   {202, 48}, 1}, //D7
    {{2|(13<<4)},   {224, 64}, 1}, //D8
    {{3|(6<<4)},    {116, 48}, 0}, //D9
    {{3|(7<<4)},    {132, 48}, 0}, //D10
    {{3|(8<<4)},    {148, 48}, 0}, //D11
    {{3|(9<<4)},    {164, 48}, 0}, //D12
    {{4|(9<<4)},    {160, 64}, 1}, //D13
    {{4|(10<<4)},   {176, 64}, 1}, //D14
    {{4|(11<<4)},   {192, 64}, 1}, //D15
    {{4|(12<<4)},   {208, 64}, 1}  //D16
};


void bootmagic_lite(void)
{
	// The lite version of TMK's bootmagic made by Wilba.
	// 100% less potential for accidentally making the
	// keyboard do stupid things.

	// We need multiple scans because debouncing can't be turned off.
	matrix_scan();
	wait_ms(DEBOUNCING_DELAY);
	matrix_scan();

	// If the Esc and space bar are held down on power up,
	// reset the EEPROM valid state and jump to bootloader.
	// Assumes Esc is at [0,0] and spacebar is at [4,6].
	// This isn't very generalized, but we need something that doesn't
	// rely on user's keymaps in firmware or EEPROM.
	if ( ( matrix_get_row(0) & (1<<0) ) &&
		( matrix_get_row(4) & (1<<6) ) )
	{
		// Set the TMK/QMK EEPROM state as invalid.
		eeconfig_disable();
		//eeprom_set_valid(false);
		// Jump to bootloader.
		bootloader_jump();
	}
}

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
	debug_enable=true;
	bootmagic_lite();
	matrix_init_user();
}

void matrix_scan_kb(void) {

	matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {

	return process_record_user(keycode, record);
}

void led_set_kb(uint8_t usb_led) {
	//backlight_set_indicator_state(usb_led);
}

void suspend_power_down_kb(void)
{
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_kb(void)
{
    rgb_matrix_set_suspend_state(false);
}

