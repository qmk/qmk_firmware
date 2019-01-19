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

#ifndef PROCESS_TERMINAL_H
#define PROCESS_TERMINAL_H

#include "quantum.h"

extern const char keycode_to_ascii_lut[58];
extern const char shifted_keycode_to_ascii_lut[58];
extern const char terminal_prompt[8];
bool process_terminal(uint16_t keycode, keyrecord_t *record);

#endif