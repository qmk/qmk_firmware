/*
Copyright 2021 Merlin Jehli <merlin@jeh.li> @fml128

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

#define COLOR HSV_GREEN // define solid color
#define BACKLIGHT_TIMEOUT 5 // (minutes)

#define USB_POLLING_INTERVAL_MS 1
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_COLOR

#undef USB2422_MANUFACTURER
#undef USB2422_PRODUCT
#define USB2422_MANUFACTURER "FML128.ch"
#define USB2422_PRODUCT "FMK128 Hub"
