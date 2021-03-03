/* Copyright 2020 Brandon Schlack
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "brandonschlack.h"

user_config_t user_config;
#ifdef STOPLIGHT_LED
static stoplight_led_t stoplight_led;
#endif

/**
 * Resets user config in EEPROM
 *
 * Default is use rgb for layer indication
 */
void eeconfig_init_user(void) {
    user_config.raw = 0;
    user_config.rgb_layer_change = true;
    user_config.rgb_theme = 0;
    eeconfig_update_user(user_config.raw);
}

__attribute__((weak))
void matrix_init_keymap(void){ }

void matrix_init_user(void) {
    matrix_init_keymap();
}

__attribute__((weak))
void keyboard_post_init_keymap(void){ }

/**
 * Reads user config from EEPROM,
 * calls RGB init if RGBs enabled
 */
void keyboard_post_init_user(void){
    // Read the user config from EEPROM
    user_config.raw = eeconfig_read_user();
    // Do Stoplight Animation if enabled
#ifdef STOPLIGHT_LED
    led_stoplight_start();
#endif
    // Do RGB things if RGBs enabled
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    keyboard_post_init_rgb();
#endif
    keyboard_post_init_keymap();
}

__attribute__ ((weak))
void shutdown_keymap(void) {}

/**
 * On shutdown,
 * If RGBs enabled,
 * then set RGB color to Red
 */
void shutdown_user (void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_sethsv_noeeprom(0, 255, 127);
#endif // RGBLIGHT_ENABLE
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_color_all( 0xFF, 0x00, 0x00 );
#endif //RGB_MATRIX_ENABLE
    shutdown_keymap();
}

__attribute__ ((weak))
void suspend_power_down_keymap(void) {}

/**
 * Set rgb_matrix suspend state to true if not already
 */
void suspend_power_down_user(void) {
#ifdef RGB_MATRIX_ENABLE
    if (!g_suspend_state) {
        rgb_matrix_set_suspend_state(true);
    }
#endif //RGB_MATRIX_ENABLE
    suspend_power_down_keymap();
}

__attribute__ ((weak))
void suspend_wakeup_init_keymap(void) {}

/**
 * Set rgb_matrix suspend state to false if not already
 */
void suspend_wakeup_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
    if (g_suspend_state) {
        rgb_matrix_set_suspend_state(false);
    }
#endif //RGB_MATRIX_ENABLE
    suspend_wakeup_init_keymap();
}

__attribute__ ((weak))
void matrix_scan_keymap(void) {}

/**
 * Checks for Super CMD↯TAB
 */
void matrix_scan_user(void) {
    matrix_scan_cmd_tab();
#ifdef STOPLIGHT_LED
    matrix_scan_led_stoplight();
#endif
    matrix_scan_keymap();
}

__attribute__ ((weak))
layer_state_t default_layer_state_set_keymap(layer_state_t state) {
    return state;
}

/**
 * For macropads, if a new default layer is set from DF()
 * then automatically set that layer with layer_move()
 */
layer_state_t default_layer_state_set_user(layer_state_t state) {
#if defined(IS_MACROPAD)
    layer_move(get_highest_layer(state));
#endif
    return default_layer_state_set_keymap(state);
}

__attribute__ ((weak))
layer_state_t layer_state_set_keymap(layer_state_t state) {
    return state;
}

/**
 * Do RGB things (like layer indication) on layer change
 */
layer_state_t layer_state_set_user(layer_state_t state) {
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    state = layer_state_set_rgb(state);
#endif // RGBLIGHT_ENABLE
    return layer_state_set_keymap(state);
}

__attribute__((weak)) bool led_update_keymap(led_t led_state) { return true; }

bool led_update_user(led_t led_state) {
#ifdef STOPLIGHT_LED
    if (stoplight_led.is_active) {
        return false;
    }
#endif
    return led_update_keymap(led_state);
}

#ifdef STOPLIGHT_LED
void led_stoplight_start(void) {
    writePin(TOP_LED, LED_ON(false));
    writePin(MIDDLE_LED, LED_ON(false));
    writePin(BOTTOM_LED, LED_ON(false));

    stoplight_led.is_active = true;
    stoplight_led.timer = timer_read();
};

void led_stoplight_set(pin_t pin) {
    writePin(pin, LED_ON(true));
};

void led_stoplight_end(void) {
    // Reset timer and status variables
    stoplight_led.is_active = false;
    stoplight_led.index = 0;
    stoplight_led.timer = 0;
    led_update_kb(host_keyboard_led_state());
};

void matrix_scan_led_stoplight(void) {
    if (stoplight_led.is_active) {
        if (timer_elapsed(stoplight_led.timer) > (1000 * (stoplight_led.index + 1))) {
            switch (stoplight_led.index){
                case 0:
                    led_stoplight_set(TOP_LED);
                    stoplight_led.index++;
                    break;
                case 1:
                    led_stoplight_set(MIDDLE_LED);
                    stoplight_led.index++;
                    break;
                case 2:
                    led_stoplight_set(BOTTOM_LED);
                    stoplight_led.index++;
                    break;
                default:
                    led_stoplight_end();
                    break;
            }
        }
    }
};
#endif
