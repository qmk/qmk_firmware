#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "color.h"
#include "led.h"
#include "rgb_matrix_types.h"

#ifndef RGB_INDICATOR_MATCHERS_COUNT
    #define RGB_INDICATOR_MATCHERS_COUNT 0
#endif

#ifndef RGB_INDICATOR_MATCHERS_COUNT_MAX
    #define RGB_INDICATOR_MATCHERS_COUNT_MAX RGB_INDICATOR_MATCHERS_COUNT
#endif

#if RGB_INDICATOR_MATCHERS_COUNT > RGB_INDICATOR_MATCHERS_COUNT_MAX
    #error Number of indicator matchers, exceeds the number of dynamic indicator matchers
#endif

#if !defined(RGB_INDICATOR_MATCHERS) && (RGB_INDICATOR_MATCHERS_COUNT == 0)
    #define RGB_INDICATOR_MATCHERS {}
#elif !defined(RGB_INDICATOR_MATCHERS)
    #error No RGB indicator matchers have been defined, please define RGB_INDICATOR_MATCHERS
#endif

typedef struct PACKED {
    int led_index;
    led_t led_state;
    HSV color;
    bool override_brightness_limit;
} t_rgb_indicator_matcher;

typedef struct PACKED {
    bool initialised;
    uint8_t matcher_count;
    t_rgb_indicator_matcher matchers[RGB_INDICATOR_MATCHERS_COUNT_MAX];
} t_rgb_matrix_indicator_config;

void rgb_matrix_indicators_init(void);

// This runs after another backlight effect and replaces
// colors already set
void rgb_matrix_indicators(void);
bool rgb_matrix_indicators_kb(void);
bool rgb_matrix_indicators_user(void);

void rgb_matrix_indicators_advanced(effect_params_t *params);
bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max);
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max);
