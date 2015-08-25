/*
Copyright 2015 Jack Humbert <jack.humb@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "extended_keymap_common.h"
#include "keymap_midi.h"
#include <lufa.h>

uint8_t starting_note = 0x0C;

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
	if (id != 0) {
	    if (record->event.pressed) {
	    	midi_send_noteon(&midi_device, opt, (id & 0xFF), 127);
	    } else {
	        midi_send_noteoff(&midi_device, opt, (id & 0xFF), 127);
	    }
	}

    if (record->event.key.col == 11 && record->event.key.row == 4 && record->event.pressed) {
        starting_note++;
        midi_send_cc(&midi_device, 0, 0x7B, 0);
        midi_send_cc(&midi_device, 1, 0x7B, 0);
        midi_send_cc(&midi_device, 2, 0x7B, 0);
        midi_send_cc(&midi_device, 3, 0x7B, 0);
        midi_send_cc(&midi_device, 4, 0x7B, 0);
    }
    if (record->event.key.col == 8 && record->event.key.row == 4 && record->event.pressed) {
        starting_note--;
        midi_send_cc(&midi_device, 0, 0x7B, 0);
        midi_send_cc(&midi_device, 1, 0x7B, 0);
        midi_send_cc(&midi_device, 2, 0x7B, 0);
        midi_send_cc(&midi_device, 3, 0x7B, 0);
        midi_send_cc(&midi_device, 4, 0x7B, 0);
    }

    if (record->event.pressed) {
    	midi_send_noteon(&midi_device, record->event.key.row, starting_note + SCALE[record->event.key.col], 127);
    } else {
        midi_send_noteoff(&midi_device, record->event.key.row, starting_note + SCALE[record->event.key.col], 127);
    }
}