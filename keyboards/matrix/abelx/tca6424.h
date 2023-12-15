/**
 * @file tca6424.h
 * @author astro
 * @brief  driver for the tca6424
 *
 * Copyright 2020 astro <yuleiz@gmail.com>
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

#include <stdint.h>

#ifndef TCA6424_ADDR
    #define TCA6424_ADDR 0x44
#endif

typedef enum {
    TCA6424_PORT0 = 0,
    TCA6424_PORT1,
    TCA6424_PORT2,
} TCA6424_PORT;

void tca6424_init(void);

void    tca6424_write_config(TCA6424_PORT port, uint8_t data);
void    tca6424_write_polarity(TCA6424_PORT port, uint8_t data);

void    tca6424_write_port(TCA6424_PORT port, uint8_t data);
uint8_t tca6424_read_port(TCA6424_PORT port);
