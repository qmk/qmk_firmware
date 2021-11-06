/* Copyright 2021 yushakobo
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

#ifdef KEYBOARD_yushakobo_navpad_10_rev0
    #include "rev0.h"
#endif

#ifdef KEYBOARD_yushakobo_navpad_10_rev1
    #include "rev1.h"
#endif

enum layer_name {
    _BASE,
    _FN1,
    _FN2,
    _FN3
};

enum custom_keycodes { 
  TAP_00
};