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

#define ML_LED_1(status) writePin(B5, (bool)status)
#define ML_LED_2(status) writePin(B4, (bool)status)
#define ML_LED_3(status) writePin(B3, (bool)status)

#define ML_LED_4(status) mcp23018_leds[0] = (bool)status
#define ML_LED_5(status) mcp23018_leds[1] = (bool)status
#define ML_LED_6(status) mcp23018_leds[2] = (bool)status


// clang-format off
#define LED_LAYOUT_moonlander( \
    l00, l01, l02, l03, l04, l05, l06,   l60, l61, l62, l63, l64, l65, l66, \
    l10, l11, l12, l13, l14, l15, l16,   l70, l71, l72, l73, l74, l75, l76, \
    l20, l21, l22, l23, l24, l25, l26,   l80, l81, l82, l83, l84, l85, l86, \
    l30, l31, l32, l33, l34, l35,             l91, l92, l93, l94, l95, l96, \
    l40, l41, l42, l43, l44,      l53,   lb3,      la2, la3, la4, la5, la6, \
                        l50, l51, l52,   lb4, lb5, lb6 \
) \
{ \
    l00, l10, l20, l30, l40, \
    l01, l11, l21, l31, l41, \
    l02, l12, l22, l32, l42, \
    l03, l13, l23, l33, l43, \
    l04, l14, l24, l34, l44, \
    l05, l15, l25, l35, \
    l06, l16, l26, \
    l50, l51, l52, l53, \
\
    l66, l76, l86, l96, la6, \
    l65, l75, l85, l95, la5, \
    l64, l74, l84, l94, la4, \
    l63, l73, l83, l93, la3, \
    l62, l72, l82, l92, la2, \
    l61, l71, l81, l91, \
    l60, l70, l80, \
    lb6, lb5, lb4, lb3 \
}
// clang-format on

enum planck_ez_keycodes {
    TOGGLE_LAYER_COLOR = QK_KB_0,
    LED_LEVEL,
};

#ifndef WEBUSB_ENABLE
#    define WEBUSB_PAIR KC_NO
#endif

typedef union {
  uint32_t raw;
  struct {
    bool         disable_layer_led   :1;
    bool         rgb_matrix_enable   :1;
    bool         led_level           :1;
    uint8_t      led_level_res       :2; // DO NOT REMOVE
  };
} keyboard_config_t;

extern keyboard_config_t keyboard_config;

bool is_transport_connected(void);
