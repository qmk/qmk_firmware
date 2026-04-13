/* Copyright 2019 Jason Williams (Wilba)
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

// Changing the layout options size after release will invalidate EEPROM,
// but this is something that should be set correctly on initial implementation.
// 1 byte is enough for most uses (i.e. 8 binary states, or 6 binary + 1 ternary/quaternary )
#ifndef VIA_EEPROM_LAYOUT_OPTIONS_SIZE
#    define VIA_EEPROM_LAYOUT_OPTIONS_SIZE 1
#endif

#ifndef VIA_EEPROM_CUSTOM_CONFIG_SIZE
#    define VIA_EEPROM_CUSTOM_CONFIG_SIZE 0
#endif

#define EECONFIG_MODULE_VIA_DATA_SIZE (3 + (VIA_EEPROM_LAYOUT_OPTIONS_SIZE) + (VIA_EEPROM_CUSTOM_CONFIG_SIZE))
