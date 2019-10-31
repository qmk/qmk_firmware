/* Copyright 2017 Jeremy Cowgar
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

#ifndef AUTO_SHIFT_TIMEOUT
#    define AUTO_SHIFT_TIMEOUT 175
#endif

bool process_auto_shift(uint16_t keycode, keyrecord_t *record);

void     autoshift_enable(void);
void     autoshift_disable(void);
void     autoshift_toggle(void);
bool     get_autoshift_state(void);
uint16_t get_autoshift_timeout(void);
void     set_autoshift_timeout(uint16_t timeout);
