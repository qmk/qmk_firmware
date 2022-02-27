/* Copyright 2021 thewerther
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

/**
 * NB!  THIS VARIANT DISABLES THE UNDERGLOW LEDs
 *      FOR BOARDS WITH A SOLID (NON-ACRILIC) BOTTOM
 */

#pragma once

#if defined(RGB_MATRIX_ENABLE)
    #define VIA_QMK_RGBLIGHT_ENABLE
    #define ID67_DISABLE_UNDERGLOW
#endif
