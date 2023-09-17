#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "color.h"

typedef struct {
    int led_index;
    led_t led_state;
    HSV color;
    bool override_brightness_limit;
} t_rgb_indicator_matcher;

#ifndef INDICATOR_MATCHERS_COUNT
    #define INDICATOR_MATCHERS_COUNT 0
#endif

#ifndef INDICATOR_MATCHERS_COUNT_MAX
    #define INDICATOR_MATCHERS_COUNT_MAX INDICATOR_MATCHERS_COUNT
#endif

#if INDICATOR_MATCHERS_COUNT > INDICATOR_MATCHERS_COUNT_MAX
    #error Number of indicator matchers, exceeds the number of dynamic indicator matchers
#endif

extern t_rgb_indicator_matcher g_rgb_indicator_matchers[INDICATOR_MATCHERS_COUNT_MAX];

void rgb_matrix_indicators_init(void);

// This runs after another backlight effect and replaces
// colors already set
void rgb_matrix_indicators(void);
bool rgb_matrix_indicators_kb(void);
bool rgb_matrix_indicators_user(void);

void rgb_matrix_indicators_advanced(effect_params_t *params);
bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max);
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max);
