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

#define LAYOUT( \
  L07, L06, L05, L04, L03, L02,                    R05, R04, R03, R02, R01, R00, \
  L17, L16, L15, L14, L13, L12, L01,          R06, R15, R14, R13, R12, R11, R10, \
  L27, L26, L25, L24, L23, L22, L11,          R16, R25, R24, R23, R22, R21, R20, \
  L37, L36, L35, L34, L33, L32, L21,          R26, R35, R34, R33, R32, R31, R30, \
                           L00,                    R07,                          \
                              L10,              R17,                             \
                                 L20,        R27,                                \
                                    L30,  R37,                                   \
                           L31,                    R36                           \
  ) { \
      {L00, L01, L02, L03, L04, L05, L06, L07}, \
      {L10, L11, L12, L13, L14, L15, L16, L17}, \
      {L20, L21, L22, L23, L24, L25, L26, L27}, \
      {L30, L31, L32, L33, L34, L35, L36, L37}, \
      {R00, R01, R02, R03, R04, R05, R06, R07}, \
      {R10, R11, R12, R13, R14, R15, R16, R17}, \
      {R20, R21, R22, R23, R24, R25, R26, R27}, \
      {R30, R31, R32, R33, R34, R35, R36, R37} \
  }

#include "wire-protocol-constants.h"
#define I2C_ADDR_LEFT   (0x58 << 1)
#define I2C_ADDR_RIGHT  (I2C_ADDR_LEFT + 6)
#define I2C_ADDR(hand)  ((hand) ? I2C_ADDR_RIGHT : I2C_ADDR_LEFT)
#define LEFT            0
#define RIGHT           1

#include "leds.h"

/* vim: set ts=2 sw=2 et: */
