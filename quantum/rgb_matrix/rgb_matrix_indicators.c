#include <string.h>

#include "rgb_matrix_indicators.h"
#include "rgb_matrix.h"
#include "host.h"
#include "eeprom.h"
#include "eeconfig.h"
#include "debug.h"

t_rgb_indicator_matcher default_matchers[RGB_INDICATOR_MATCHERS_COUNT] = RGB_INDICATOR_MATCHERS;

static t_rgb_matrix_indicator_config rgb_matrix_indicators_config;

EECONFIG_DEBOUNCE_HELPER(rgb_matrix_indicators, EECONFIG_RGB_MATRIX_INDICATORS, rgb_matrix_indicators_config);

static void eeconfig_update_rgb_matrix_indicators_default(void) {
    rgb_matrix_indicators_config.initialised = true;
    rgb_matrix_indicators_config.matcher_count = RGB_INDICATOR_MATCHERS_COUNT;
    memcpy(rgb_matrix_indicators_config.matchers, default_matchers, RGB_INDICATOR_MATCHERS_COUNT * sizeof(t_rgb_indicator_matcher));
    eeconfig_flush_rgb_matrix_indicators(true);
}

void rgb_matrix_indicators_init(void) {
    if (!eeconfig_is_enabled()) {
        dprintf("eeconfig is not enabled.\n");
        eeconfig_init();
    }

    eeconfig_init_rgb_matrix_indicators();
    if (!rgb_matrix_indicators_config.initialised) {
        dprintf("rgb_matrix_indicators have not been initialised. Writing default values to EEPROM.\n");
        eeconfig_update_rgb_matrix_indicators_default();
    }
}

void rgb_matrix_indicators(void) {
    if (!rgb_matrix_indicators_kb()) return;
    led_t led_state = host_keyboard_led_state();
    for (size_t i = 0; i < rgb_matrix_indicators_config.matcher_count; i++) {
        t_rgb_indicator_matcher matcher = rgb_matrix_indicators_config.matchers[i];
        if (!(matcher.led_index >= 0 && matcher.led_index < RGB_MATRIX_LED_COUNT)) {
            dprintf("LED %d is out of range of the rgb matrix configuration\n", matcher.led_index);
        } else if (!(g_led_config.flags[matcher.led_index] & LED_FLAG_INDICATOR)) {
            dprintf("LED %d is not configured as an indicator but has indicator config provided\n", matcher.led_index);
        } else if((matcher.led_state.raw & led_state.raw) == matcher.led_state.raw) {
            uint8_t clamped_v = matcher.color.v;
            if(!matcher.override_brightness_limit && matcher.color.v > rgb_matrix_config.hsv.v)
                clamped_v = rgb_matrix_config.hsv.v;
            HSV color_hsv = {
                .h = matcher.color.h,
                .s = matcher.color.s,
                .v = clamped_v
            };
            RGB color = rgb_matrix_hsv_to_rgb(color_hsv);
            rgb_matrix_set_color(matcher.led_index, color.r, color.g, color.b);
        }
    }
}

__attribute__((weak)) bool rgb_matrix_indicators_kb(void) {
    return rgb_matrix_indicators_user();
}

__attribute__((weak)) bool rgb_matrix_indicators_user(void) {
    return true;
}

void rgb_matrix_indicators_advanced(effect_params_t *params) {
    /* special handling is needed for "params->iter", since it's already been incremented.
     * Could move the invocations to rgb_task_render, but then it's missing a few checks
     * and not sure which would be better. Otherwise, this should be called from
     * rgb_task_render, right before the iter++ line.
     */
    RGB_MATRIX_USE_LIMITS_ITER(min, max, params->iter - 1);
    rgb_matrix_indicators_advanced_kb(min, max);
}

__attribute__((weak)) bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    return rgb_matrix_indicators_advanced_user(led_min, led_max);
}

__attribute__((weak)) bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    return true;
}
