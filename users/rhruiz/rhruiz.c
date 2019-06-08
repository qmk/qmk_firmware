#include "quantum.h"
#include "rhruiz.h"

__attribute__ ((weak))
void rhruiz_update_layer_colors(void) {
}

uint32_t rhruiz_layer_state_set_user(uint32_t state) {
  static uint32_t last_state = 0;

  if (state != last_state) {
    switch(biton32(state)) {
      case _BL:
      case _VIM_EMACS:
      case _MOUSE:
      case _KEY_OVERRIDE:
        state = state & (0UL << _VIM_EMACS) & (0UL << _MOUSE) & (0UL << _KEY_OVERRIDE);
        rhruiz_rgblight_reset();
        break;

      case _FN1:
      case _FN2:
        state = state | (1UL << _VIM_EMACS) | (1UL << _MOUSE) | (1UL << _KEY_OVERRIDE);
        rhruiz_update_layer_colors();
        break;

      case _CFG:
        rhruiz_update_layer_colors();
        break;

      default:
        break;
    }

    last_state = state;
  }

  return state;
}

void rhruiz_rgblight_reset(void) {
#ifdef RGBLIGHT_ENABLE
  rgblight_config_t eeprom_config;
  eeprom_config.raw = eeconfig_read_rgblight();

  if (!eeprom_config.enable) {
    rgblight_disable_noeeprom();
  }

  rgblight_mode_noeeprom(eeprom_config.mode);
  rgblight_sethsv_noeeprom(eeprom_config.hue, eeprom_config.sat, eeprom_config.val);
#endif
}

__attribute__ ((weak))
bool rhruiz_is_layer_indicator_led(uint8_t index) {
  return index == 0 || index == RGBLED_NUM / 2 - 1;
}

void rhruiz_change_leds_to(uint16_t hue, uint8_t sat) {
#ifdef RGBLIGHT_ENABLE
  rgblight_config_t eeprom_config;
  eeprom_config.raw = eeconfig_read_rgblight();
  LED_TYPE *ledp;

  #ifdef RGBLIGHT_LED_MAP
    LED_TYPE led0[RGBLED_NUM];
    for(uint8_t i = 0; i < RGBLED_NUM; i++) {
        led0[i] = led[pgm_read_byte(&led_map[i])];
    }
    ledp = led0;
  #else
    ledp = led;
  #endif

  bool rgbmode = rgblight_get_mode();

  for (uint8_t i = RGBLED_NUM ; i-- > 0 ; ) {
    if (rhruiz_is_layer_indicator_led(i)) {
      sethsv(hue, sat, eeprom_config.val, (LED_TYPE *)&ledp[i]);
    } else {
      if (rgbmode == false) {
        sethsv(0, 0, 0, (LED_TYPE *)&ledp[i]);
      }
    }
  }

  #ifdef RGBW
    ws2812_setleds_rgbw(ledp, RGBLED_NUM);
  #else
    ws2812_setleds(ledp, RGBLED_NUM);
  #endif
#endif
}

#ifdef RAW_ENABLE
void raw_hid_receive( uint8_t *data, uint8_t length ) {
	uint8_t *command_id = &(data[0]);
	uint8_t *command_data = &(data[1]);

	switch ( *command_id ) {
		case id_get_keyboard_value: {
			if ( command_data[0] == id_uptime ) {
				uint32_t value = timer_read32();
				command_data[1] = (value >> 24 ) & 0xFF;
				command_data[2] = (value >> 16 ) & 0xFF;
				command_data[3] = (value >> 8 ) & 0xFF;
				command_data[4] = value & 0xFF;
			} else {
				*command_id = id_unhandled;
			}
			break;
		}

    case id_bootloader_jump: {
			raw_hid_send( data, length );
			wait_ms(100);
			bootloader_jump();
			break;
    }

    case id_rgblight_color: {
      uint16_t hue = ((uint16_t)command_data[0] << 8) | command_data[1];
      uint8_t sat = command_data[2];
      rhruiz_change_leds_to(hue, sat);

      break;
    }

    case id_rgblight_reset: {
#ifdef RGBLIGHT_ENABLE
      rhruiz_rgblight_reset();
#endif
      break;
    }

    case id_backlight_toggle: {
#ifdef BACKLIGHT_ENABLE
      backlight_toggle();
#endif
      break;
    }

    case id_rgblight_toggle: {
#ifdef RGBLIGHT_ENABLE
      rgblight_toggle();
#endif
      break;
    }
  }

	raw_hid_send( data, length );
}
#endif
