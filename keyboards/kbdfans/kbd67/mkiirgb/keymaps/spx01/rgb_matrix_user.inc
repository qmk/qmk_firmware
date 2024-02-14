/* Copyright 2022 spx01 (@spx01)
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

RGB_MATRIX_EFFECT(RGB_STATIC)

#define UNWRAP_RGB_PARAMS(x) x[0], x[1], x[2]
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

/* eeprom saved data structure */
typedef struct {
    union {
        uint32_t whole;
        uint8_t  rgb[3];
    };
} UserData;

uint8_t g_rgb_static_color[3];

/* save current colors to eeprom */
void RGB_STATIC_save_eeprom(void) {
    UserData data = {0};
    for (int8_t i = 0; i < 3; ++i) {
        data.rgb[i] = g_rgb_static_color[i];
    }
    eeconfig_update_user(data.whole);
}

/* initialize by loading the eeprom colors */
static void RGB_STATIC_init(void) {
    UserData data;
    data.whole = eeconfig_read_user();
    for (int8_t i = 0; i < 3; ++i) {
        g_rgb_static_color[i] = data.rgb[i];
    }
}

/* reset colors to eeprom values */
void RGB_STATIC_reset(void) {
    RGB_STATIC_init();
}

static bool RGB_STATIC(effect_params_t *params) {
    if (params->init) {
        RGB_STATIC_init();
    }
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        rgb_matrix_set_color(i, UNWRAP_RGB_PARAMS(g_rgb_static_color));
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#endif
#undef UNWRAP_RGB_PARAMS
