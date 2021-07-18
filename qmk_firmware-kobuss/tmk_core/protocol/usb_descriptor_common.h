/* Copyright 2020 Nick Brassel (tzarc)
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

/////////////////////
// RAW Usage page and ID configuration

#ifndef RAW_USAGE_PAGE
#    define RAW_USAGE_PAGE 0xFF60
#endif

#ifndef RAW_USAGE_ID
#    define RAW_USAGE_ID 0x61
#endif

#define RAW_USAGE_PAGE_HI ((uint8_t)(RAW_USAGE_PAGE >> 8))
#define RAW_USAGE_PAGE_LO ((uint8_t)(RAW_USAGE_PAGE & 0xFF))
