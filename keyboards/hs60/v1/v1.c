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
#include "quantum.h"

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

const is31fl3731_led_t PROGMEM g_is31fl3731_leds[RGB_MATRIX_LED_COUNT] = {
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

led_config_t g_led_config = { {
    {  36,  35,  34,  33,  32,  31,  30,   6,   5,   4,   3,   2,   1,   0 },
    {  37,  38,  39,  40,  41,  42,  43,   7,   8,   9,  10,  11,  12, NO_LED },
    {  48,  49,  50,  51,  52,  45,  44,  20,  21,  22,  23,  15,  14,  13 },
    {  47, NO_LED,  46,  53,  54,  55,  56,  19,  18,  17,  16,  24, NO_LED,  25 },
    {  60,  59,  58,  57, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,  29,  28,  27,  26 }
}, {
	//A1-A16
    { 224,   0 }, { 204,   0 }, { 187,   0 }, { 170,   0 }, { 153,   0 }, { 136,   0 }, { 119,   0 }, { 119,  16 }, { 136,  16 }, { 153,  16 }, { 170,  16 }, { 187,  16 }, { 204,  16 }, { 224,  32 },
    { 224,  16 }, { 197,  32 },
	//B1-B14
    { 170,  48 }, { 153,  48 }, { 136,  48 }, { 119,  48 }, { 119,  32 }, { 136,  32 }, { 153,  32 }, { 170,  32 }, { 187,  48 }, { 214,  48 }, { 224,  64 }, { 204,  64 }, { 187,  64 }, { 170,  64 },
	//C1-C16
    { 102,   0 }, {  85,   0 }, {  68,   0 }, {  51,   0 }, {  34,   0 }, {  17,   0 }, {   0,   0 }, {   0,  16 }, {  17,  16 }, {  34,  16 }, {  51,  16 }, {  68,  16 }, {  85,  16 }, { 102,  16 },
    { 102,  32 }, {  85,  32 },
	//D1-D16
    {  32,  48 }, {  10,  48 }, {   0,  32 }, {  17,  32 }, {  34,  32 }, {  51,  32 }, {  68,  32 }, {  51,  48 }, {  68,  48 }, {  85,  48 }, { 102,  48 }, { 102,  64 }, {  34,  68 }, {  17,  68 },
    {   0,  68 }
}, {
	//A1-A16
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    4, 4,
	//B1-B14
    4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1,
	//C1-C16
    4, 4, 4, 4, 4, 4, 1, 1, 4, 4, 4, 4, 4, 4,
    4, 4,
	//D1-D16
    4, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
    1
} };

#else

const is31fl3731_led_t PROGMEM g_is31fl3731_leds[RGB_MATRIX_LED_COUNT] = {
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

led_config_t g_led_config = { {
    {  36,  35,  34,  33,  32,  31,  30,   6,   5,   4,   3,   2,   1,   0 },
    {  37,  38,  39,  40,  41,  42,  43,   7,   8,   9,  10,  11,  12, NO_LED },
    {  49,  50,  51,  52,  53,  45,  44,  20,  21,  22,  23,  15,  14,  13 },
    {  48,  47,  46,  54,  55,  56,  57,  19,  18,  17,  16,  24, NO_LED,  25 },
    {  61,  60,  59,  58, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,  29,  28,  27,  26 }
}, {
	//A1-A16
    { 224,   0 }, { 204,   0 }, { 187,   0 }, { 170,   0 }, { 153,   0 }, { 136,   0 }, { 119,   0 }, { 119,  16 }, { 136,  16 }, { 153,  16 }, { 170,  16 }, { 187,  16 }, { 204,  16 }, { 224,   8 },
    { 204,  32 }, { 187,  32 },
	//B1-B14
    { 170,  48 }, { 153,  48 }, { 136,  48 }, { 119,  48 }, { 119,  32 }, { 136,  32 }, { 153,  32 }, { 170,  32 }, { 187,  48 }, { 214,  48 }, { 224,  64 }, { 204,  64 }, { 187,  64 }, { 170,  64 },
	//C1-C16
    { 102,   0 }, {  85,   0 }, {  68,   0 }, {  51,   0 }, {  34,   0 }, {  17,   0 }, {   0,   0 }, {   0,  16 }, {  17,  16 }, {  34,  16 }, {  51,  16 }, {  68,  16 }, {  85,  16 }, { 102,  16 },
    { 102,  32 }, {  85,  32 },
	//D1-D16
    {  32,  48 }, {  17,  48 }, {   0,  48 }, {   0,  32 }, {  17,  32 }, {  34,  32 }, {  51,  32 }, {  68,  32 }, {  51,  48 }, {  68,  48 }, {  85,  48 }, { 102,  48 }, { 102,  64 }, {  34,  68 },
    {  17,  68 }, {   0,  68 }
}, {
	//A1-A16
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    4, 4,
	//B1-B14
    4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1,
	//C1-C16
    4, 4, 4, 4, 4, 4, 1, 1, 4, 4, 4, 4, 4, 4,
    4, 4,
	//D1-D16
    4, 4, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 1
} };

#endif

#ifndef DEBOUNCE
#    define DEBOUNCE 5
#endif

void bootmagic_lite(void)
{
	// The lite version of TMK's bootmagic made by Wilba.
	// 100% less potential for accidentally making the
	// keyboard do stupid things.

	// We need multiple scans because debouncing can't be turned off.
	matrix_scan();
	wait_ms(DEBOUNCE);
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

void suspend_power_down_kb(void)
{
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_kb(void)
{
    rgb_matrix_set_suspend_state(false);
}
