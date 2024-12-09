// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rgblight_drivers.h"

#if defined(RGBLIGHT_WS2812)
#    include "ws2812.h"

const rgblight_driver_t rgblight_driver = {
    .init          = ws2812_init,
    .set_color     = ws2812_set_color,
    .set_color_all = ws2812_set_color_all,
    .flush         = ws2812_flush,
};

#elif defined(RGBLIGHT_APA102)
#    include "apa102.h"

const rgblight_driver_t rgblight_driver = {
    .init          = apa102_init,
    .set_color     = apa102_set_color,
    .set_color_all = apa102_set_color_all,
    .flush         = apa102_flush,
};

#endif

#ifdef RGBLIGHT_DOUBLE_BUFFER

static rgb_t led_buffer[RGBLIGHT_LED_COUNT];

void rgblight_driver_init(void) {
    rgblight_driver.init();
}

void rgblight_driver_flush(void) {
    for (uint16_t i = 0; i < RGBLIGHT_LED_COUNT; i++) {
        rgblight_driver.set_color(i, led_buffer[i].r, led_buffer[i].g, led_buffer[i].b);
    }
    rgblight_driver.flush();
}

void rgblight_driver_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    led_buffer[index] = (rgb_t){.r = red, .g = green, .b = blue};
}

void rgblight_driver_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (uint16_t i = 0; i < RGBLIGHT_LED_COUNT; i++) {
        rgb_matrix_driver_set_color(i, red, green, blue);
    }
}

const rgblight_driver_t rgblight_driver_wrapper = {
    .init          = rgblight_driver_init,
    .flush         = rgblight_driver_flush,
    .set_color     = rgblight_driver_set_color,
    .set_color_all = rgblight_driver_set_color_all,
};

#endif
