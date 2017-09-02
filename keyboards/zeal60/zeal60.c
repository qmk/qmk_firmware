#include "zeal60.h"
#include "zeal_backlight.h"
#include "zeal_keymap.h"
#include "zeal_eeprom.h"
#include "zeal_rpc.h"

#include "raw_hid.h"
#include "config.h"

#ifdef RAW_ENABLE

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

#endif

void bootmagic_lite(void)
{
	// The lite version of TMK's bootmagic.
	// 100% less potential for accidentally making the
	// keyboard do stupid things.

	// We need multiple scans because debouncing can't be turned off.
	matrix_scan();
	wait_ms(DEBOUNCING_DELAY);
	matrix_scan();

	// If the Esc and space bar are held down on power up,
	// reset the EEPROM valid state and jump to bootloader.
	// Assumes Esc is at [0,0] and spacebar is at [4,7].
	// This isn't very generalized, but we need something that doesn't
	// rely on user's keymaps in firmware or EEPROM.
	if ( ( matrix_get_row(0) & (1<<0) ) &&
		( matrix_get_row(4) & (1<<7) ) )
	{
		// Set the Zeal60 specific EEPROM state as invalid.
		eeprom_set_valid(false);
		// Set the TMK/QMK EEPROM state as invalid.
		eeconfig_disable();
		// Jump to bootloader.
		bootloader_jump();
	}
}

void matrix_init_kb(void)
{
	bootmagic_lite();

	// If the EEPROM has the magic, the data is good.
	// OK to load from EEPROM.
	if (eeprom_is_valid())
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

		// This saves "empty" keymaps so it falls back to the keymaps
		// in the firmware (aka. progmem/flash)
		keymap_default_save();

		// Save the magic number last, in case saving was interrupted
		eeprom_set_valid(true);
	}

	// Initialize LED drivers for backlight.
	backlight_init_drivers();
	
	backlight_timer_init();
	backlight_timer_enable();

	matrix_init_user();
}

void matrix_scan_kb(void)
{
	// This only updates the LED driver buffers if something has changed.
	backlight_update_pwm_buffers();
	matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record)
{
	// Record keypresses for backlight effects
	if ( record->event.pressed )
	{
		backlight_set_key_hit( record->event.key.row, record->event.key.col );
	}

	switch(keycode)
	{
		case BR_INC:
			if (record->event.pressed)
			{
				backlight_brightness_increase();
			}
			return false;
			break;
		case BR_DEC:
			if (record->event.pressed)
			{
				backlight_brightness_decrease();
			}
			return false;
			break;
		case EF_INC:
			if (record->event.pressed)
			{
				backlight_effect_increase();
			}
			return false;
			break;
		case EF_DEC:
			if (record->event.pressed)
			{
				backlight_effect_decrease();
			}
			return false;
			break;
		case ES_INC:
			if (record->event.pressed)
			{
				backlight_effect_speed_increase();
			}
			return false;
			break;
		case ES_DEC:
			if (record->event.pressed)
			{
				backlight_effect_speed_decrease();
			}
			return false;
			break;
		case H1_INC:
			if (record->event.pressed)
			{
				backlight_color_1_hue_increase();
			}
			return false;
			break;
		case H1_DEC:
			if (record->event.pressed)
			{
				backlight_color_1_hue_decrease();
			}
			return false;
			break;
		case S1_INC:
			if (record->event.pressed)
			{
				backlight_color_1_sat_increase();
			}
			return false;
			break;
		case S1_DEC:
			if (record->event.pressed)
			{
				backlight_color_1_sat_decrease();
				break;
			}
			return false;
			break;
		case H2_INC:
			if (record->event.pressed)
			{
				backlight_color_2_hue_increase();
			}
			return false;
			break;
		case H2_DEC:
			if (record->event.pressed)
			{
				backlight_color_2_hue_decrease();
			}
			return false;
			break;
		case S2_INC:
			if (record->event.pressed)
			{
				backlight_color_2_sat_increase();
			}
			return false;
			break;
		case S2_DEC:
			if (record->event.pressed)
			{
				backlight_color_2_sat_decrease();
				break;
			}
			return false;
			break;
		case FN_MO13:
			if (record->event.pressed)
			{
				layer_on(1);
				update_tri_layer(1, 2, 3);
			}
			else
			{
				layer_off(1);
				update_tri_layer(1, 2, 3);
			}
			return false;
			break;
		case FN_MO23:
			if (record->event.pressed)
			{
				layer_on(2);
				update_tri_layer(1, 2, 3);
			}
			else
			{
				layer_off(2);
				update_tri_layer(1, 2, 3);
			}
			return false;
			break;
	}
	
	return process_record_user(keycode, record);
}

// This overrides the one in quantum/keymap_common.c
uint16_t keymap_function_id_to_action( uint16_t function_id )
{
	// Zeal60 specific "action functions" are 0xF00 to 0xFFF
	// i.e. F(0xF00) to F(0xFFF) are mapped to
	// enum zeal60_action_functions by masking last 8 bits.
	if ( function_id >= 0x0F00 && function_id <= 0x0FFF )
	{
		uint8_t id = function_id & 0xFF;
		switch ( id )
		{
			case TRIPLE_TAP_1_3:
			case TRIPLE_TAP_2_3:
			{
				return ACTION_FUNCTION_TAP(id);
				break;
			}
			default:
				break;
		}
	}

#if USE_KEYMAPS_IN_EEPROM

#if 0
	// This is how to implement actions stored in EEPROM.
	// Not yet implemented. Not sure if it's worth the trouble
	// before we have a nice GUI for keymap editing.
	if ( eeprom_is_valid() &&
		 function_id < 32 ) // TODO: replace magic number
	{
		uint16_t action = keymap_action_load(function_id);

		// If action is not "empty", return it, otherwise
		// drop down to return the one in flash
		if ( action != 0x0000 ) // TODO: replace magic number
		{
			return action;
		}
	}
#endif

#endif // USE_KEYMAPS_IN_EEPROM

	return pgm_read_word(&fn_actions[function_id]);
}


// Zeal60 specific "action functions"
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
	switch (id)
	{
	case TRIPLE_TAP_1_3:
	case TRIPLE_TAP_2_3:
		if (record->event.pressed)
		{
			layer_on( id == TRIPLE_TAP_1_3 ? 1 : 2 );

			if (record->tap.count && !record->tap.interrupted)
			{
				if (record->tap.count >= 3)
				{
					layer_invert(3);
				}
			}
			else
			{
				record->tap.count = 0;
			}
		}
		else
		{
			layer_off( id == TRIPLE_TAP_1_3 ? 1 : 2 );
		}
		break;
	}
}

void led_set_kb(uint8_t usb_led)
{
	backlight_set_indicator_state(usb_led);
	//backlight_debug_led(usb_led & (1<<USB_LED_CAPS_LOCK));
}

void suspend_power_down_kb(void)
{
	backlight_set_suspend_state(true);
}

void suspend_wakeup_init_kb(void)
{
	backlight_set_suspend_state(false);
}

