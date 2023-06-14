/*
Copyright 2020 Copyright 2020 Draevin Luke <contact@drae.vin> @draevin

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

#include QMK_KEYBOARD_H
#include "wrappers.h"

enum my_layers {
    _CM,
    _QW,
    _FN,
};

enum my_keycodes {
    CM_QW = SAFE_RANGE,  // Switch between Colemak and QWERTY
    KC_MAKE,
    PRNPAIR,
    BRCPAIR,
    NEW_SAFE_RANGE
};

enum my_taps {
    TD_CAPS  // shift/caps TD
};
