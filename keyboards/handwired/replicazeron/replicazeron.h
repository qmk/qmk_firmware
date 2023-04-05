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

// FIXME: The "common/" prefixes can probably be removed using VPATH or whatever on the mk file

#include "common/state.h"

#ifdef LEDS_ENABLE
#    include "common/leds.h"
#endif

#ifdef OLED_ENABLE
#    include "common/oled.h"
#endif

#ifdef THUMBSTICK_ENABLE
#    include "common/thumbstick.h"
#endif

enum kb_layers {
    _BASE,
    _SHOOTER,
    _MISC,
    _SETTINGS,
};

enum kb_keycodes {
    JOYMODE = QK_KB,
    AUTORUN,
    M_UP,
    M_DWN,
    M_L,
    M_R,
    M_SEL
};
