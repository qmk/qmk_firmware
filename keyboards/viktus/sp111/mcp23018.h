/* Copyright 2020 zvecr<git@zvecr.com>
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
#include <stdbool.h>

#define mcp23018_PORTA 0
#define mcp23018_PORTB 1

#define ALL_OUTPUT 0
#define ALL_INPUT 0xFF
#define ALL_LOW 0
#define ALL_HIGH 0xFF

void mcp23018_init(uint8_t addr);
bool mcp23018_set_config(uint8_t slave_addr, uint8_t port, uint8_t conf);
bool mcp23018_set_output(uint8_t slave_addr, uint8_t port, uint8_t conf);
bool mcp23018_set_output_all(uint8_t slave_addr, uint8_t confA, uint8_t confB);
bool mcp23018_readPins(uint8_t slave_addraddr, uint8_t port, uint8_t* ret);
bool mcp23018_readPins_all(uint8_t slave_addr, uint16_t* ret);
