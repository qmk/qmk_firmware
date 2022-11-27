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

enum layer_names {
    _DF_MAC,
    _WIN,
    _NAV_FN1,   //with keycodes piggybacking of off layer data to use proper modifiers
    _KEYB
};
/*
    Most CK_ CustomKeycodes simply exist to keep the keymap file clean and
    relay logic for windows/macos to the mreel.c userspace file.
    This is done so both the keymaps file stay clean, and more importantly,
    this means that for example CK_BWRD (backspace-word) has only one
    location in the keymap and can be easily moved.
*/
 enum my_keycodes {
     CK_BWRD = SAFE_RANGE,
     CK_HOME,
     CK_END,
     CK_VOLU,
     CK_VOLD,
     CK_DLFT,
     CK_DRHT,
     CK_LWRD,
     CK_RWRD,
     UC_UCIS,
     // unicodemap characters
     UC_TRMI,   //leave first
     UC_TRMU,
     UC_TRMO,
     UC_TRME,
     UC_AGRE,
     UC_AAGE,
     UC_ACRE,
     UC_SP23,
     UC_SMLE,
     UC_COL     //leave last
 };
