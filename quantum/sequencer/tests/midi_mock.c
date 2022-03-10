/* Copyright 2020 Rodolphe Belouin
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

#include "midi_mock.h"

uint16_t last_noteon  = 0;
uint16_t last_noteoff = 0;

uint16_t midi_compute_note(uint16_t keycode) {
    return keycode;
}

void process_midi_basic_noteon(uint16_t note) {
    last_noteon = note;
}

void process_midi_basic_noteoff(uint16_t note) {
    last_noteoff = note;
}
