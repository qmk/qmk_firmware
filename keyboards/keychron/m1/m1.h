/* Copyright 2022 @ Keychron (https://www.keychron.com)
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

#define XXX KC_NO

typedef union {
    uint32_t raw;
    struct {
        uint8_t dpi_config;
    };
} keyboard_config_t;

extern keyboard_config_t keyboard_config;
extern uint16_t dpi_array[];

enum custom_keycodes {
#ifdef VIA_ENABLE
    DPI_CONFIG = USER00,
#else
    DPI_CONFIG = SAFE_RANGE,
#endif
    RGB_CONFIG
};

#define LAYOUT( \
    BL, BR, BM, BDPI, BRGB, BF, BB, BRR, BLL,      \
    K1, K2, K3, K4, K5                             \
) { \
    { BL, BR, BM, BDPI, BRGB, BF, BB, BRR, BLL,    \
      K1, K2, K3, K4, K5 }, \
}
