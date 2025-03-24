/*
Copyright 2025 Mechlovin'

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "rev1.h"
#include "rgblight.h"

// Set values
void rgblight_config_set_value(uint8_t *data) {
    switch (data[0]) {
        case id_rgblight_logo_toggle:
            g_custom_rgblight_config.logo_enabled = data[1];
            break;
        case id_rgblight_ug_toggle:
            g_custom_rgblight_config.ug_enabled = data[1];
            break;
    }
    rgblight_config_save();
    update_rgblight();
}

// Get values
void rgblight_config_get_value(uint8_t *data) {
    data[1] = (data[0] == id_rgblight_logo_toggle) ? g_custom_rgblight_config.logo_enabled : g_custom_rgblight_config.ug_enabled;
}

// Save values to EEPROM
void rgblight_config_save(void) {
    eeconfig_update_user((uint32_t)g_custom_rgblight_config.logo_enabled | ((uint32_t)g_custom_rgblight_config.ug_enabled << 1));
}

// Load state from EEPROM
void rgblight_config_load(void) {
    uint32_t eeprom_data = eeconfig_read_user();
    g_custom_rgblight_config.logo_enabled = eeprom_data & 0x1;
    g_custom_rgblight_config.ug_enabled = (eeprom_data >> 1) & 0x1;
}

// Update UG LED and Logo LED
void update_rgblight(void) {
    if (g_custom_rgblight_config.logo_enabled || g_custom_rgblight_config.ug_enabled) {
        rgblight_enable_noeeprom(); // Không lưu vào EEPROM khi chỉ cập nhật trạng thái
        
        if (g_custom_rgblight_config.logo_enabled && g_custom_rgblight_config.ug_enabled) {
            rgblight_set_effect_range(0, RGBLIGHT_LED_COUNT);
        } else {
            if (g_custom_rgblight_config.logo_enabled) {
                rgblight_set_effect_range(UG_LED_COUNT, BLOCKER_LED_COUNT);
            } else {
                rgblight_sethsv_range(0, 0, 0, UG_LED_COUNT, RGBLIGHT_LED_COUNT);
            }
            if (g_custom_rgblight_config.ug_enabled) {
                rgblight_set_effect_range(0, UG_LED_COUNT);
            } else {
                rgblight_sethsv_range(0, 0, 0, 0, UG_LED_COUNT);
            }
        }
        
        // Force effect update to ensure static mode respond
        rgblight_mode_noeeprom(rgblight_get_mode());
    } else {
        rgblight_disable_noeeprom();
    }
}

void keyboard_post_init_user(void) {
    rgblight_config_load();
    update_rgblight();
}
