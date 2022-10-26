// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include "color.h"
/*
****************** rgb indicator mode *****************
|-----------------|-----------------------------------|
|   mode number   |   mode name                       |
|-----------------|-----------------------------------|
|        1        | RGB_INDICATOR_MODE_PLAIN          |
|        2        | RGB_INDICATOR_MODE_FADE_IN        |
|        3        | RGB_INDICATOR_MODE_FADE_OUT       |
|        4        | RGB_INDICATOR_MODE_FADE_INOUT     |
|        5        | RGB_INDICATOR_MODE_GRADIENT       |
|        6        | RGB_INDICATOR_MODE_RANDOM_HUE     |
|-----------------|-----------------------------------|
*/

#ifndef RGB_INDICATOR_SELECT_PIN
#    define RGB_INDICATOR_SELECT_PIN GP27
#endif
#ifndef RGB_INDICATOR_TEST_PIN
#    define RGB_INDICATOR_TEST_PIN GP23
#endif
#define RGB_INDICATOR_EFFECT_MAX 6
#ifndef RGB_INDICATOR_GLOBAL_CURRENT
#    define RGB_INDICATOR_GLOBAL_CURRENT LED_CURRENT_MAX
#endif

typedef union {
    uint32_t raw;
    struct PACKED {
        bool    enable : 1;
        bool    select : 1;
        uint8_t mode : 6;
        HSV     hsv;
    };
} rgb_indicator_config_t;
rgb_indicator_config_t rgb_indicator_config;

void rgb_indicator_init(void);
void eeconfig_init_rgb_indicator(void);
void eeconfig_update_rgb_indicator_default(void);
void eeconfig_update_rgb_indicator(void);
void eeconfig_debug_rgb_indicator(void);
void rgb_indicator_enable(void);
void rgb_indicator_disable(void);
void rgb_indicator_enable_toggle(void);
void rgb_indicator_factory_test_runner(void);
void rgb_indicator_toggle(bool your_led_state);
void rgb_indicator_select(void);
void rgb_indicator_select_toggle(void);
void rgb_indicator_sethsv(uint16_t hue, uint8_t sat, uint8_t val);
void rgb_indicator_mode(uint8_t mode);
void rgb_indicator_step(void);
void rgb_indicator_increase_hue(void);
void rgb_indicator_decrease_hue(void);
void rgb_indicator_increase_sat(void);
void rgb_indicator_decrease_sat(void);
void rgb_indicator_increase_val(void);
void rgb_indicator_decrease_val(void);