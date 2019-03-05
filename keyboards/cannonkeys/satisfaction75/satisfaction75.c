#include "satisfaction75.h"
#include "print.h"
#include "debug.h"

#include "ch.h"
#include "hal.h"

#ifdef QWIIC_MICRO_OLED_ENABLE
#include "micro_oled.h"
#include "qwiic.h"
#endif

#include "timer.h"

#include "raw_hid.h"
#include "dynamic_keymap.h"
#include "tmk_core/common/eeprom.h"

// HACK
#include "keyboards/zeal60/zeal60_api.h" // Temporary hack
#include "keyboards/zeal60/zeal60_keycodes.h" // Temporary hack


/* Artificial delay added to get media keys to work in the encoder*/
#define MEDIA_KEY_DELAY 10

uint16_t last_flush;

volatile uint8_t led_numlock = false;
volatile uint8_t led_capslock = false;
volatile uint8_t led_scrolllock = false;

uint8_t layer;

bool queue_for_send = false;
bool clock_set_mode = false;
uint8_t oled_mode = OLED_DEFAULT;
bool oled_sleeping = false;

uint8_t encoder_value = 32;
uint8_t encoder_mode = ENC_MODE_VOLUME;
uint8_t enabled_encoder_modes = 0x1F;

RTCDateTime last_timespec;
uint16_t last_minute = 0;

uint8_t time_config_idx = 0;
int8_t hour_config = 0;
int16_t minute_config = 0;
int8_t year_config = 0;
int8_t month_config = 0;
int8_t day_config = 0;
uint8_t previous_encoder_mode = 0;

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
	// Set the Zeal60 specific EEPROM state as invalid.
	eeprom_set_valid(false);
	// Set the TMK/QMK EEPROM state as invalid.
	eeconfig_disable();
}

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
        case id_oled_default_mode:
        {
          uint8_t default_oled = eeprom_read_byte((uint8_t*)DYNAMIC_KEYMAP_DEFAULT_OLED);
          command_data[1] = default_oled;
          break;
        }
        case id_oled_mode:
        {
          command_data[1] = oled_mode;
          break;

        }
        case id_encoder_modes:
        {
          command_data[1] = enabled_encoder_modes;
          break;
        }
        case id_encoder_custom:
        {
          // uint8_t custom_encoder_idx = command_data[1];
          // command_data[2] = 0x00;
          // command_data[3] = 0x00;
          // command_data[4] = 0x00;
          // command_data[5] = 0x00;
          // command_data[6] = 0x00;
          // command_data[7] = 0x00;
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
    case id_set_keyboard_value:
    {
      switch(command_data[0]){
        case id_oled_default_mode:
        {
          eeprom_update_byte((uint8_t*)DYNAMIC_KEYMAP_DEFAULT_OLED, command_data[1]);
          break;
        }
        case id_oled_mode:
        {
          oled_mode = command_data[1];
          draw_ui();
          break;
        }
        case id_encoder_modes:
        {
          enabled_encoder_modes = command_data[1];
          eeprom_update_byte((uint8_t*)DYNAMIC_KEYMAP_ENABLED_ENCODER_MODES, enabled_encoder_modes);
          break;
        }
        case id_encoder_custom:
        {
          // uint8_t custom_encoder_idx = command_data[1];
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


void read_host_led_state(void) {
  uint8_t leds = host_keyboard_leds();
  if (leds & (1 << USB_LED_NUM_LOCK))    {
    if (led_numlock == false){
    led_numlock = true;}
    } else {
    if (led_numlock == true){
    led_numlock = false;}
    }
  if (leds & (1 << USB_LED_CAPS_LOCK))   {
    if (led_capslock == false){
    led_capslock = true;}
    } else {
    if (led_capslock == true){
    led_capslock = false;}
    }
  if (leds & (1 << USB_LED_SCROLL_LOCK)) {
    if (led_scrolllock == false){
    led_scrolllock = true;}
    } else {
    if (led_scrolllock == true){
    led_scrolllock = false;}
    }
}

uint32_t layer_state_set_kb(uint32_t state) {
  state = layer_state_set_user(state);
  layer = biton32(state);
  queue_for_send = true;
  return state;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  queue_for_send = true;
  switch (keycode) {
    case OLED_TOGG:
      if(!clock_set_mode){
        if (record->event.pressed) {
          oled_mode = (oled_mode + 1) % _NUM_OLED_MODES;
          draw_ui();
        }
      }
      return false;
    case CLOCK_SET:
      if (record->event.pressed) {
        if(clock_set_mode){
          pre_encoder_mode_change();
          clock_set_mode = false;
          encoder_mode = previous_encoder_mode;
          post_encoder_mode_change();

        }else{
          previous_encoder_mode = encoder_mode;
          pre_encoder_mode_change();
          clock_set_mode = true;
          encoder_mode = ENC_MODE_CLOCK_SET;
          post_encoder_mode_change();
        }
      }
      return false;
    case ENC_PRESS:
      if (record->event.pressed) {
        uint16_t mapped_code = handle_encoder_press();
        uint16_t held_keycode_timer = timer_read();
        if(mapped_code != 0){
          register_code(mapped_code);
          while (timer_elapsed(held_keycode_timer) < MEDIA_KEY_DELAY){ /* no-op */ }
          unregister_code(mapped_code);
        }
      } else {
        // Do something else when release
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

  return process_record_user(keycode, record);
}


void encoder_update_kb(uint8_t index, bool clockwise) {
  encoder_value = (encoder_value + (clockwise ? 1 : -1)) % 64;
  queue_for_send = true;
  if (index == 0) {
    if (layer == 0){
      uint16_t mapped_code = 0;
      if (clockwise) {
        mapped_code = handle_encoder_clockwise();
      } else {
        mapped_code = handle_encoder_ccw();
      }
      uint16_t held_keycode_timer = timer_read();
      if(mapped_code != 0){
        register_code(mapped_code);
        while (timer_elapsed(held_keycode_timer) < MEDIA_KEY_DELAY){ /* no-op */ }
        unregister_code(mapped_code);
      }
    } else {
      if(clockwise){
        change_encoder_mode(false);
      } else {
        change_encoder_mode(true);
      }
    }
  }
}

void dynamic_keymap_custom_reset(void){
  void *p = (void*)(DYNAMIC_KEYMAP_CUSTOM_BACKLIGHT);
	void *end = (void*)(DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR);
	while ( p != end ) {
		eeprom_update_byte(p, 0);
		++p;
	}
  eeprom_update_byte((uint8_t*)DYNAMIC_KEYMAP_ENABLED_ENCODER_MODES, 0x1F);
}

void save_backlight_config_to_eeprom(){
  eeprom_update_byte((uint8_t*)DYNAMIC_KEYMAP_CUSTOM_BACKLIGHT, kb_backlight_config.raw);
}

void load_custom_config(){
  kb_backlight_config.raw = eeprom_read_byte((uint8_t*)DYNAMIC_KEYMAP_CUSTOM_BACKLIGHT);
#ifdef DYNAMIC_KEYMAP_ENABLE
  oled_mode = eeprom_read_byte((uint8_t*)DYNAMIC_KEYMAP_DEFAULT_OLED);
  enabled_encoder_modes = eeprom_read_byte((uint8_t*)DYNAMIC_KEYMAP_ENABLED_ENCODER_MODES);
#endif
}

void eeprom_init_kb(void)
{
	// If the EEPROM has the magic, the data is good.
	// OK to load from EEPROM.
	if (eeprom_is_valid()) {
		load_custom_config();
	} else	{
		// If the EEPROM has not been saved before, or is out of date,
		// save the default values to the EEPROM. Default values
		// come from construction of the zeal_backlight_config instance.
		//backlight_config_save();
#ifdef DYNAMIC_KEYMAP_ENABLE
		// This resets the keymaps in EEPROM to what is in flash.
		dynamic_keymap_reset();
		// This resets the macros in EEPROM to nothing.
		dynamic_keymap_macro_reset();
    // Reset the custom stuff
    dynamic_keymap_custom_reset();
#endif
		// Save the magic number last, in case saving was interrupted
		eeprom_set_valid(true);
	}
}

void matrix_init_kb(void)
{
	eeprom_init_kb();
  rtcGetTime(&RTCD1, &last_timespec);
  queue_for_send = true;
  backlight_init_ports();
	matrix_init_user();
}


void matrix_scan_kb(void) {
  rtcGetTime(&RTCD1, &last_timespec);
  uint16_t minutes_since_midnight = last_timespec.millisecond / 1000 / 60;

  if (minutes_since_midnight != last_minute){
    last_minute = minutes_since_midnight;
    if(!oled_sleeping){
      queue_for_send = true;
    }
  }
#ifdef QWIIC_MICRO_OLED_ENABLE
  if (queue_for_send && oled_mode != OLED_OFF) {
    oled_sleeping = false;
    read_host_led_state();
    draw_ui();
    queue_for_send = false;
  }
  if (timer_elapsed(last_flush) > ScreenOffInterval && !oled_sleeping) {
    send_command(DISPLAYOFF);      /* 0xAE */
    oled_sleeping = true;
  }
#endif
}

