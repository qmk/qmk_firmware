/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>
Copyright 2015 ZSA Technology Labs Inc (@zsa)
Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "quantum.h"
#include <stdint.h>
#include <stdbool.h>
#include "i2c_master.h"

extern i2c_status_t mcp23018_status;

#ifndef ERGODOX_EZ_I2C_TIMEOUT
#    define ERGODOX_EZ_I2C_TIMEOUT 80
#endif
#ifndef MCP23018_EXPANDER_I2C_ADDR
#    define MCP23018_EXPANDER_I2C_ADDR (0x20 << 1)
#endif

uint8_t init_mcp23018(void);
void ergodox_blink_all_leds(void);
bool is_transport_connected(void);

void ergodox_board_led_on(void);
void ergodox_right_led_1_on(void);
void ergodox_right_led_2_on(void);
void ergodox_right_led_3_on(void);
void ergodox_right_led_on(uint8_t led);
void ergodox_board_led_off(void);
void ergodox_right_led_1_off(void);
void ergodox_right_led_2_off(void);
void ergodox_right_led_3_off(void);
void ergodox_right_led_off(uint8_t led);
void ergodox_led_all_on(void);
void ergodox_led_all_off(void);
void ergodox_right_led_1_set(uint8_t n);
void ergodox_right_led_2_set(uint8_t n);
void ergodox_right_led_3_set(uint8_t n);
void ergodox_right_led_set(uint8_t led, uint8_t n);
void ergodox_led_all_set(uint8_t n);

#ifndef LED_BRIGHTNESS_LO
#    define LED_BRIGHTNESS_LO 15
#endif
#ifndef LED_BRIGHTNESS_HI
#    define LED_BRIGHTNESS_HI 255
#endif

enum ergodox_ez_keycodes {
    LED_LEVEL = QK_KB,
    TOGGLE_LAYER_COLOR,
    EZ_SAFE_RANGE
};

typedef union {
    uint32_t raw;
    struct {
        uint8_t led_level : 3;
        bool    disable_layer_led : 1;
        bool    placeholder : 1;
    };
} keyboard_config_t;

extern keyboard_config_t keyboard_config;

#define STATUS_LED_1(status) (bool)status ? ergodox_right_led_1_on() : ergodox_right_led_1_off()
#define STATUS_LED_2(status) (bool)status ? ergodox_right_led_2_on() : ergodox_right_led_2_off()
#define STATUS_LED_3(status) (bool)status ? ergodox_right_led_3_on() : ergodox_right_led_3_off()
