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

#define TERMINAL_MAX_ARGS   6
#define TERMINAL_ARGS_LEN  20

typedef struct {
    size_t args_no;
    char args[TERMINAL_MAX_ARGS][TERMINAL_ARGS_LEN];
} terminal_ctx_t;

typedef struct {
    char *string;
    void (*func)(terminal_ctx_t*);
}  stringcase_t;


extern const char keycode_to_ascii_lut[58];
extern const char shifted_keycode_to_ascii_lut[58];
extern const char terminal_prompt[8];
bool              process_terminal(uint16_t keycode, keyrecord_t *record);
void process_terminal_register_user_command(stringcase_t * table);
