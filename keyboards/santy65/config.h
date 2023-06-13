/* Copyright 2023 Your Name (@santy81855)
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
/* optical sensor settings */
// define which side the pointing device is on
#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_LEFT
// SS Pin on the Trackball sensor 
#define PMW33XX_CS_PIN B0
// the sensitivity between 100 and 12000
#define PMW33XX_CPI 1200
#define POINTING_DEVICE_INVERT_Y
#define SCROLL_DIVIDER 12

// Decrease firmware size
#define NO_ACTION_ONESHOT