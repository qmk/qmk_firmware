/* Copyright 2022 Christoph Jabs (BifbofII)
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

#include "bifbofii.h"

#include "progmem.h"

const uint32_t PROGMEM unicode_map[] = {
    [SAE] = 0x00E4, // ä
    [CAE] = 0x00C4, // Ä
    [SUE] = 0x00FC, // ü
    [CUE] = 0x00DC, // Ü
    [SOE] = 0x00F6, // ü
    [COE] = 0x00D6, // Ü
    [SS]  = 0x00DF, // ß
    [EUR] = 0x20AC, // €
    [CPR] = 0x00A9, // ©
};
