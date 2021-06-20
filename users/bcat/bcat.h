/* Copyright 2021 Jonathan Rascher
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

/* Layer numbers shared across keymaps. */
enum user_layer {
    /* Base layers: */
    LAYER_DEFAULT,

#if defined(BCAT_ORTHO_LAYERS)
    /* Function layers for ortho (and ergo) boards: */
    LAYER_LOWER,
    LAYER_RAISE,
    LAYER_ADJUST,
#else
    /* Function layers for traditional boards: */
    LAYER_FUNCTION_1,
    LAYER_FUNCTION_2,
#endif
};

/* Custom keycodes shared across keymaps. */
enum user_keycode {
    MC_ALTT = SAFE_RANGE,
    KEYMAP_SAFE_RANGE,
};
