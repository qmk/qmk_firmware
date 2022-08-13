/* Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>
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

#include "keymap.h"

/* -----------------------
 * RGB Utils. Functions
 * -----------------------
 */

enum INDICATOR_STATES{
    DEFAULT_INDI = 0,  // Show indicator
    MASK_ANIM,         // Mask Indicators
    SHOW_ANIM          // Show Animations
};

typedef union Color
{
    unsigned int hex;
    struct { unsigned char b, g, r; };
} HexColor;

extern bool rgb_matrix_idling;
extern uint8_t indicator_state;