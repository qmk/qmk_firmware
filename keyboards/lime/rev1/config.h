 /* Copyright 2021 HellSingCoder
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

/* joystick support */
#ifdef JOYSTICK_ENABLE
#   define JOYSTICK_AXIS_COUNT 2
#   define JOYSTICK_BUTTON_COUNT 1
#   define JOYSTICK_AXIS_RESOLUTION 8
#endif

#define SPLIT_USB_DETECT

#ifdef WPM_ENABLE
#    define SPLIT_WPM_ENABLE
#endif

