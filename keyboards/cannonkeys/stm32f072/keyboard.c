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
#include "version.h" // for QMK_BUILDDATE used in EEPROM magic

#include "via.h"
#define EEPROM_CUSTOM_BACKLIGHT (VIA_EEPROM_CUSTOM_CONFIG_ADDR)

backlight_config_t kb_backlight_config = {
  .enable = true,
  .breathing = true,
  .level = BACKLIGHT_LEVELS
};

void backlight_config_save(){
  eeprom_update_byte((uint8_t*)EEPROM_CUSTOM_BACKLIGHT, kb_backlight_config.raw);
}

void backlight_config_load(){
  kb_backlight_config.raw = eeprom_read_byte((uint8_t*)EEPROM_CUSTOM_BACKLIGHT);
}

// Called from via_init() if VIA_ENABLE
// Called from matrix_init_kb() if not VIA_ENABLE
void via_init_kb(void)
{
	// If the EEPROM has the magic, the data is good.
	// OK to load from EEPROM.
	if (via_eeprom_is_valid()) {
		backlight_config_load();
	} else	{
		// If the EEPROM has not been saved before, or is out of date,
		// save the default values to the EEPROM. Default values
		// come from construction of the backlight_config instance.
		backlight_config_save();

		// DO NOT set EEPROM valid here, let caller do this
	}
}

__attribute__ ((weak))
void matrix_init_board(void);

void matrix_init_kb(void){
	// If VIA is disabled, we still need to load backlight settings.
	// Call via_init_kb() the same way as via_init(), with setting
	// EEPROM valid afterwards.
#ifndef VIA_ENABLE
	via_init_kb();
	via_eeprom_set_valid(true);
#endif // VIA_ENABLE
      /* MOSI pin*/
#ifdef RGBLIGHT_ENABLE
    palSetPadMode(PORT_WS2812, PIN_WS2812, PAL_MODE_ALTERNATE(0));
    wait_ms(500);
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
        backlight_config_save();
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
        backlight_config_save();
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
        backlight_config_save();
      }
      return false;
    case BL_BRTG:
      if (record->event.pressed) {
        kb_backlight_config.breathing = !kb_backlight_config.breathing;
        breathing_toggle();
        backlight_config_save();
      }
      return false;
    default:
        break;
  }

  return process_record_user(keycode, record);;
}




//
// In the case of VIA being disabled, we still need to check if
// keyboard level EEPROM memory is valid before loading.
// Thus these are copies of the same functions in VIA, since
// the backlight settings reuse VIA's EEPROM magic/version,
// and the ones in via.c won't be compiled in.
//
// Yes, this is sub-optimal, and is only here for completeness
// (i.e. catering to the 1% of people that want wilba.tech LED bling
// AND want persistent settings BUT DON'T want to use dynamic keymaps/VIA).
//
#ifndef VIA_ENABLE

bool via_eeprom_is_valid(void)
{
    char *p = QMK_BUILDDATE; // e.g. "2019-11-05-11:29:54"
    uint8_t magic0 = ( ( p[2] & 0x0F ) << 4 ) | ( p[3]  & 0x0F );
    uint8_t magic1 = ( ( p[5] & 0x0F ) << 4 ) | ( p[6]  & 0x0F );
    uint8_t magic2 = ( ( p[8] & 0x0F ) << 4 ) | ( p[9]  & 0x0F );

    return (eeprom_read_byte( (void*)VIA_EEPROM_MAGIC_ADDR+0 ) == magic0 &&
            eeprom_read_byte( (void*)VIA_EEPROM_MAGIC_ADDR+1 ) == magic1 &&
            eeprom_read_byte( (void*)VIA_EEPROM_MAGIC_ADDR+2 ) == magic2 );
}

// Sets VIA/keyboard level usage of EEPROM to valid/invalid
// Keyboard level code (eg. via_init_kb()) should not call this
void via_eeprom_set_valid(bool valid)
{
    char *p = QMK_BUILDDATE; // e.g. "2019-11-05-11:29:54"
    uint8_t magic0 = ( ( p[2] & 0x0F ) << 4 ) | ( p[3]  & 0x0F );
    uint8_t magic1 = ( ( p[5] & 0x0F ) << 4 ) | ( p[6]  & 0x0F );
    uint8_t magic2 = ( ( p[8] & 0x0F ) << 4 ) | ( p[9]  & 0x0F );

    eeprom_update_byte( (void*)VIA_EEPROM_MAGIC_ADDR+0, valid ? magic0 : 0xFF);
    eeprom_update_byte( (void*)VIA_EEPROM_MAGIC_ADDR+1, valid ? magic1 : 0xFF);
    eeprom_update_byte( (void*)VIA_EEPROM_MAGIC_ADDR+2, valid ? magic2 : 0xFF);
}

void via_eeprom_reset(void)
{
    // Set the VIA specific EEPROM state as invalid.
    via_eeprom_set_valid(false);
    // Set the TMK/QMK EEPROM state as invalid.
    eeconfig_disable();
}

#endif // VIA_ENABLE