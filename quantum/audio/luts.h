/* Copyright 2016 IBNobody
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

#if defined(__AVR__)
    #include <avr/io.h>
    #include <avr/interrupt.h>
    #include <avr/pgmspace.h>
#else
    #include "ch.h"
    #include "hal.h"
#endif

#ifndef LUTS_H
#define LUTS_H

#define VIBRATO_LUT_LENGTH 20

#define FREQUENCY_LUT_LENGTH 349

extern const float vibrato_lut[VIBRATO_LUT_LENGTH];
extern const uint16_t frequency_lut[FREQUENCY_LUT_LENGTH];

#endif /* LUTS_H */
