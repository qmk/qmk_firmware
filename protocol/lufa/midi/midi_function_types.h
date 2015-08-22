//midi for embedded chips,
//Copyright 2010 Alex Norman
//
//This file is part of avr-midi.
//
//avr-midi is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//avr-midi is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with avr-midi.  If not, see <http://www.gnu.org/licenses/>.

/**
 * @file
 * @brief Function signature definitions
 */

#ifndef MIDI_FUNCTION_TYPES_H
#define MIDI_FUNCTION_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif 

#include <inttypes.h>
#include <stdbool.h>

//forward declaration
typedef struct _midi_device MidiDevice;

typedef void (* midi_one_byte_func_t)(MidiDevice * device, uint8_t byte);
typedef void (* midi_two_byte_func_t)(MidiDevice * device, uint8_t byte0, uint8_t byte1);
typedef void (* midi_three_byte_func_t)(MidiDevice * device, uint8_t byte0, uint8_t byte1, uint8_t byte2);
//all bytes after count bytes should be ignored
typedef void (* midi_var_byte_func_t)(MidiDevice * device, uint16_t count, uint8_t byte0, uint8_t byte1, uint8_t byte2);

//the start byte tells you how far into the sysex message you are, the data_length tells you how many bytes data is
typedef void (* midi_sysex_func_t)(MidiDevice * device, uint16_t start_byte, uint8_t data_length, uint8_t *data);

#ifdef __cplusplus
}
#endif 

#endif
