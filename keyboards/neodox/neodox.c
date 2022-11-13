/* Copyright 2022 MatteoDM <matteodalmo@gmail.com>
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
#include "neodox.h"


/* Mask out handedness diode to prevent it
*  from keeping the keyboard awake
* - just mirroring `KC_NO` in the `LAYOUT`
*   macro to keep it simple
*/
const matrix_row_t matrix_mask[] = {
    0b00111111,
    0b00111111,
    0b01111111,
    0b01111111,
    0b01111111,
    0b00111111,
    0b00111111,
    0b01111111,
    0b01111111,
    0b01111111    
};