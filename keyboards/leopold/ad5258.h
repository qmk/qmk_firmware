/*
Copyright 2017 Balz Guenat

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

#include <stdint.h>

#define AD5258_RDAC_MAX 63
#define AD5258_RDAC_MIN 0

void ad5258_init(void);

int8_t ad5258_read_rdac(void);

int8_t ad5258_read_eeprom(void);

int8_t ad5258_write_rdac(uint8_t rdac);

void ad5258_restore_from_eeprom(void);
