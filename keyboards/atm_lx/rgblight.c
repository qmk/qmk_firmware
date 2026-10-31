// Copyright 2024 WestBerry Tech (https://www.westberrytech.com)
// Copyright 2024 JoyLee (@itarze)
// SPDX-License-Identifier: GPL-2.0-or-later

#if defined(RGBLIGHT_CUSTOM) && defined(RGB_MATRIX_ENABLE)
#    include "rgb_matrix.h"
#    include "rgblight_drivers.h"
#include "debug.h"

#if defined RGB_LIGHT_LED_BEGIN_IND
    const int basic_index = RGB_LIGHT_LED_BEGIN_IND;
#else
    const int basic_index = (RGB_MATRIX_LED_COUNT - RGBLIGHT_LED_COUNT);
#endif

static rgb_t rgblight_buffer[RGBLIGHT_LED_COUNT] = {0};

static void rgblight_init(void) {
    // do nothing
}

static void rgblight_flush(void) {
    // do nothing
}

static void rgblight_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {

    if ((index < 0) || (index >= RGBLIGHT_LED_COUNT)) {
        return;
    }

    rgblight_buffer[index] = (rgb_t){red, green, blue};
}

static void rgblight_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {

    for (int i = 0; i < RGBLIGHT_LED_COUNT; i++) {
        rgblight_set_color(i, red, green, blue);
    }
}

// 此处被强制定义，不允许修改
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    if (basic_index <= 0) {
        return true;
    }

    for (int i = 0; i < RGBLIGHT_LED_COUNT; i++) {
        // if (i >= led_min && i < led_max)
        {
            rgb_matrix_set_color(basic_index + i, rgblight_buffer[i].r, rgblight_buffer[i].g, rgblight_buffer[i].b);
        }
    }
    return true;
}

const rgblight_driver_t rgblight_driver = {
    .init          = rgblight_init,
    .set_color     = rgblight_set_color,
    .set_color_all = rgblight_set_color_all,
    .flush         = rgblight_flush,
};
#endif
