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
#include "hs60.h"
#include "config.h"

// Please ignore this is for upcoming features
/*#ifdef RAW_ENABLE

void raw_hid_receive( uint8_t *data, uint8_t length )
{
	uint8_t command = data[0];
	switch ( command )
	{
		case id_protocol_version:
		{
			msg_protocol_version *msg = (msg_protocol_version*)&data[1];
			msg->version = PROTOCOL_VERSION;
			break;
		}
#if USE_KEYMAPS_IN_EEPROM
		case id_keymap_keycode_load:
		{
			msg_keymap_keycode_load *msg = (msg_keymap_keycode_load*)&data[1];
			msg->keycode = keymap_keycode_load( msg->layer, msg->row, msg->column );
			break;
		}
		case id_keymap_keycode_save:
		{
			msg_keymap_keycode_save *msg = (msg_keymap_keycode_save*)&data[1];
			keymap_keycode_save( msg->layer, msg->row, msg->column, msg->keycode);
			break;
		}
		case id_keymap_default_save:
		{
			keymap_default_save();
			break;
		}
#endif // USE_KEYMAPS_IN_EEPROM
		case id_backlight_config_set_values:
		{
			msg_backlight_config_set_values *msg = (msg_backlight_config_set_values*)&data[1];
			backlight_config_set_values(msg);
			backlight_config_save();
			break;
		}
		case id_backlight_config_set_alphas_mods:
		{
			msg_backlight_config_set_alphas_mods *msg = (msg_backlight_config_set_alphas_mods*)&data[1];
			backlight_config_set_alphas_mods( msg->alphas_mods );
			backlight_config_save();
			break;
		}
		case id_backlight_set_key_color:
		{
			msg_backlight_set_key_color *msg = (msg_backlight_set_key_color*)&data[1];
			backlight_set_key_color(msg->row, msg->column, msg->hsv);
			break;
		}
		case id_system_get_state:
		{
			msg_system_state *msg = (msg_system_state*)&data[1];
			msg->value = backlight_get_tick();
			break;
		}
		default:
		{
			// Unhandled message.
			data[0] = id_unhandled;
			break;
		}
	}

	// Return same buffer with values changed
	raw_hid_send( data, length );

}

#endif*/

#ifdef HS60_ANSI

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
    //D2
    {1, C1_11,  C2_11,  C3_11}, //D3
    {1, C1_12,  C2_12,  C3_12}, //D4
    {1, C1_13,  C2_13,  C3_13}, //D5
    {1, C1_14,  C2_14,  C3_14}, //D6
    {1, C1_15,  C2_15,  C3_15}, //D7
    {1, C1_16,  C2_16,  C3_16}, //D8
    {1, C9_9,   C8_9,   C7_9},  //D9
    {1, C9_10,  C8_10,  C7_10}, //D10
    {1, C9_11,  C8_11,  C7_11}, //D11
    {1, C9_12,  C8_12,  C7_12}, //D12
    {1, C9_13,  C8_13,  C7_13}, //D13
    {1, C9_14,  C8_14,  C7_14}, //D14
    {1, C9_15,  C8_15,  C6_14}, //D15
    {1, C9_16,  C7_15,  C6_15}  //D16
};

const rgb_led g_rgb_leds[DRIVER_LED_TOTAL] = {
//
//  C7,  C6,  C5,  C4,  C3,  C2,  C1,  A7,  A6,  A5,  A4,  A3,  A2,  A1,
//  C8,  C9, C10, C11, C12, C13, C14,  A8,  A9, A10, A11, A12, A13, A15,
//  D4,  D5,  D6,  D7,  D8, C16, C15,  B5,  B6,  B7,  B8, A16, ---, A14,
//  D3, ---,  D1,  D9, D10, D11, D12,  B4,  B3,  B2,  B1,  B9, ---, B10,
// D16, D15, D14, ---, ---, ---, D13, ---, ---, ---, B14, B13, B12, B11
/* {row | col << 4}
 *    |           {x=0..224, y=0..64}
 *    |              |            modifier
 *    |              |         | */
    {{0|(13<<4)},   {224,  0}, 1}, //A1-A16
    {{0|(12<<4)},   {204,  0}, 0},
    {{0|(11<<4)},   {187,  0}, 0},
    {{0|(10<<4)},   {170,  0}, 0},
    {{0|(9<<4)},    {153,  0}, 0},
    {{0|(8<<4)},    {136,  0}, 0},
    {{0|(7<<4)},    {119,  0}, 0},
    {{1|(7<<4)},    {119, 16}, 0},
    {{1|(8<<4)},    {136, 16}, 0},
    {{1|(9<<4)},    {153, 16}, 0},
    {{1|(10<<4)},   {170, 16}, 0},
    {{1|(11<<4)},   {187, 16}, 0},
    {{1|(12<<4)},   {204, 16}, 0},
    {{2|(13<<4)},   {224, 32}, 1},
    {{2|(12<<4)},   {224, 16}, 0},
    {{2|(11<<4)},   {197, 32}, 0},

    {{3|(10<<4)},   {170, 48}, 0}, //B1-B14
    {{3|(9<<4)},    {153, 48}, 0},
    {{3|(8<<4)},    {136, 48}, 0},
    {{3|(7<<4)},    {119, 48}, 0},
    {{2|(7<<4)},    {119, 32}, 0},
    {{2|(8<<4)},    {136, 32}, 0},
    {{2|(9<<4)},    {153, 32}, 0},
    {{2|(10<<4)},   {170, 32}, 0},
    {{3|(11<<4)},   {187, 48}, 0},
    {{3|(13<<4)},   {214, 48}, 1},
    {{4|(13<<4)},   {224, 64}, 1},
    {{4|(12<<4)},   {204, 64}, 1},
    {{4|(11<<4)},   {187, 64}, 1},
    {{4|(10<<4)},   {170, 64}, 1},

    {{0|(6<<4)},    {102,  0}, 0}, //C1-C16
    {{0|(5<<4)},    { 85,  0}, 0},
    {{0|(4<<4)},    { 68,  0}, 0},
    {{0|(3<<4)},    { 51,  0}, 0},
    {{0|(2<<4)},    { 34,  0}, 0},
    {{0|(1<<4)},    { 17,  0}, 0},
    {{0|(0<<4)},    {  0,  0}, 1},
    {{1|(0<<4)},    {  0, 16}, 1},
    {{1|(1<<4)},    { 17, 16}, 0},
    {{1|(2<<4)},    { 34, 16}, 0},
    {{1|(3<<4)},    { 51, 16}, 0},
    {{1|(4<<4)},    { 68, 16}, 0},
    {{1|(5<<4)},    { 85, 16}, 0},
    {{1|(6<<4)},    {102, 16}, 0},
    {{2|(6<<4)},    {102, 32}, 0},
    {{2|(5<<4)},    { 85, 32}, 0},

    {{3|(2<<4)},    { 32, 48}, 0}, //D1-D16
    //D2
    {{3|(0<<4)},    { 10, 48}, 1},
    {{2|(0<<4)},    {  0, 32}, 1},
    {{2|(1<<4)},    { 17, 32}, 0},
    {{2|(2<<4)},    { 34, 32}, 0},
    {{2|(3<<4)},    { 51, 32}, 0},
    {{2|(4<<4)},    { 68, 32}, 0},
    {{3|(3<<4)},    { 51, 48}, 0},
    {{3|(4<<4)},    { 68, 48}, 0},
    {{3|(5<<4)},    { 85, 48}, 0},
    {{3|(6<<4)},    {102, 48}, 0},
    {{4|(3<<4)},    {102, 64}, 0},
    {{4|(2<<4)},    { 34, 68}, 1},
    {{4|(1<<4)},    { 17, 68}, 1},
    {{4|(0<<4)},    {  0, 68}, 1}
};

#else

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
    {1, C9_9,   C8_9,   C7_9},  //D9
    {1, C9_10,  C8_10,  C7_10}, //D10
    {1, C9_11,  C8_11,  C7_11}, //D11
    {1, C9_12,  C8_12,  C7_12}, //D12
    {1, C9_13,  C8_13,  C7_13}, //D13
    {1, C9_14,  C8_14,  C7_14}, //D14
    {1, C9_15,  C8_15,  C6_14}, //D15
    {1, C9_16,  C7_15,  C6_15}  //D16
};

const rgb_led g_rgb_leds[DRIVER_LED_TOTAL] = {
//
//  C7,  C6,  C5,  C4,  C3,  C2,  C1,  A7,  A6,  A5,  A4,  A3,  A2,  A1,
//  C8,  C9, C10, C11, C12, C13, C14,  A8,  A9, A10, A11, A12, A13, ---,
//  D4,  D5,  D6,  D7,  D8, C16, C15,  B5,  B6,  B7,  B8, A16, A15, A14,
//  D3,  D2,  D1,  D9, D10, D11, D12,  B4,  B3,  B2,  B1,  B9, ---, B10,
// D16, D15, D14, ---, ---, ---, D13, ---, ---, ---, B14, B13, B12, B11
/* {row | col << 4}
 *    |           {x=0..224, y=0..64}
 *    |              |            modifier
 *    |              |         | */
    {{0|(13<<4)},   {224,  0}, 1}, //A1-A16
    {{0|(12<<4)},   {204,  0}, 0},
    {{0|(11<<4)},   {187,  0}, 0},
    {{0|(10<<4)},   {170,  0}, 0},
    {{0|(9<<4)},    {153,  0}, 0},
    {{0|(8<<4)},    {136,  0}, 0},
    {{0|(7<<4)},    {119,  0}, 0},
    {{1|(7<<4)},    {119, 16}, 0},
    {{1|(8<<4)},    {136, 16}, 0},
    {{1|(9<<4)},    {153, 16}, 0},
    {{1|(10<<4)},   {170, 16}, 0},
    {{1|(11<<4)},   {187, 16}, 0},
    {{1|(12<<4)},   {204, 16}, 0},
    {{2|(13<<4)},   {224,  8}, 1},
    {{2|(12<<4)},   {204, 32}, 0},
    {{2|(11<<4)},   {187, 32}, 0},

    {{3|(10<<4)},   {170, 48}, 0}, //B1-B14
    {{3|(9<<4)},    {153, 48}, 0},
    {{3|(8<<4)},    {136, 48}, 0},
    {{3|(7<<4)},    {119, 48}, 0},
    {{2|(7<<4)},    {119, 32}, 0},
    {{2|(8<<4)},    {136, 32}, 0},
    {{2|(9<<4)},    {153, 32}, 0},
    {{2|(10<<4)},   {170, 32}, 0},
    {{3|(11<<4)},   {187, 48}, 0},
    {{3|(13<<4)},   {214, 48}, 1},
    {{4|(13<<4)},   {224, 64}, 1},
    {{4|(12<<4)},   {204, 64}, 1},
    {{4|(11<<4)},   {187, 64}, 1},
    {{4|(10<<4)},   {170, 64}, 1},

    {{0|(6<<4)},    {102,  0}, 0}, //C1-C16
    {{0|(5<<4)},    { 85,  0}, 0},
    {{0|(4<<4)},    { 68,  0}, 0},
    {{0|(3<<4)},    { 51,  0}, 0},
    {{0|(2<<4)},    { 34,  0}, 0},
    {{0|(1<<4)},    { 17,  0}, 0},
    {{0|(0<<4)},    {  0,  0}, 1},
    {{1|(0<<4)},    {  0, 16}, 1},
    {{1|(1<<4)},    { 17, 16}, 0},
    {{1|(2<<4)},    { 34, 16}, 0},
    {{1|(3<<4)},    { 51, 16}, 0},
    {{1|(4<<4)},    { 68, 16}, 0},
    {{1|(5<<4)},    { 85, 16}, 0},
    {{1|(6<<4)},    {102, 16}, 0},
    {{2|(6<<4)},    {102, 32}, 0},
    {{2|(5<<4)},    { 85, 32}, 0},

    {{3|(2<<4)},    { 32, 48}, 0}, //D1-D16
    {{3|(1<<4)},    { 17, 48}, 0},
    {{3|(0<<4)},    {  0, 48}, 1},
    {{2|(0<<4)},    {  0, 32}, 1},
    {{2|(1<<4)},    { 17, 32}, 0},
    {{2|(2<<4)},    { 34, 32}, 0},
    {{2|(3<<4)},    { 51, 32}, 0},
    {{2|(4<<4)},    { 68, 32}, 0},
    {{3|(3<<4)},    { 51, 48}, 0},
    {{3|(4<<4)},    { 68, 48}, 0},
    {{3|(5<<4)},    { 85, 48}, 0},
    {{3|(6<<4)},    {102, 48}, 0},
    {{4|(3<<4)},    {102, 64}, 0},
    {{4|(2<<4)},    { 34, 68}, 1},
    {{4|(1<<4)},    { 17, 68}, 1},
    {{4|(0<<4)},    {  0, 68}, 1}
};

#endif

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

	bootmagic_lite();

    // Please ignore this is for upcoming features
	// If the EEPROM has the magic, the data is good.
	// OK to load from EEPROM.
	/*if (eeprom_is_valid())
	{
		backlight_config_load();

		// TODO: do something to "turn on" keymaps in EEPROM?
	}
	else
	{
		// If the EEPROM has not been saved before, or is out of date,
		// save the default values to the EEPROM. Default values
		// come from construction of the zeal_backlight_config instance.
		backlight_config_save();

		// Clear the LED colors stored in EEPROM
		for ( int row=0; row < MATRIX_ROWS; row++ )
		{
			HSV hsv;
			for ( int column=0; column < MATRIX_COLS; column++ )
			{
				hsv.h = rand() & 0xFF;
				hsv.s = rand() & 0x7F;
				hsv.v = 255;
				backlight_set_key_color( row, column, hsv );
			}
		}
        #ifdef USE_KEYMAPS_IN_EEPROM
		keymap_default_save();
		#endif
		// Save the magic number last, in case saving was interrupted
		eeprom_set_valid(true);
	}*/

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