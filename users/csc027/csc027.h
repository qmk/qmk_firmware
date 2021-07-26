/*
Copyright 2020 Constantine Chen @csc027

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "quantum.h"
#include "defines.h"

enum custom_keycodes {
    // Layer Keycodes
    LOWER = SAFE_RANGE,
    RAISE,


    MC_first,

    // Macro Keycodes
    CUSTOM_MACROS(CUSTOM_ENUM, DROP, COMMA_DELIM),

    MC_last
};

enum custom_layers {
    _QW = 0, // Qwerty
    _RS,     // Raise
    _LW,     // Lower
    _MS,     // Mouse
    _WT,     // Windows Terminal
    _CN,     // Convenience
    _GG,     // General Gaming
    _CS      // Counter-Strike: Global Offensive
};
