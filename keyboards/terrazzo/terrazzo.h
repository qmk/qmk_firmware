/* Copyright 2020 ademey "MsMustard"
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

enum terrazzo_matrix_effects {
    TERRAZZO_NONE = 0,
// --------------------------------------
// -----Begin led effect enum macros-----
#define TERRAZZO_EFFECT(name, ...) TERRAZZO_EFFECT_##name,
#include "terrazzo_effects/terrazzo_effects.inc"
#undef TERRAZZO_EFFECT
    // --------------------------------------
    // -----End led effect enum macros-------
    // All new effects go above this line
    TERRAZZO_EFFECT_MAX
};

enum terrazzo_keycodes {
    TZ_NXT = QK_KB_0,
    TZ_PRV,
    TZ_OFF
};

void terrazzo_render(void);
void terrazzo_set_pixel(uint8_t x, uint8_t y, uint8_t value);
void terrazzo_draw_at(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t image[]);
void terrazzo_scroll_pixel(bool clockwise);
void terrazzo_step_mode(void);
void terrazzo_step_mode_reverse(void);
void terrazzo_mode_off(void);
