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
#include "rgb_theme.h"
#include "rgb_bs.h"

#if defined(RGBLIGHT_ENABLE)
extern rgblight_config_t rgblight_config;
#elif defined(RGB_MATRIX_ENABLE)
extern rgb_config_t rgb_matrix_config;
extern bool g_suspend_state;
extern led_config_t g_led_config;
#endif

#if defined(RGB_THEME_ENABLE)
// Should be rgb_theme.c
#define RGB_THEME(name) const rgb_theme_t RGB_##name
#define RGB_THEME_IMPLS
#include "rgb_theme_user.inc"
#undef RGB_THEME_IMPLS
#undef RGB_THEME

#define RGB_THEME(name) [RGB_THEME_##name] = &RGB_##name,
const rgb_theme_t *themes[] = {
    #include "rgb_theme_user.inc"
};
#undef RGB_THEME

// Userspace loose colors
rgb_theme_color_t default_adjust = { HSV_SPRINGGREEN };
#endif

void keyboard_post_init_rgb(void) {
    layer_state_set_user(layer_state);
}

#if defined(RGB_THEME_ENABLE)
void set_rgb_theme(uint8_t index) {
    if (!user_config.rgb_layer_change) {
        user_config.rgb_layer_change = true;
    }
    user_config.rgb_theme = index;
    dprintf("rgb theme [EEPROM]: %u\n", user_config.rgb_theme);
    eeconfig_update_user(user_config.raw);
}

rgb_theme_t get_rgb_theme(void) {
    return *themes[user_config.rgb_theme];
}

void rgb_theme_step(void) {
    uint8_t current = user_config.rgb_theme;
    current = (current + 1) % RGB_THEME_MAX;
    set_rgb_theme(current);
}

void rgb_theme_step_reverse(void) {
    uint8_t current = user_config.rgb_theme;
    current = (current - 1) % RGB_THEME_MAX;
    set_rgb_theme(current);
}

rgb_theme_color_t get_rgb_theme_color(uint8_t index) {
    rgb_theme_t theme = get_rgb_theme();
    size_t rgb_theme_color_max = sizeof theme.colors / sizeof *theme.colors;

    if (index == _ADJUST) {
        return default_adjust;
    } else {
        return **(theme.colors + (index % rgb_theme_color_max));
    }
};

void rgb_theme_layer(layer_state_t state) {
    uint8_t rgb_color_index = get_highest_layer(state);
    HSV color = get_rgb_theme_color(rgb_color_index);
#if defined(RGBLIGHT_ENABLE)
    color.v = rgblight_config.val;
#elif defined(RGB_MATRIX_ENABLE)
    color.v = rgb_matrix_config.hsv.v;
#endif
    rgb_layer_helper( color.h, color.s, color.v );
}
#endif

#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_layer_helper (uint8_t red, uint8_t green, uint8_t blue, uint8_t led_type) {
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        if (!HAS_ANY_FLAGS(g_led_config.flags[i], led_type)) {
            rgb_matrix_set_color( i, red, green, blue );
        }
    }
}

void rgb_matrix_cycle_flag (void) {
    switch (rgb_matrix_get_flags()) {
        case LED_FLAG_ALL:
            rgb_matrix_set_flags(LED_FLAG_KEYS);
            rgb_matrix_set_color_all(0, 0, 0);
            break;
        case LED_FLAG_KEYS:
            rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
            rgb_matrix_set_color_all(0, 0, 0);
            break;
        case LED_FLAG_UNDERGLOW:
            rgb_matrix_set_flags(LED_FLAG_NONE);
            rgb_matrix_set_color_all(0, 0, 0);
            break;
        default:
            rgb_matrix_set_flags(LED_FLAG_ALL);
            rgb_matrix_enable();
            break;
    }
}
#endif

void rgb_layer_helper(uint8_t hue, uint8_t sat, uint8_t val) {
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    rgblight_sethsv_noeeprom(hue, sat, val);
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_layer_helper(0, 0, 0, rgb_matrix_get_flags());
#endif
}
#endif

layer_state_t layer_state_set_rgb(layer_state_t state) {
#if defined(RGB_THEME_ENABLE)
    if (user_config.rgb_layer_change) {
        rgb_theme_layer(state);
    }
#endif // RGBLIGHT_ENABLE
    return state;
}
