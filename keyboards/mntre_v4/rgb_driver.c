// Copyright 2026 Andreas Hirschauer
// SPDX-License-Identifier: GPL-2.0-or-later

// Flush only changed WS2812 frames to keep USB stable on this board.
// keyboard.json enables static effects only.

#include "gpio.h"
#include "rgb_matrix.h"
#include "ws2812.h"

// Match the board's WS2812 pad settings: slow slew, 4 mA.
#ifndef REFORM4_WS2812_PAD_MODE
#    define REFORM4_WS2812_PAD_MODE (PAL_RP_GPIO_OE | PAL_RP_PAD_DRIVE4 | PAL_MODE_ALTERNATE_PIO0)
#endif

static uint8_t shadow[RGB_MATRIX_LED_COUNT][3];
static bool    dirty = true;

static void init(void) {
    ws2812_init();
    palSetLineMode(WS2812_DI_PIN, REFORM4_WS2812_PAD_MODE);
    dirty = true;
}

static void set_color(int index, uint8_t r, uint8_t g, uint8_t b) {
    uint8_t *led = shadow[index];
    if (led[0] == r && led[1] == g && led[2] == b) {
        return;
    }
    led[0] = r;
    led[1] = g;
    led[2] = b;
    ws2812_set_color(index, r, g, b);
    dirty = true;
}

static void set_color_all(uint8_t r, uint8_t g, uint8_t b) {
    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        set_color(i, r, g, b);
    }
}

static void flush(void) {
    if (!dirty) {
        return;
    }
    ws2812_flush();
    dirty = false;
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init          = init,
    .set_color     = set_color,
    .set_color_all = set_color_all,
    .flush         = flush,
};
