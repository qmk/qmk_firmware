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

#include "keymap_common.h"
#include "keymap_midi.h"
#include <lufa.h>

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    if (record->event.pressed) {
    	midi_send_noteon(&midi_device, opt, (id & 0xFF), 127);
    } else {
        midi_send_noteoff(&midi_device, opt, (id & 0xFF), 127);
    }
}