/* Copyright 2019 Neil Kettle
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

#ifdef RIGHT_HALF
# include <stdint.h>
# include "i2c_master.h"

// I2C aliases and register addresses (see "mcp23018.md")
# define I2C_ADDR        0b0100000
# define I2C_ADDR_WRITE  ( (I2C_ADDR<<1) | I2C_WRITE )
# define I2C_ADDR_READ   ( (I2C_ADDR<<1) | I2C_READ  )
# define IODIRA          0x00            // i/o direction register
# define IODIRB          0x01
# define GPPUA           0x0C            // GPIO pull-up resistor register
# define GPPUB           0x0D
# define GPIOA           0x12            // general purpose i/o port register (write modifies OLAT)
# define GPIOB           0x13
# define OLATA           0x14            // output latch register
# define OLATB           0x15

extern i2c_status_t mcp23018_status;
# define MCP23018_I2C_TIMEOUT 100

uint8_t init_mcp23018(void);
#endif

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

/*
 *   LEFT HAND,
 *  RIGHT HAND
 */
#define LAYOUT_ergodox(                                         \
                                                                \
    k00,k01,k02,k03,k04,k05,k06,                                \
    k10,k11,k12,k13,k14,k15,k16,                                \
    k20,k21,k22,k23,k24,k25,                                    \
    k30,k31,k32,k33,k34,k35,k36,                                \
    k40,k41,k42,k43,k44,                                        \
                            k55,k56,                            \
                                k54,                            \
                        k53,k52,k51,                            \
                                                                \
        k0D,k0C,k0B,k0A,k09,k08,k07,                            \
        k1D,k1C,k1B,k1A,k19,k18,k17,                            \
            k2D,k2C,k2B,k2A,k29,k28,                            \
        k3D,k3C,k3B,k3A,k39,k38,k37,                            \
                k4D,k4C,k4B,k4A,k49,                            \
    k5C,k5B,                                                    \
    k5A,                                                        \
    k59,k58,k57 )                                               \
                                                                \
   /* matrix positions */                                       \
   {                                                            \
    { k00,   k01,   k02, k03, k04, k05,   k06,   k07,   k08,   k09, k0A, k0B, k0C,   k0D   }, \
    { k10,   k11,   k12, k13, k14, k15,   k16,   k17,   k18,   k19, k1A, k1B, k1C,   k1D   }, \
    { k20,   k21,   k22, k23, k24, k25,   KC_NO, k28,   k29,   k2A, k2B, k2C, k2D,   KC_NO }, \
    { k30,   k31,   k32, k33, k34, k35,   k36,   k37,   k38,   k39, k3A, k3B, k3C,   k3D   }, \
    { k40,   k41,   k42, k43, k44, k53,   k52,   k49,   k4A,   k4B, k4C, k4D, k57,   k58   }, \
    { KC_NO, KC_NO, k56, k51, k54, KC_NO, k55,   KC_NO, KC_NO, k59, k5C, k5A, KC_NO, k5B   }  \
   }

#define LAYOUT LAYOUT_ergodox

