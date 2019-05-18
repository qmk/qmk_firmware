#include "keyboard.h"
#include "ch.h"
#include "hal.h"
#include "led_custom.h"
#include "util.h"
#include "quantum.h"

#include "ws2812.h"

#include "raw_hid.h"
#include "dynamic_keymap.h"
#include "tmk_core/common/eeprom.h"

// HACK
#include "keyboards/zeal60/zeal60_api.h" // Temporary hack
#include "keyboards/zeal60/zeal60_keycodes.h" // Temporary hack


backlight_config_t kb_backlight_config = {
  .enable = true,
  .breathing = true,
  .level = BACKLIGHT_LEVELS
};

bool eeprom_is_valid(void)
{
	return (eeprom_read_word(((void*)EEPROM_MAGIC_ADDR)) == EEPROM_MAGIC &&
			eeprom_read_byte(((void*)EEPROM_VERSION_ADDR)) == EEPROM_VERSION);
}

void eeprom_set_valid(bool valid)
{
	eeprom_update_word(((void*)EEPROM_MAGIC_ADDR), valid ? EEPROM_MAGIC : 0xFFFF);
	eeprom_update_byte(((void*)EEPROM_VERSION_ADDR), valid ? EEPROM_VERSION : 0xFF);
}

void eeprom_reset(void)
{
	eeprom_set_valid(false);
	eeconfig_disable();
}

void save_backlight_config_to_eeprom(){
  eeprom_update_byte((uint8_t*)EEPROM_CUSTOM_BACKLIGHT, kb_backlight_config.raw);
}

void load_custom_config(){
  kb_backlight_config.raw = eeprom_read_byte((uint8_t*)EEPROM_CUSTOM_BACKLIGHT);
}

#ifdef DYNAMIC_KEYMAP_ENABLE
void dynamic_keymap_custom_reset(void){
    void *p = (void*)(EEPROM_CUSTOM_BACKLIGHT);
	void *end = (void*)(DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR);
	while ( p != end ) {
		eeprom_update_byte(p, 0);
		++p;
	}
}
#endif

void eeprom_init_kb(void)
{
	// If the EEPROM has the magic, the data is good.
	// OK to load from EEPROM.
	if (eeprom_is_valid()) {
		load_custom_config();
	} else	{
#ifdef DYNAMIC_KEYMAP_ENABLE
		// This resets the keymaps in EEPROM to what is in flash.
		dynamic_keymap_reset();
		// This resets the macros in EEPROM to nothing.
		dynamic_keymap_macro_reset();
        // Reset the custom stuff
        dynamic_keymap_custom_reset();
#endif
		// Save the magic number last, in case saving was interrupted
        save_backlight_config_to_eeprom();
		eeprom_set_valid(true);
	}
}

__attribute__ ((weak))
void matrix_init_board(void);

void matrix_init_kb(void){
  	eeprom_init_kb();
      /* MOSI pin*/
    palSetPadMode(PORT_WS2812, PIN_WS2812, PAL_MODE_ALTERNATE(0));
    wait_ms(500);

#ifdef RGBLIGHT_ENABLE
    leds_init();
#endif
    backlight_init_ports();

    matrix_init_board();
}

void matrix_scan_kb(void)
{
  #ifdef RGBLIGHT_ENABLE
    rgblight_task();
  #endif
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case BL_INC:
      if (record->event.pressed) {
        kb_backlight_config.level = kb_backlight_config.level + 1;
        if(kb_backlight_config.level > BACKLIGHT_LEVELS){
          kb_backlight_config.level = BACKLIGHT_LEVELS;
        }
        backlight_set(kb_backlight_config.level);
        save_backlight_config_to_eeprom();
      }
      return false;
    case BL_TOGG:
      if (record->event.pressed) {
        kb_backlight_config.enable = !kb_backlight_config.enable;
        if(kb_backlight_config.enable){
          backlight_set(kb_backlight_config.level);
        } else {
          backlight_set(0);
        }
        save_backlight_config_to_eeprom();
      }
      return false;

    case BL_DEC:
      if (record->event.pressed) {
        if(kb_backlight_config.level <= 1){
          kb_backlight_config.level = 0;
        } else {
          kb_backlight_config.level = kb_backlight_config.level - 1;
        }
        backlight_set(kb_backlight_config.level);
        save_backlight_config_to_eeprom();
      }
      return false;
    case BL_BRTG:
      if (record->event.pressed) {
        kb_backlight_config.breathing = !kb_backlight_config.breathing;
        breathing_toggle();
        save_backlight_config_to_eeprom();
      }
      return false;
    default:
        break;
  }

  #ifdef DYNAMIC_KEYMAP_ENABLE
	// Handle macros
	if (record->event.pressed) {
		if ( keycode >= MACRO00 && keycode <= MACRO15 )
		{
			uint8_t id = keycode - MACRO00;
			dynamic_keymap_macro_send(id);
			return false;
		}
	}
    #endif //DYNAMIC_KEYMAP_ENABLE

  return true;
}


// Start Dynamic Keymap code
#ifdef RAW_ENABLE

void raw_hid_receive( uint8_t *data, uint8_t length )
{
	uint8_t *command_id = &(data[0]);
	uint8_t *command_data = &(data[1]);
	switch ( *command_id )
	{
		case id_get_protocol_version:
		{
			command_data[0] = PROTOCOL_VERSION >> 8;
			command_data[1] = PROTOCOL_VERSION & 0xFF;
			break;
		}
		case id_get_keyboard_value:
		{
            switch( command_data[0])
            {
                case id_uptime:
                {
                uint32_t value = timer_read32();
                command_data[1] = (value >> 24 ) & 0xFF;
                command_data[2] = (value >> 16 ) & 0xFF;
                command_data[3] = (value >> 8 ) & 0xFF;
                command_data[4] = value & 0xFF;
                break;
                }
                default:
                {
                *command_id = id_unhandled;
                break;
                }
            }
            break;
        }
#ifdef DYNAMIC_KEYMAP_ENABLE

		case id_dynamic_keymap_get_keycode:
		{
			uint16_t keycode = dynamic_keymap_get_keycode( command_data[0], command_data[1], command_data[2] );
			command_data[3] = keycode >> 8;
			command_data[4] = keycode & 0xFF;
			break;
		}
		case id_dynamic_keymap_set_keycode:
		{
			dynamic_keymap_set_keycode( command_data[0], command_data[1], command_data[2], ( command_data[3] << 8 ) | command_data[4] );
			break;
		}
		case id_dynamic_keymap_reset:
		{
			dynamic_keymap_reset();
			break;
		}
		case id_dynamic_keymap_macro_get_count:
		{
			command_data[0] = dynamic_keymap_macro_get_count();
			break;
		}
		case id_dynamic_keymap_macro_get_buffer_size:
		{
			uint16_t size = dynamic_keymap_macro_get_buffer_size();
			command_data[0] = size >> 8;
			command_data[1] = size & 0xFF;
			break;
		}
		case id_dynamic_keymap_macro_get_buffer:
		{
			uint16_t offset = ( command_data[0] << 8 ) | command_data[1];
			uint16_t size = command_data[2]; // size <= 28
			dynamic_keymap_macro_get_buffer( offset, size, &command_data[3] );
			break;
		}
		case id_dynamic_keymap_macro_set_buffer:
		{
			uint16_t offset = ( command_data[0] << 8 ) | command_data[1];
			uint16_t size = command_data[2]; // size <= 28
			dynamic_keymap_macro_set_buffer( offset, size, &command_data[3] );
			break;
		}
		case id_dynamic_keymap_macro_reset:
		{
			dynamic_keymap_macro_reset();
			break;
		}
		case id_dynamic_keymap_get_layer_count:
		{
			command_data[0] = dynamic_keymap_get_layer_count();
			break;
		}
		case id_dynamic_keymap_get_buffer:
		{
			uint16_t offset = ( command_data[0] << 8 ) | command_data[1];
			uint16_t size = command_data[2]; // size <= 28
			dynamic_keymap_get_buffer( offset, size, &command_data[3] );
			break;
		}
		case id_dynamic_keymap_set_buffer:
		{
			uint16_t offset = ( command_data[0] << 8 ) | command_data[1];
			uint16_t size = command_data[2]; // size <= 28
			dynamic_keymap_set_buffer( offset, size, &command_data[3] );
			break;
		}
#endif // DYNAMIC_KEYMAP_ENABLE
		case id_eeprom_reset:
		{
			eeprom_reset();
			break;
		}
		case id_bootloader_jump:
		{
			// Need to send data back before the jump
			// Informs host that the command is handled
			raw_hid_send( data, length );
			// Give host time to read it
			wait_ms(100);
			bootloader_jump();
			break;
		}
		default:
		{
			// Unhandled message.
			*command_id = id_unhandled;
			break;
		}
	}

	// Return same buffer with values changed
	raw_hid_send( data, length );

}

#endif
