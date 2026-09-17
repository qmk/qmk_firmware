// Copyright 2023 ZSA Technology Labs, Inc <@zsa>
// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

extern bool mcp23018_leds[];

#define MCP23018_DEFAULT_ADDRESS 0b0100000

#define STATUS_LED_1(status) gpio_write_pin(B5, (bool)(status))
#define STATUS_LED_2(status) gpio_write_pin(B4, (bool)(status))
#define STATUS_LED_3(status) mcp23018_leds[0] = (bool)(status)
#define STATUS_LED_4(status) mcp23018_leds[1] = (bool)(status)

enum voyager_keycodes {
    TOGGLE_LAYER_COLOR = QK_KB,
    LED_LEVEL,
};

typedef union {
    uint32_t raw;
    struct {
        bool    disable_layer_led : 1;
        bool    placeholder : 1;
        bool    led_level : 1;
        uint8_t led_level_res : 2; // DO NOT REMOVE
    };
} keyboard_config_t;

extern keyboard_config_t keyboard_config;

bool is_transport_connected(void);
