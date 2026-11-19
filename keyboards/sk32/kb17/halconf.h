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

/* No PWM-based LED driver is used on the SK32F077: RGB runs over the native
 * SLED peripheral (WS2812_DRIVER=sled), which the build system enables with
 * -DHAL_USE_SLED=TRUE.  The SK32 platform common halconf.h provides the HAL
 * drivers this keyboard needs (USB device driver, etc.). */
#include_next <halconf.h>
