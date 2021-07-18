/*
Copyright 2021 id-b3
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

#include "quantum.h"
#include "pointing_device.h"

#ifndef TRACKBALL_ADDRESS
#    define TRACKBALL_ADDRESS 0x0A
#endif
#define TRACKBALL_WRITE ((TRACKBALL_ADDRESS << 1) | I2C_WRITE)
#define TRACKBALL_READ  ((TRACKBALL_ADDRESS << 1) | I2C_READ)

void trackball_set_rgbw(uint8_t red, uint8_t green, uint8_t blue, uint8_t white);
void trackball_check_click(bool pressed, report_mouse_t *mouse);

int16_t trackball_get_precision(void);
void    trackball_set_precision(int16_t precision);
bool    trackball_is_scrolling(void);
void    trackball_set_scrolling(bool scroll);
bool    trackball_is_carret(void);
void    trackball_set_carret(bool scroll);

void trackball_set_left(bool pressed);
void trackball_set_right(bool pressed);
void trackball_set_middle(bool pressed);