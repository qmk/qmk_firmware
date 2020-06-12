#include QMK_KEYBOARD_H
#include "settings.h"

void keyboard_post_init_user(void) {
	// read user config from eeprom
	user_config.raw = eeconfig_read_user();
}

void eeconfig_init_user(void) {
	user_config.raw = 0;
	user_config.dead_keys = true;
  user_config.switch_caps_esc = true;
	eeconfig_update_user(user_config.raw);
}
