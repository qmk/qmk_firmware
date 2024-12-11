/* Copyright 2023 9R
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

#include "state.h"

#ifdef LEDS_ENABLE
#    include "leds.h"
#endif

#ifdef OLED_ENABLE
#    include "oled.h"
#endif

#ifdef THUMBSTICK_ENABLE
#    include "thumbstick.h"
#endif

enum kb_layers {
    _BASE,
    _SHOOTER,
    _MISC,
    _SETTINGS,
};

enum kb_keycodes {
    JOYMODE = QK_USER,
    AUTORUN,
    M_UP,
    M_DWN,
    M_L,
    M_R,
    M_SEL
};
