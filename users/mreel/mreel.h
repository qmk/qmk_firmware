/*
Copyright 2022 Tibo Loete, aka Mister Eel <mistermister1111@hotmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once 

#include QMK_KEYBOARD_H
#include "wrappers.h"

enum my_tapdances {
    TD_SHAP,
};

enum layer_names {
    _DF_MAC,
    _WIN,
    _NAV_FN1,   //with keycodes piggybacking of off layer data to use proper modifiers
    _KEYB
};

 enum my_keycodes {
     CK_BWRD = SAFE_RANGE,
     CK_HOME,
     CK_END,
     CK_WCMD,
 };