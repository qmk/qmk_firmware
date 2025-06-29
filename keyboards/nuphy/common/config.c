#include "config.h"
#ifdef VIA_ENABLE
#    include "eeprom.h"
#    include "via.h"
#else
#    include "eeconfig.h"
#endif

uint32_t read_custom_config(void *data, uint32_t offset, uint32_t length) {
#ifdef VIA_ENABLE
    return via_read_custom_config(data, offset, length);
#else
    return eeconfig_read_kb_datablock(data, offset, length);
#endif
}

uint32_t write_custom_config(const void *data, uint32_t offset, uint32_t length) {
#ifdef VIA_ENABLE
    return via_update_custom_config(data, offset, length);
#else
    return eeconfig_update_kb_datablock(data, offset, length);
#endif
}

void load_config_from_eeprom(void) {
    read_custom_config(&keyboard_config, 0, sizeof(keyboard_config));
}

void save_config_to_eeprom(void) {
    write_custom_config(&keyboard_config, 0, sizeof(keyboard_config));
}

__attribute__((weak)) void init_keyboard_config(void) {
    keyboard_config.common.sleep_toggle        = DEFAULT_SLEEP_TOGGLE;
    keyboard_config.common.usb_sleep_toggle    = DEFAULT_USB_SLEEP_TOGGLE;
    keyboard_config.common.deep_sleep_toggle   = DEFAULT_DEEP_SLEEP_TOGGLE;
    keyboard_config.common.sleep_timeout       = DEFAULT_SLEEP_TIMEOUT;
    keyboard_config.common.debounce_press_ms   = DEBOUNCE;
    keyboard_config.common.debounce_release_ms = RELEASE_DEBOUNCE;
    keyboard_config.common.caps_indicator_type = DEFAULT_CAPS_INDICATOR_TYPE;
    // lights
    keyboard_config.lights.side_mode          = DEFAULT_SIDE_MODE;
    keyboard_config.lights.side_brightness    = DEFAULT_SIDE_BRIGHTNESS;
    keyboard_config.lights.side_speed         = DEFAULT_SIDE_SPEED;
    keyboard_config.lights.side_rgb           = DEFAULT_SIDE_RGB;
    keyboard_config.lights.side_color         = DEFAULT_SIDE_COLOR;
    keyboard_config.lights.ambient_mode       = DEFAULT_AMBIENT_MODE;
    keyboard_config.lights.ambient_brightness = DEFAULT_AMBIENT_BRIGHTNESS;
    keyboard_config.lights.ambient_speed      = DEFAULT_AMBIENT_SPEED;
    keyboard_config.lights.ambient_rgb        = DEFAULT_AMBIENT_RGB;
    keyboard_config.lights.ambient_color      = DEFAULT_AMBIENT_COLOR;
    // custom
    keyboard_config.custom.battery_indicator_brightness = DEFAULT_BATTERY_INDICATOR_BRIGHTNESS;
    keyboard_config.custom.toggle_custom_keys_highlight = DEFAULT_LIGHT_CUSTOM_KEYS;
    keyboard_config.custom.detect_numlock_state         = DEFAULT_DETECT_NUMLOCK;
    keyboard_config.custom.battery_indicator_numeric    = DEFAULT_BATTERY_INDICATOR_NUMERIC;
    keyboard_config.custom.show_socd_indicator          = DEFAULT_SHOW_SOCD_INDICATOR;
}

__attribute__((weak)) void custom_eeprom_init(void) {
    if (eeconfig_is_enabled()) {
        load_config_from_eeprom();
    } else {
        init_keyboard_config();
        keyboard_config.been_initiated = 0x45;
        save_config_to_eeprom();
    }
};

