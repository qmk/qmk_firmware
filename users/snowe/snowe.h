/*
Copyright 2021 Tyler Thrailkill <@snowe/@snowe2010>

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

#ifndef QMK_FIRMWARE_SNOWE_H
#    define QMK_FIRMWARE_SNOWE_H ;
#endif  // QMK_FIRMWARE_SNOWE_H

#include "wrappers.h"
#include "keycode_aliases.h"

#undef PERMISSIVE_HOLD

//#if defined(RGBLIGHT_ENABLE)
//#    include "rgb_stuff.h"
//#endif
//#if defined(RGB_MATRIX_ENABLE)
//#    include "rgb_matrix_stuff.h"
//#endif
#ifdef OLED_ENABLE
#    include "oled_setup.h"
#endif


enum layers { _MAIN, _GAMING, _LOWER, _UPPER, _ADJUST };
