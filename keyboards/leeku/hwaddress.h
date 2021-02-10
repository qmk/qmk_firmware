/* Copyright 2015 LeeKu <https://github.com/leeku11>

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

enum {
    RGB_EFFECT_BOOTHID = 0,
    RGB_EFFECT_FADE_BUF,
    RGB_EFFECT_FADE_LOOP,
    RGB_EFFECT_HEARTBEAT_BUF,
    RGB_EFFECT_HEARTBEAT_LOOP,
    RGB_EFFECT_BASIC,
    RGB_EFFECT_MAX
};

#define FADE_HIGH_HOLD             5
#define FADE_LOW_HOLD              0
#define FADE_IN_ACCEL              0  // normal ascending

#define HEARTBEAT_HIGH_HOLD        1
#define HEARTBEAT_LOW_HOLD         5
#define HEARTBEAT_IN_ACCEL         1  // 1: weighted ascending. 2: quadratic ascending

typedef struct {
    uint8_t index;
    uint8_t high_hold;
    uint8_t low_hold;
    uint8_t accel_mode;
} rgb_effect_param_type;

typedef struct kbd_conf {
    uint8_t led_preset_index;               // LED effect  preset index
    uint8_t led_preset[3][5];               // Block configuration for LED effect  preset
    uint8_t rgb_effect_index;               // RGB effect index
    uint16_t rgb_limit;
    uint16_t rgb_speed;
    uint8_t rgb_chain;                      // RGB5050 numbers (H/W dependent)
    rgb_effect_param_type rgb_effect_param[RGB_EFFECT_MAX]; // RGB effect parameter
}kbd_configuration_t;
