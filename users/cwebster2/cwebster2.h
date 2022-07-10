/* Copyright 2020 Casey Webster <casey@e1337.dev>
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

#include "my_miryoku.h"
#include "keycodes.h"
#include "eeprom.h"

#define LAYOUT_kyria_wrapper(...)  LAYOUT(__VA_ARGS__)
#define LAYOUT_zen_wrapper(...)    LAYOUT(__VA_ARGS__)

enum userspace_layers {
    _COLEMAK = 0,
    _QWERTY,
    _GAME,
    _FN,
    _SYMBOLS,
    _NUM,
    _NAV,
    _MOUSE,
    _MEDIA,
    __LAST
};

void keyboard_post_init_rgb(void);
void matrix_scan_keymap(void);
void eeconfig_init_keymap(void);
bool hasAllBitsInMask(uint8_t value, uint8_t mask);


typedef union {
    uint32_t raw;
    struct {
        bool rgb_layer_change :1;
    };
} userspace_config_t;

extern userspace_config_t userspace_config;
