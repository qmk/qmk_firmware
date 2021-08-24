/* Copyright 2017 Jack Humbert
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
#include "process_unicode_common.h"

#ifndef UCIS_MAX_SYMBOL_LENGTH
#    define UCIS_MAX_SYMBOL_LENGTH 32
#endif
#ifndef UCIS_MAX_CODE_POINTS
#    define UCIS_MAX_CODE_POINTS 3
#endif

typedef struct {
    char *   symbol;
    uint32_t code_points[UCIS_MAX_CODE_POINTS];
} qk_ucis_symbol_t;

typedef struct {
    uint8_t  count;
    uint16_t codes[UCIS_MAX_SYMBOL_LENGTH];
    bool     in_progress : 1;
} qk_ucis_state_t;

extern qk_ucis_state_t qk_ucis_state;

// clang-format off

#define UCIS_TABLE(...) \
    {                   \
        __VA_ARGS__,    \
        { NULL, {} }    \
    }
#define UCIS_SYM(name, ...) \
    { name, {__VA_ARGS__} }

// clang-format on

extern const qk_ucis_symbol_t ucis_symbol_table[];

void qk_ucis_start(void);
void qk_ucis_start_user(void);
void qk_ucis_symbol_fallback(void);
void qk_ucis_success(uint8_t symbol_index);

void register_ucis(const uint32_t *code_points);

bool process_ucis(uint16_t keycode, keyrecord_t *record);
