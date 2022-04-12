/* Copyright 2019 Nick Brassel (tzarc)
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

/*
    The size of the transient EEPROM buffer size.
*/
#ifndef TRANSIENT_EEPROM_SIZE
#    include "eeconfig.h"
#    define TRANSIENT_EEPROM_SIZE (((EECONFIG_SIZE + 3) / 4) * 4) // based off eeconfig's current usage, aligned to 4-byte sizes, to deal with LTO
#endif
