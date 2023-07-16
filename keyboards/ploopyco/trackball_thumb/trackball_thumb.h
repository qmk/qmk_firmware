/* Copyright 2021 Colin Lam (Ploopy Corporation)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
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
#include "analog.h"
#include "opt_encoder.h"

// Sensor defs
#define OPT_ENC1 F4
#define OPT_ENC2 F0
#define OPT_ENC1_MUX 4
#define OPT_ENC2_MUX 0

typedef union {
    uint32_t raw;
    struct {
        uint8_t dpi_config;
    };
} keyboard_config_t;
_Static_assert(sizeof(keyboard_config_t) == sizeof(uint32_t), "keyboard_config_t size mismatch compared to EEPROM area");

extern keyboard_config_t keyboard_config;
extern uint16_t          dpi_array[];

enum ploopy_keycodes {
    DPI_CONFIG = QK_KB_0,
    DRAG_SCROLL,
};
