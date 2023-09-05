/* Copyright 2017 Joseph Wasson
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

#include <stdint.h>
#include <stdbool.h>
#include "action.h"

#define BOLT_STROKE_SIZE 4
#define GEMINI_STROKE_SIZE 6

#ifdef STENO_ENABLE_GEMINI
#    define MAX_STROKE_SIZE GEMINI_STROKE_SIZE
#else
#    define MAX_STROKE_SIZE BOLT_STROKE_SIZE
#endif

typedef enum {
    STENO_MODE_GEMINI,
    STENO_MODE_BOLT,
} steno_mode_t;

bool process_steno(uint16_t keycode, keyrecord_t *record);
#ifdef STENO_ENABLE_ALL
void steno_init(void);
void steno_set_mode(steno_mode_t mode);
#endif // STENO_ENABLE_ALL
