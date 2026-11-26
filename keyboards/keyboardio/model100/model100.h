/* Copyright 2018 James Laird-Wah
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

#include "quantum.h"

#include "wire-protocol-constants.h"
#define I2C_ADDR_LEFT   (0x58 << 1)
#define I2C_ADDR_RIGHT  (I2C_ADDR_LEFT + 6)
#define I2C_ADDR(hand)  ((hand) ? I2C_ADDR_RIGHT : I2C_ADDR_LEFT)
#define LEFT            0
#define RIGHT           1

/* Polled (non-DMA) I2C for the scanners, implemented in matrix.c. Both the key
 * matrix and the LED driver (leds.c) share this: QMK's ChibiOS DMA i2c_transmit
 * does not work on the GD32F303, and mixing it with our polled reads corrupts
 * the bus. addr8 is the pre-shifted 8-bit address (I2C_ADDR macro). */
bool i2c_poll_write(uint8_t addr8, const uint8_t *src, int n);

#include "leds.h"

/* vim: set ts=2 sw=2 et: */
