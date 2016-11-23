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
		case id_keymap_keycode_load:
		{
			uint16_t keycode = keymap_keycode_load(data[1], data[2], data[3]);
			data[4] = (uint8_t)(keycode >> 8);
			data[5] = (uint8_t)(keycode & 0xFF);
			break;
		}
		case id_keymap_keycode_save:
		{
			uint16_t keycode = data[4] << 8;
			keycode |= data[5];
			keymap_keycode_save(data[1], data[2], data[3], keycode);
			break;
		}
		case id_keymap_default_save:
		{
			keymap_default_save();
			break;
		}
		case id_backlight_config_set_flags:
		{
			backlight_config_set_flags(data[1]);
			backlight_config_save();
			backlight_init_drivers();
			break;
		}
		case id_backlight_config_set_alphas_mods:
		{
			uint16_t alpha_mods[5];
			alpha_mods[0] = data[1] << 8 | data[2];
			alpha_mods[1] = data[3] << 8 | data[4];
			alpha_mods[2] = data[5] << 8 | data[6];
			alpha_mods[3] = data[7] << 8 | data[8];
			alpha_mods[4] = data[9] << 8 | data[10];
			backlight_config_set_alphas_mods( alpha_mods );
			backlight_config_save();
			break;
		}
		case id_backlight_set_key_color:
		{
			HSV hsv = { data[3], data[4], data[5] };
			backlight_set_key_color(data[1], data[2], hsv);
			break;
		}
	}

	// Return same buffer with values changed
	raw_hid_send( data, length );

}

#endif


void matrix_init_kb(void)
{

#ifndef ZEAL60_TEST
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

		// This saves "empty" keymaps so it falls back to the keymaps
		// in the firmware (aka. progmem/flash)
		keymap_default_save();

		// Save the magic number last, in case saving was interrupted
	    eeprom_set_valid(true);
	}
#endif

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

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
	// put your per-action keyboard code here
	// runs for every action, just before processing by the firmware

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
	if (usb_led & (1<<USB_LED_CAPS_LOCK))
    {
		// Output high.
		DDRE |= (1<<6);
		PORTE |= (1<<6);
    }
	else
	{
		// Output low.
		DDRE &= ~(1<<6);
		PORTE &= ~(1<<6);
    }
	
	led_set_user(usb_led);
}



