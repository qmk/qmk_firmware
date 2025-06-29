#include <quantum.h>
#include "config.h"

#ifdef VIA_ENABLE
void via_init_kb(void) {
    custom_eeprom_init();
}

void via_config_set_value(uint8_t *data) {
    // data = [ value_id, value_data ]

    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_usb_sleep_toggle:
            keyboard_config.common.usb_sleep_toggle = *value_data;
            break;
        case id_deep_sleep_toggle:
            keyboard_config.common.deep_sleep_toggle = *value_data;
            break;
        case id_debounce_press:
            keyboard_config.common.debounce_press_ms = *value_data;
            break;
        case id_debounce_release:
            keyboard_config.common.debounce_release_ms = *value_data;
            break;
        case id_sleep_timeout:
            keyboard_config.common.sleep_timeout = *value_data + 1;
            break;
        case id_caps_indicator_type:
            keyboard_config.common.caps_indicator_type = *value_data;
            break;
        case id_sleep_toggle:
            keyboard_config.common.sleep_toggle = *value_data;
            break;

        case id_side_light_mode:
            keyboard_config.lights.side_mode = *value_data;
            break;
        case id_side_light_speed:
            keyboard_config.lights.side_speed = *value_data;
            break;
        case id_side_light_color:
            keyboard_config.lights.side_color = *value_data;
            break;
        case id_side_light_brightness:
            keyboard_config.lights.side_brightness = *value_data;
            break;

        case id_ambient_light_mode:
            keyboard_config.lights.ambient_mode = *value_data;
            break;
        case id_ambient_light_speed:
            keyboard_config.lights.ambient_speed = *value_data;
            break;
        case id_ambient_light_color:
            keyboard_config.lights.ambient_color = *value_data;
            break;
        case id_ambient_light_brightness:
            keyboard_config.lights.ambient_brightness = *value_data;
            break;
        case id_battery_indicator_brightness:
            keyboard_config.custom.battery_indicator_brightness = *value_data;
            break;
        case id_toggle_custom_keys_highlight:
            keyboard_config.custom.toggle_custom_keys_highlight = *value_data;
            break;
        case id_toggle_detect_numlock_state:
            keyboard_config.custom.detect_numlock_state = *value_data;
            break;
        case id_battery_indicator_numeric:
            keyboard_config.custom.battery_indicator_numeric = *value_data;
            break;
        case id_toggle_socd_indicator:
            keyboard_config.custom.show_socd_indicator = *value_data;
            break;
    }
}

void via_config_get_value(uint8_t *data) {
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch (*value_id) {
        case id_usb_sleep_toggle:
            *value_data = keyboard_config.common.usb_sleep_toggle;
            break;
        case id_deep_sleep_toggle:
            *value_data = keyboard_config.common.deep_sleep_toggle;
            break;
        case id_debounce_press:
            *value_data = keyboard_config.common.debounce_press_ms;
            break;
        case id_debounce_release:
            *value_data = keyboard_config.common.debounce_release_ms;
            break;
        case id_sleep_timeout:
            *value_data = keyboard_config.common.sleep_timeout - 1;
            break;
        case id_caps_indicator_type:
            *value_data = keyboard_config.common.caps_indicator_type;
            break;
        case id_sleep_toggle:
            *value_data = keyboard_config.common.sleep_toggle;
            break;

        case id_side_light_mode:
            *value_data = keyboard_config.lights.side_mode;
            break;
        case id_side_light_speed:
            *value_data = keyboard_config.lights.side_speed;
            break;
        case id_side_light_color:
            *value_data = keyboard_config.lights.side_color;
            break;
        case id_side_light_brightness:
            *value_data = keyboard_config.lights.side_brightness;
            break;

        case id_ambient_light_mode:
            *value_data = keyboard_config.lights.ambient_mode;
            break;
        case id_ambient_light_speed:
            *value_data = keyboard_config.lights.ambient_speed;
            break;
        case id_ambient_light_color:
            *value_data = keyboard_config.lights.ambient_color;
            break;
        case id_ambient_light_brightness:
            *value_data = keyboard_config.lights.ambient_brightness;
            break;
        case id_battery_indicator_brightness:
            *value_data = keyboard_config.custom.battery_indicator_brightness;
            break;
        case id_toggle_custom_keys_highlight:
            *value_data = keyboard_config.custom.toggle_custom_keys_highlight;
            break;
        case id_toggle_detect_numlock_state:
            *value_data = keyboard_config.custom.detect_numlock_state;
            break;

        case id_battery_indicator_numeric:
            *value_data = keyboard_config.custom.battery_indicator_numeric;
            break;
        case id_toggle_socd_indicator:
            *value_data = keyboard_config.custom.show_socd_indicator;
            break;
    }
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id = &(data[0]);
    uint8_t *channel_id = &(data[1]);

    uint8_t *value_id_and_data = &(data[2]);

    if (*channel_id == id_custom_channel) {
        switch (*command_id)

        {
            case id_custom_set_value: {
                via_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value: {
                via_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save: {
                save_config_to_eeprom();
                break;
            }
            default: {
                // Unhandled message.
                *command_id = id_unhandled;
                break;
            }
        }
        return;
    }

    // Return the unhandled state
    *command_id = id_unhandled;

    // DO NOT call raw_hid_send(data,length) here, let caller do this
}
#endif
