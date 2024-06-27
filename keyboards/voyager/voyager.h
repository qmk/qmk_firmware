/* Copyright 2020 ZSA Technology Labs, Inc <@zsa>
 * Copyright 2020 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"

extern bool mcp23018_leds[];

#define MCP23018_DEFAULT_ADDRESS 0b0100000

#define STATUS_LED_1(status) writePin(B5, status)
#define STATUS_LED_2(status) writePin(B4, status)
#define STATUS_LED_3(status) mcp23018_leds[0] = status
#define STATUS_LED_4(status) mcp23018_leds[1] = status

// clang-format off
#define LAYOUT( \
  k00, k01, k02, k03, k04, k05,                 k26, k27, k28, k29, k30, k31, \
  k06, k07, k08, k09, k10, k11,                 k32, k33, k34, k35, k36, k37, \
  k12, k13, k14, k15, k16, k17,                 k38, k39, k40, k41, k42, k43, \
  k18, k19, k20, k21, k22, k23,                 k44, k45, k46, k47, k48, k49, \
                              k24, k25, k50, k51 \
)\
{ \
    { KC_NO, k00, k01, k02, k03, k04, k05 }, \
    { KC_NO, k06, k07, k08, k09, k10, k11 }, \
    { KC_NO, k12, k13, k14, k15, k16, k17 }, \
    { KC_NO, k18, k19, k20, k21, k22, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, k23, KC_NO, KC_NO }, \
    { k24, k25, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
\
    { k26, k27, k28, k29, k30, k31, KC_NO }, \
    { k32, k33, k34, k35, k36, k37, KC_NO }, \
    { k38, k39, k40, k41, k42, k43, KC_NO }, \
    { KC_NO, k45, k46, k47, k48, k49, KC_NO }, \
    { KC_NO, KC_NO, k44, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k50, k51 }, \
}
// clang-format on
enum voyager_keycodes {
    TOGGLE_LAYER_COLOR = SAFE_RANGE,
    LED_LEVEL,
    ML_SAFE_RANGE,
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
