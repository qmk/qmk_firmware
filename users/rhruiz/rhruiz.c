#include "quantum.h"
#include "rhruiz.h"

void rhruiz_rgblight_reset(void) {
  rgblight_config_t eeprom_config;
  eeprom_config.raw = eeconfig_read_rgblight();

  if (!eeprom_config.enable) {
    rgblight_disable_noeeprom();
  }

  rgblight_mode_noeeprom(eeprom_config.mode);
  rgblight_sethsv_noeeprom(eeprom_config.hue, eeprom_config.sat, eeprom_config.val);
}

void rhruiz_change_leds_to(uint16_t hue, uint8_t sat) {
  rgblight_config_t eeprom_config;
  eeprom_config.raw = eeconfig_read_rgblight();

  if (rgblight_get_mode() == false) {
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    for (uint8_t i = RGBLED_NUM ; i-- > 0 ; ) {
      if (i == 8 || i == 15) {
        continue;
      }

      sethsv(0, 0, 0, (LED_TYPE *)&led[i]);
    }
  }

  sethsv(hue, sat, eeprom_config.val, (LED_TYPE *)&led[8]);
  sethsv(hue, sat, eeprom_config.val, (LED_TYPE *)&led[15]);
  rgblight_set();
}
