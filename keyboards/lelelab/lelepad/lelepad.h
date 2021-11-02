/* Copyright 2021 LeleLab
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
    k11,k12,k13,k14,\
    k21,k22,k23,k24,\
    k31,k32,k33,k34,\
    k41,k42,k43,k44,\
    k51,k52,k53,k54\
) \
{ \
    {k11,k12,k13,k14},\
    {k21,k22,k23,k24},\
    {k31,k32,k33,k34},\
    {k41,k42,k43,k44},\
    {k51,k52,k53,k54}\
}


// status LED
#define SLED_INIT()   DDRD |= (1<<4)
#define SLED_ON()     PORTD &= ~(1<<4)
#define SLED_OFF()    PORTD |= (1<<4)
#define SLED_TOGGLE()   PORTD ^= (1<<4)

