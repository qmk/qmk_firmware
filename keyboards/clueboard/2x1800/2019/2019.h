/* Copyright 2017 Zach White <skullydazed@gmail.com>
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

enum TWOx1800_keycodes {
    ENC_BTN1 = SAFE_RANGE,
    ENC_BTN2,
    ENC_BTN3,
    ENC_BTN4,
    NEW_SAFE_RANGE
};

#undef SAFE_RANGE
#define SAFE_RANGE NEW_SAFE_RANGE

// Encoder update function that returns true/false
__attribute__ ((weak))
bool encoder_update_keymap(int8_t index, bool clockwise);

// Encoder button combo check
void check_encoder_buttons(void);
