/* Copyright 2016 Jack Humbert
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

#ifndef PROCESS_CHORDING_H
#define PROCESS_CHORDING_H

#include "quantum.h"

// Chording stuff
#define CHORDING_MAX 4
bool chording = false;

uint8_t chord_keys[CHORDING_MAX] = {0};
uint8_t chord_key_count = 0;
uint8_t chord_key_down = 0;

bool process_chording(uint16_t keycode, keyrecord_t *record);

#endif
