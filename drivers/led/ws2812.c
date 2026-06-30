// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "ws2812.h"
#include "gpio.h"

#if defined(WS2812_RGBW)
void ws2812_rgb_to_rgbw(ws2812_led_t *led) {
    // Determine lowest value in all three colors, put that into
    // the white channel and then shift all colors by that amount
    led->w = MIN(led->r, MIN(led->g, led->b));
    led->r -= led->w;
    led->g -= led->w;
    led->b -= led->w;
}
#endif

#if defined(WS2812_VCC_ENABLE_PINS)

static const pin_t ws2812_vcc_enable_pins[] = WS2812_VCC_ENABLE_PINS;

void ws2812_set_power(bool on) {
    static bool initialized = false;
    static bool last_on     = false;

    if (initialized && on == last_on) {
        return;
    }

    bool pin_value = on;
#if defined(WS2812_VCC_ACTIVE_LOW)
    pin_value = !pin_value;
#endif

    for (uint8_t i = 0; i < ARRAY_SIZE(ws2812_vcc_enable_pins); i++) {
        gpio_write_pin(ws2812_vcc_enable_pins[i], pin_value);
    }

    if (!initialized) {
        /* Latch-then-output order avoids active-low glitch on first call. */
        for (uint8_t i = 0; i < ARRAY_SIZE(ws2812_vcc_enable_pins); i++) {
            gpio_set_pin_output(ws2812_vcc_enable_pins[i]);
        }
        initialized = true;
    }

    last_on = on;
}

#endif
