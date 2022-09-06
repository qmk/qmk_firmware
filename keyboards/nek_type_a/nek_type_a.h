/* Copyright 2018 REPLACE_WITH_YOUR_NAME
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
#ifndef NEK_TYPE_A_H
#define NEK_TYPE_A_H

#include "quantum.h"
#include <stdint.h>
#include <stdbool.h>
#include <util/delay.h>

#define I2C_ADDR        0b0100000
#define I2C_ADDR_WRITE  ( (I2C_ADDR<<1) | I2C_WRITE )
#define I2C_ADDR_READ   ( (I2C_ADDR<<1) | I2C_READ  )
#define IODIRA          0x00            // i/o direction register
#define IODIRB          0x01
#define GPPUA           0x0C            // GPIO pull-up resistor register
#define GPPUB           0x0D
#define GPIOA           0x12            // general purpose i/o port register (write modifies OLAT)
#define GPIOB           0x13
#define OLATA           0x14            // output latch register
#define OLATB           0x15

extern uint8_t expander_status;
extern uint8_t expander_input_pin_mask;
extern bool i2c_initialized;

void init_expander(void);

#define LAYOUT( \
         L12,      L14, L15, L16, L17,   R11, R12, R13, R14, R15, R16, R17, R18, R19, R1A, R1B, \
    L21, L22, L23, L24, L25, L26, L27,   R21, R22, R23, R24, R25, R26,      R28, R29, R2A, R2B, \
    L31, L32, L33, L34, L35, L36,        R31, R32, R33, R34, R35, R36, R37, R38, R39, R3A, R3B, \
    L41, L42, L43, L44, L45, L46,        R41, R42, R43, R44, R45, R46,      R48,                \
    L51, L52, L53, L54, L55, L56,        R51, R52, R53, R54, R55,           R58,      R5A,      \
    L61, L62, L63,      L65,             R61,      R63,      R65, R66,      R68, R69, R6A, R6B  \
) \
{ \
    { KC_NO,   L12, KC_NO,   L14,   L15,   L16,   L17,   R11,   R12,   R13,   R14,   R15,   R16,   R17,   R18,   R19,   R1A,   R1B }, \
    {   L21,   L22,   L23,   L24,   L25,   L26,   L27,   R21,   R22,   R23,   R24,   R25,   R26, KC_NO,   R28,   R29,   R2A,   R2B }, \
    {   L31,   L32,   L33,   L34,   L35,   L36, KC_NO,   R31,   R32,   R33,   R34,   R35,   R36,   R37,   R38,   R39,   R3A,   R3B }, \
    {   L41,   L42,   L43,   L44,   L45,   L46, KC_NO,   R41,   R42,   R43,   R44,   R45,   R46, KC_NO,   R48, KC_NO, KC_NO, KC_NO }, \
    {   L51,   L52,   L53,   L54,   L55,   L56, KC_NO,   R51,   R52,   R53,   R54,   R55, KC_NO, KC_NO,   R58, KC_NO,   R5A, KC_NO }, \
    {   L61,   L62,   L63, KC_NO,   L65, KC_NO, KC_NO,   R61, KC_NO,   R63, KC_NO,   R65,   R66, KC_NO,   R68,   R69,   R6A,   R6B }, \
}
#endif
