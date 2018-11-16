#include "quantum.h"
#include "rhruiz.h"

bool rhruiz_state_changed;

void rhruiz_state_will_change() {
  rhruiz_state_changed = true;
}

void rhruiz_state_did_change() {
  rhruiz_state_changed = false;
}

void rhruiz_matrix_init() {
  rhruiz_state_did_change();
}

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

  if (rhruiz_state_changed) {
    if (!eeprom_config.enable) {
      rgblight_enable_noeeprom();
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
      for (uint8_t i = RGBLED_NUM ; i-- > 0 ; ) {
        if (i == 8 || i == 15) {
          continue;
        }

        sethsv(0, 0, 0, (LED_TYPE *)&led[i]);
      }
    }

    rhruiz_state_changed = false;
  }

  sethsv(hue, sat, eeprom_config.val, (LED_TYPE *)&led[8]);
  sethsv(hue, sat, eeprom_config.val, (LED_TYPE *)&led[15]);
  rgblight_set();
}
