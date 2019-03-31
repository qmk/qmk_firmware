/* Copyright 2019 Bence Domonkos
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

#ifndef PROCESS_KOMBOH
#define PROCESS_KOMBOH

#include "quantum.h"

enum kombo_type {
	nested = false,
	instant = true
};

typedef struct _kombo_t {
	uint64_t keys;
	uint16_t keycode;
	enum kombo_type is_instant;
} kombo_t;

bool process_kombo(uint16_t keycode, keyrecord_t *record);
void kombo_toggle(void);
void kombo_enable(void);
void kombo_disable(void);

#endif
