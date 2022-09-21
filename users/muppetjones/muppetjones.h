/* Copyright 2020 Stephen J. Bush @muppetjones
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
#include QMK_KEYBOARD_H

#include "tapmods.h"
#include "wrappers.h"
#include "features/casemodes.h"

#ifdef COMBO_ENABLE
#    include "features/combos.h"
#endif

#ifdef ENCODER_ENABLE
#    include "features/etchamouse.h"
#endif

#ifdef RGBLIGHT_ENABLE
#    include "features/rgblayers.h"
#endif

#ifdef TAP_DANCE_ENABLE
#    include "features/dancelayers.h"
#endif

/* Define layer names */
enum userspace_layers {
    _CLMK_DH = 0,
    _QWERTY,
    _MOUSE,  // Intended for encoders. Mostly pass through.
    _LOWER,
    _RAISE,
    _NAV,
    _ADJUST,
};

// for casemodes
enum custom_keycodes {
    CLMK_DH = SAFE_RANGE,
    QWERTY,
    CAPSWRD,
};
