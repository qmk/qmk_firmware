/* Copyright 2023 Ciaanh (@ciaanh)
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

#ifdef KEYBOARD_ciaanh_kanagawa_ansi
    #include "ansi.h"
#endif 

#ifdef KEYBOARD_ciaanh_kanagawa_iso
    #include "iso.h"
#endif 

#define ___ KC_NO
#define NA NO_LED

enum layers 
{ 
    _BASE,
    _CODE, 
    _FUNC,
    _TOP
};

enum custom_keycodes 
{ 
    CUSTOMKEY = SAFE_RANGE, 
    NEW_SAFE_RANGE, 
};

#define TO_BASE     TO(_BASE)
#define TO_FUNC     TG(_FUNC)

#define L_CODE      MO(_CODE)

#define _SCRNSHOT LSFT(LGUI(KC_S))