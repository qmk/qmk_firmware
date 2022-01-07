/* Copyright 2020 Sergi Meseguer <zigotica@gmail.com>
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

#include "rows.h"

#ifdef SPLIT_KEYBOARD
enum userspace_layers {
    BASE = 0,
    _NUM,
    _NAV,
    _SYM,
    _FN,
};
#else
enum userspace_layers {
    _BASE = 0,
    _FIGMA,
    _BROWSER,
    _VIM,
};
#endif


#ifdef TAP_DANCE_ENABLE
#    include "tapdances.h"
#endif

#ifdef COMBO_ENABLE
#    include "combos.h"
#endif

#ifdef OLED_ENABLE
  #include "oled.h"
#endif

#ifdef ENCODER_ENABLE
  #include "encoder.h"
#endif
