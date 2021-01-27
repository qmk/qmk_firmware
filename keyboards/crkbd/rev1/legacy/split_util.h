/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

#ifndef SPLIT_KEYBOARD_UTIL_H
#define SPLIT_KEYBOARD_UTIL_H

#include <stdbool.h>
#include "eeconfig.h"

#define SLAVE_I2C_ADDRESS           0x32

extern volatile bool isLeftHand;

// slave version of matix scan, defined in matrix.c
uint8_t matrix_slave_scan(void);

void split_keyboard_setup(void);
bool has_usb(void);

void matrix_master_OLED_init (void);

#endif
