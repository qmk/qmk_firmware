/*
Copyright 2021 CapsUnlocked

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

/* enable RGB matrix */
#define CU80_RGB

/* update the product for RGB Matrix variant in VIA/VIAL and Remap-keys.app */
#undef PRODUCT
#define PRODUCT         CU80 v2 ISO RGB

/* moved to RGB specific */
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 50

/* RGB firmware override */
#undef RGBLIGHT_ANIMATIONS
#undef RGBLIGHT_HUE_STEP
#undef RGBLIGHT_SAT_STEP
#undef RGBLIGHT_VAL_STEP
#undef RGBLIGHT_LIMIT_VAL
