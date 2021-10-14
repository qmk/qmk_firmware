/*
This is the c configuration file for the keymap

Copyright 2021 @Yowkees

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

// 8bit is enough for layer state, because VIA (dynamic keymap) requires 4
// layer as default.
// cf. DYNAMIC_KEYMAP_LAYER_COUNT
#define LAYER_STATE_8BIT

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_LIMIT_VAL 120
#    define RGBLIGHT_HUE_STEP 10
#    define RGBLIGHT_SAT_STEP 17
#    define RGBLIGHT_VAL_STEP 17

#    define RGBLIGHT_ANIMATIONS
#endif

#undef PRODUCT_ID
#define PRODUCT_ID 0x0003

#define OLED_FONT_H "keyboards/keyball/lib/glcdfont.c"
