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

#include "keymap.h"
#include "keymap_midi.h"

uint8_t starting_note = 0x0C;
int offset = 7;

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
	if (id != 0) {
	    if (record->event.pressed) {
	    	midi_send_noteon(&midi_device, opt, (id & 0xFF), 127);
	    } else {
	        midi_send_noteoff(&midi_device, opt, (id & 0xFF), 127);
	    }
	}

    if (record->event.key.col == (MATRIX_COLS - 1) && record->event.key.row == (MATRIX_ROWS - 1)) {
        if (record->event.pressed) {
            starting_note++;
            play_note(((double)261.626)*pow(2.0, -1.0)*pow(2.0,(starting_note + SCALE[0 + offset])/12.0+(MATRIX_ROWS - 1)), 0xC);
            midi_send_cc(&midi_device, 0, 0x7B, 0);
            midi_send_cc(&midi_device, 1, 0x7B, 0);
            midi_send_cc(&midi_device, 2, 0x7B, 0);
            midi_send_cc(&midi_device, 3, 0x7B, 0);
            midi_send_cc(&midi_device, 4, 0x7B, 0);
            return;
        } else {
            stop_note(((double)261.626)*pow(2.0, -1.0)*pow(2.0,(starting_note + SCALE[0 + offset])/12.0+(MATRIX_ROWS - 1)));
            stop_all_notes();
            return;
        }
    }
    if (record->event.key.col == (MATRIX_COLS - 2) && record->event.key.row == (MATRIX_ROWS - 1)) {
        if (record->event.pressed) {
            starting_note--;
            play_note(((double)261.626)*pow(2.0, -1.0)*pow(2.0,(starting_note + SCALE[0 + offset])/12.0+(MATRIX_ROWS - 1)), 0xC);
            midi_send_cc(&midi_device, 0, 0x7B, 0);
            midi_send_cc(&midi_device, 1, 0x7B, 0);
            midi_send_cc(&midi_device, 2, 0x7B, 0);
            midi_send_cc(&midi_device, 3, 0x7B, 0);
            midi_send_cc(&midi_device, 4, 0x7B, 0);
            return;
        } else {
            stop_note(((double)261.626)*pow(2.0, -1.0)*pow(2.0,(starting_note + SCALE[0 + offset])/12.0+(MATRIX_ROWS - 1)));
            stop_all_notes();
            return;
        }
    }

    if (record->event.key.col == (MATRIX_COLS - 3) && record->event.key.row == (MATRIX_ROWS - 1) && record->event.pressed) {
        offset++;
        midi_send_cc(&midi_device, 0, 0x7B, 0);
        midi_send_cc(&midi_device, 1, 0x7B, 0);
        midi_send_cc(&midi_device, 2, 0x7B, 0);
        midi_send_cc(&midi_device, 3, 0x7B, 0);
        midi_send_cc(&midi_device, 4, 0x7B, 0);
        stop_all_notes();
        for (int i = 0; i <= 7; i++) {
            play_note(((double)261.626)*pow(2.0, -1.0)*pow(2.0,(starting_note + SCALE[i + offset])/12.0+(MATRIX_ROWS - 1)), 0xC);
            _delay_us(80000);
            stop_note(((double)261.626)*pow(2.0, -1.0)*pow(2.0,(starting_note + SCALE[i + offset])/12.0+(MATRIX_ROWS - 1)));
            _delay_us(8000);
        }
        return;
    }
    if (record->event.key.col == (MATRIX_COLS - 4) && record->event.key.row == (MATRIX_ROWS - 1) && record->event.pressed) {
        offset--;
        midi_send_cc(&midi_device, 0, 0x7B, 0);
        midi_send_cc(&midi_device, 1, 0x7B, 0);
        midi_send_cc(&midi_device, 2, 0x7B, 0);
        midi_send_cc(&midi_device, 3, 0x7B, 0);
        midi_send_cc(&midi_device, 4, 0x7B, 0);
        stop_all_notes();
        for (int i = 0; i <= 7; i++) {
            play_note(((double)261.626)*pow(2.0, -1.0)*pow(2.0,(starting_note + SCALE[i + offset])/12.0+(MATRIX_ROWS - 1)), 0xC);
            _delay_us(80000);
            stop_note(((double)261.626)*pow(2.0, -1.0)*pow(2.0,(starting_note + SCALE[i + offset])/12.0+(MATRIX_ROWS - 1)));
            _delay_us(8000);
        }
        return;
    }

    if (record->event.pressed) {
    	// midi_send_noteon(&midi_device, record->event.key.row, starting_note + SCALE[record->event.key.col], 127);
        // midi_send_noteon(&midi_device, 0, (starting_note + SCALE[record->event.key.col + offset])+12*(MATRIX_ROWS - record->event.key.row), 127);
        play_note(((double)261.626)*pow(2.0, -1.0)*pow(2.0,(starting_note + SCALE[record->event.key.col + offset])/12.0+(MATRIX_ROWS - record->event.key.row)), 0xF);
    } else {
        // midi_send_noteoff(&midi_device, record->event.key.row, starting_note + SCALE[record->event.key.col], 127);
        // midi_send_noteoff(&midi_device, 0, (starting_note + SCALE[record->event.key.col + offset])+12*(MATRIX_ROWS - record->event.key.row), 127);
        stop_note(((double)261.626)*pow(2.0, -1.0)*pow(2.0,(starting_note + SCALE[record->event.key.col + offset])/12.0+(MATRIX_ROWS - record->event.key.row)));
    }
}