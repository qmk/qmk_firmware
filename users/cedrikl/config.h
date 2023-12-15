/* Copyright 2021 Cedrik Lussier @cedrikl
.* Directly inspired from the work of jonavin https://github.com/qmk/qmk_firmware/tree/master/keyboards/gmmk/pro/ansi/keymaps/jonavin
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

#ifdef RGB_MATRIX_ENABLE
    #define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR
    //#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CYCLE_ALL
    #define RGB_DISABLE_WHEN_USB_SUSPENDED
    #define RGB_MATRIX_DEFAULT_VAL 120
#endif
