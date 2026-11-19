/* Copyright 2020 QMK
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

/* The SSD1306 OLED uses the I2C transport (OLED_TRANSPORT=i2c), which enables
 * HAL_USE_I2C and the native SK32 I2C driver through the build system.  RGB
 * runs over the native SLED peripheral (WS2812_DRIVER=sled), enabled with
 * -DHAL_USE_SLED=TRUE.  The SK32 platform common halconf.h provides the other
 * HAL drivers this keyboard needs (USB device driver, etc.). */
#include_next <halconf.h>
