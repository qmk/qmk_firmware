/*
Copyright 2021 @kuriatsu

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
#define MASTER_RIGHT

#    define RGBLED_NUM 12
#    define RGBLIGHT_SPLIT
#    define RGBLED_SPLIT {6, 6}
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 1
#    define RGBLIGHT_VAL_STEP 1
#    define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL

#define SPLIT_WPM_ENABLE
#define SPLIT_LAYER_STATE_ENABLE
