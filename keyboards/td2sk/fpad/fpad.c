// Copyright 2023 td2sk (@td2sk)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "i2c_master.h"

#include QMK_KEYBOARD_H

#include <stdbool.h>

#include "i2c_master.h"
#include "gpio.h"

#include "drivers/is31fl3208.h"
#include "drivers/xl9555.h"
#include "drivers/ws2812.h"

static uint8_t prev_pressed             = 0;
static uint8_t additional_keys_map[][2] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {2, 4}, {4, 4}};

static void additional_button_scan(void) {
    uint16_t pressed = XL9555_read() >> 10;
    if (readPin(B1)) {
        pressed |= 0b00100000;
    }
    uint8_t changed = prev_pressed ^ pressed;
    for (uint8_t i = 0; i < 6; ++i) {
        uint8_t mask = 1 << i;
        if (changed & mask) {
            action_exec(MAKE_KEYEVENT(additional_keys_map[i][0], additional_keys_map[i][1], (pressed >> i) & 1));
        }
    }
    prev_pressed = pressed;
}

void keyboard_post_init_user(void) {
    setPinInputHigh(B1);
    i2c_init();
    XL9555_set_polarity(0xFF, 0b10000011);
}

void matrix_scan_user(void) {
    additional_button_scan();
}

joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {[0] = JOYSTICK_AXIS_IN(F7, 102, 512, 922), [1] = JOYSTICK_AXIS_IN(F6, 102, 512, 922)};

// LED color buffer
LED_TYPE rgb_matrix_ws2812_array[RGB_MATRIX_LED_COUNT];

static void init(void) {
    i2c_init();
    IS31FL3208_init();
}

static void flush(void) {
    ws2812_setleds(rgb_matrix_ws2812_array, CUSTOM_SERIAL_LED_TOTAL);
    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT - CUSTOM_SERIAL_LED_TOTAL; ++i) {
        RGB *led = rgb_matrix_ws2812_array + CUSTOM_SERIAL_LED_TOTAL + i;
        IS31FL3208_set_color(i, led->r, led->g, led->b);
    }
    IS31FL3208_update();
}

static void set_color(int i, uint8_t r, uint8_t g, uint8_t b) {
#if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_SPLIT)
    const uint8_t k_rgb_matrix_split[2] = RGB_MATRIX_SPLIT;
    if (!is_keyboard_left()) {
        if (i >= k_rgb_matrix_split[0]) {
            i -= k_rgb_matrix_split[0];
        } else {
            return;
        }
    } else if (i >= k_rgb_matrix_split[0]) {
        return;
    }
#endif

    rgb_matrix_ws2812_array[i].r = r;
    rgb_matrix_ws2812_array[i].g = g;
    rgb_matrix_ws2812_array[i].b = b;
#ifdef RGBW
    convert_rgb_to_rgbw(&rgb_matrix_ws2812_array[i]);
#endif
}

static void set_color_all(uint8_t r, uint8_t g, uint8_t b) {
    for (int i = 0; i < ARRAY_SIZE(rgb_matrix_ws2812_array); i++) {
        set_color(i, r, g, b);
    }
}

const rgb_matrix_driver_t rgb_matrix_driver = {.init = init, .flush = flush, .set_color = set_color, .set_color_all = set_color_all};
