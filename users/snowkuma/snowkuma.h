/* Copyright 2019 @ninjonas
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
#include "version.h"
#include "eeprom.h"
#include "process_records.h"
#include "tap_dances.h"
#include "keycodes.h"

#ifdef TAP_DANCE_ENABLE
#    include "tap_dances.h"
#endif
#if defined(KEYBOARD_lily58_rev1) & defined(PROTOCOL_LUFA)
#    include "lufa.h"
#    include "split_util.h"
#endif

enum layers { 
 _COLEMAK = 0,
 _NAV,
 _SYMBOL,
 _NUMBER,
 _ARRANGE,
 _MOUSE,
 _THUMB,
 _FUNCTION
};

