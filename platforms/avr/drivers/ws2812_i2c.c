// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "ws2812.h"
#include "i2c_master.h"

#ifdef WS2812_RGBW
#    error "RGBW not supported"
#endif

#ifndef WS2812_I2C_ADDRESS
#    define WS2812_I2C_ADDRESS 0xB0
#endif

#ifndef WS2812_I2C_TIMEOUT
#    define WS2812_I2C_TIMEOUT 100
#endif

ws2812_led_t ws2812_leds[WS2812_LED_COUNT];

void ws2812_init(void) {
    i2c_init();
}

void ws2812_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    ws2812_leds[index].r = red;
    ws2812_leds[index].g = green;
    ws2812_leds[index].b = blue;
}

void ws2812_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < WS2812_LED_COUNT; i++) {
        ws2812_set_color(i, red, green, blue);
    }
}

void ws2812_flush(void) {
    i2c_transmit(WS2812_I2C_ADDRESS, (uint8_t *)ws2812_leds, WS2812_LED_COUNT * sizeof(ws2812_led_t), WS2812_I2C_TIMEOUT);
}
