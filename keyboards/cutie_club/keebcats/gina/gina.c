/*
Copyright 2023 Cutie Club

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

#include "gina.h"

#include "indicator_leds.h"

#include "via.h"
#include "i2c_master.h"
#include "quantum/rgblight/rgblight.h"

static keyboard_config_t keyboard_config;

void keyboard_pre_init_kb(void) {
    i2c_init();
    indicator_leds_init();

    keyboard_config.raw = eeconfig_read_kb();

    enum indicator_key indicator_key = keyboard_config.indicator_key;

    if(indicator_key != NUM_LOCK && indicator_key != SCROLL_LOCK && indicator_key != CAPS_LOCK) {
        indicator_key = DEFAULT_INDICATOR_LED;
        keyboard_config.indicator_key = indicator_key;
        eeconfig_update_kb(keyboard_config.raw);
    }
    set_enabled_indicator_key(keyboard_config.indicator_key);
}

#ifndef VIA_ENABLED
enum via_gina_property {
    id_indicator_key = 1,
    id_rgb_brightness,
    id_rgb_colour
};

#define RGB_BRIGHTNESS_TO_UINT8(brightness) (((uint16_t)brightness * UINT8_MAX) / RGBLIGHT_LIMIT_VAL)
#define UINT8_TO_RGB_BRIGHTNESS(data) (((uint16_t)data * RGBLIGHT_LIMIT_VAL) / UINT8_MAX)

static void handle_set(enum via_gina_property property, uint8_t* property_data) {
    switch(property) {
        case id_indicator_key:
            keyboard_config.indicator_key = *property_data;
            set_enabled_indicator_key(keyboard_config.indicator_key);
            break;
        case id_rgb_brightness:
            if(!rgblight_is_enabled()) rgblight_enable_noeeprom();
            rgblight_sethsv_noeeprom(rgblight_get_hue(), rgblight_get_sat(), UINT8_TO_RGB_BRIGHTNESS(property_data[0]));
            break;
        case id_rgb_colour:
            if(!rgblight_is_enabled()) rgblight_enable_noeeprom();
            rgblight_sethsv_noeeprom(property_data[0], property_data[1], rgblight_get_val());
            break;
    }
}

static void handle_get(enum via_gina_property property, uint8_t* property_data) {
    switch(property) {
        case id_indicator_key:
            *property_data = get_enabled_indicator_key();
            break;
        case id_rgb_brightness:
            property_data[0] = RGB_BRIGHTNESS_TO_UINT8(rgblight_get_val());
            break;
        case id_rgb_colour:
            property_data[0] = rgblight_get_hue();
            property_data[1] = rgblight_get_sat();
            break;
    }
}

static void handle_save(void) {
    eeconfig_update_kb(keyboard_config.raw);

    rgblight_disable_noeeprom();
    eeconfig_update_rgblight_current();
    SYNCHRONISE_HOST_LED_STATUS();
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    uint8_t *channel_id = &(data[1]);
    if(*channel_id != id_custom_channel) return;

    uint8_t *command_id = &(data[0]);

    uint8_t *property_id = &((&(data[2]))[0]);
    uint8_t *property_data = &((&(data[2]))[1]);

    switch (*command_id) {
        case id_custom_set_value:
            handle_set(*property_id, property_data);
            break;

        case id_custom_get_value:
            handle_get(*property_id, property_data);
            break;

        case id_custom_save:
            handle_save();
            break;

        default:
            *command_id = id_unhandled;
            break;
    }
}

#endif
