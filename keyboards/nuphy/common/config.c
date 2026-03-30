#include "config.h"
#include "rf_driver.h"

#ifdef VIA_ENABLE
#    include "eeprom.h"
#    include "via.h"
#else
#    include "eeconfig.h"
#endif

// STATE vars
extern bool            f_deep_sleep_show;
extern bool            f_usb_sleep_show;
extern DEV_INFO_STRUCT dev_info;
RGB                    bat_pct_rgb       = {.r = 0x80, .g = 0x80, .b = 0x00};
uint16_t               rgb_led_last_act  = 0;
uint16_t               side_led_last_act = 0;

__attribute((weak)) void pwr_rgb_led_on(void) {}
__attribute((weak)) void pwr_rgb_led_off(void) {}
__attribute((weak)) void pwr_side_led_on(void) {}
__attribute((weak)) void pwr_side_led_off(void) {}

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
    keyboard_config.lights.side_mode             = DEFAULT_SIDE_MODE;
    keyboard_config.lights.side_brightness       = DEFAULT_SIDE_BRIGHTNESS;
    keyboard_config.lights.side_speed            = DEFAULT_SIDE_SPEED;
    keyboard_config.lights.side_rgb              = DEFAULT_SIDE_RGB;
    keyboard_config.lights.side_color            = DEFAULT_SIDE_COLOR;
    keyboard_config.lights.ambient_mode          = DEFAULT_AMBIENT_MODE;
    keyboard_config.lights.ambient_brightness    = DEFAULT_AMBIENT_BRIGHTNESS;
    keyboard_config.lights.ambient_speed         = DEFAULT_AMBIENT_SPEED;
    keyboard_config.lights.ambient_rgb           = DEFAULT_AMBIENT_RGB;
    keyboard_config.lights.ambient_color         = DEFAULT_AMBIENT_COLOR;
    keyboard_config.lights.right_side_mode       = DEFAULT_RIGHT_SIDE_MODE;
    keyboard_config.lights.side_speed            = DEFAULT_SIDE_SPEED;
    keyboard_config.lights.side_rgb              = DEFAULT_SIDE_RGB;
    keyboard_config.lights.side_color            = DEFAULT_SIDE_COLOR;
    keyboard_config.lights.right_side_mode       = DEFAULT_RIGHT_SIDE_MODE;
    keyboard_config.lights.right_side_brightness = DEFAULT_RIGHT_SIDE_BRIGHTNESS;
    keyboard_config.lights.right_side_speed      = DEFAULT_RIGHT_SIDE_SPEED;
    keyboard_config.lights.right_side_rgb        = DEFAULT_RIGHT_SIDE_RGB;
    keyboard_config.lights.right_side_color      = DEFAULT_RIGHT_SIDE_COLOR;
    keyboard_config.lights.ambient_mode          = DEFAULT_AMBIENT_MODE;
    keyboard_config.lights.ambient_brightness    = DEFAULT_AMBIENT_BRIGHTNESS;
    keyboard_config.lights.ambient_speed         = DEFAULT_AMBIENT_SPEED;
    keyboard_config.lights.ambient_rgb           = DEFAULT_AMBIENT_RGB;
    keyboard_config.lights.ambient_color         = DEFAULT_AMBIENT_COLOR;
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

uint32_t get_sleep_timeout(void) {
    if (!keyboard_config.common.sleep_toggle) return 0;
    return keyboard_config.common.sleep_timeout * 60 * 1000 / TIMER_STEP;
}

void toggle_deep_sleep(void) {
    f_deep_sleep_show                        = 1;
    keyboard_config.common.deep_sleep_toggle = !keyboard_config.common.deep_sleep_toggle;
    save_config_to_eeprom();
}

void toggle_power_on_animation(void) {
    keyboard_config.common.power_on_animation = !keyboard_config.common.power_on_animation;
    save_config_to_eeprom();
}

/**
 * @brief toggle usb sleep on/off
 */
void toggle_usb_sleep(void) {
    f_usb_sleep_show                        = 1;
    keyboard_config.common.usb_sleep_toggle = !keyboard_config.common.usb_sleep_toggle;
    save_config_to_eeprom();
}

/**
 * @brief Toggle caps indication between side led / under key / off
 */
void toggle_caps_indication(void) {
    if (keyboard_config.common.caps_indicator_type == CAPS_INDICATOR_OFF) {
        keyboard_config.common.caps_indicator_type = CAPS_INDICATOR_SIDE; // set to initial state, when last state reached
    } else {
        keyboard_config.common.caps_indicator_type += 1;
    }

    save_config_to_eeprom();
}

/**
 * @brief Updates RGB value for current bat percentage.
 */
void update_bat_pct_rgb(void) {
    uint8_t bat_pct = dev_info.rf_battery;

    if (bat_pct > 100) {
        bat_pct = 100;
    }
    // 120 hue is green, 0 is red on a 360 degree wheel but QMK is a uint8_t
    // so it needs to convert to relative to 255 - so green is actually 85.
    uint8_t h = 85;
    if (bat_pct <= 20) {
        h = 0; // red
    } else if (bat_pct <= 40) {
        h = 21; // orange
    } else if (bat_pct <= 80) {
        h = 43; // yellow
    }

    HSV hsv = {
        .h = h,
        .s = 255,
        .v = 128, // 50% max brightness
    };

    bat_pct_rgb = hsv_to_rgb_nocie(hsv); // this results in same calculation as color pickers.
}

/**
 * @brief Wrapper for rgb_matrix_set_color for sleep.c logic usage.
 */
void user_set_rgb_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    if (red || green || blue) {
        rgb_led_last_act = 0;
        pwr_rgb_led_on(); // turn on LEDs
    }
    rgb_matrix_set_color(index, red, green, blue);
}

/**
 * @brief Handle LED power
 * @note Turn off LEDs if not used to save some power. This is ported
 *       from older Nuphy leaks.
 */
void led_power_handle(void) {
    static uint32_t interval = 0;

    if (timer_elapsed32(interval) < 500) // only check once in a while, less flickering for unhandled cases
        return;

    interval = timer_read32();

    if (rgb_led_last_act > 100) { // 10ms intervals
        if (rgb_matrix_is_enabled() && rgb_matrix_get_val() != 0) {
            pwr_rgb_led_on();
        } else { // brightness is 0 or RGB off.
            pwr_rgb_led_off();
        }
    }

    if (side_led_last_act > 100) { // 10ms intervals
        if (keyboard_config.lights.side_brightness == 0) {
            pwr_side_led_off();
        } else {
            pwr_side_led_on();
        }
    }
}

uint8_t get_led_index(uint8_t row, uint8_t col) {
    return g_led_config.matrix_co[row][col];
}

/**
 * @brief get LED if for first digit from double digit number. Esc = 0
 */
uint8_t two_digit_decimals_led(uint8_t value) {
    if (value > 99) {
        return get_led_index(0, 0);
    }

    uint8_t dec = value / 10;

    uint8_t dec_led_idx = get_led_index(0, dec);

    return dec_led_idx;
}

/**
 * @brief get LED if for second digit from double digit number 0 = 0
 */
uint8_t two_digit_ones_led(uint8_t value) {
    if (value > 99) {
        return get_led_index(0, 0);
    }

    uint8_t ones = value % 10;
    if (ones == 0) {
        ones = 10;
    }
    uint8_t ones_led_idx = get_led_index(1, ones);

    return ones_led_idx;
}

void adjust_sleep_timeout(uint8_t dir) {
    if (keyboard_config.common.sleep_toggle) {
        if (keyboard_config.common.sleep_timeout > 1 && !dir) {
            keyboard_config.common.sleep_timeout -= SLEEP_TIMEOUT_STEP;
        } else if (keyboard_config.common.sleep_timeout < 60 && dir) {
            keyboard_config.common.sleep_timeout += SLEEP_TIMEOUT_STEP;
        }
        save_config_to_eeprom();
    }
}
