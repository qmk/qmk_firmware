/*
 * Copyright (c) 2018 Charlie Waters
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

#ifndef VORTEX_H
#define VORTEX_H

#include "quantum.h"

#define OVERRIDE

enum extra_keycodes {
    EX_ECHO = SAFE_RANGE,
    EX_DUMP,
    EX_RESET,
};

void spi_flash_init(void);
void spi_dump(void);
void spi_read(uint32_t addr, uint16_t n, uint8_t *data);
void spi_write(uint32_t addr, uint16_t n, const uint8_t *data);

#endif // VORTEX_H
