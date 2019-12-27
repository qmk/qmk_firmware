// midi for embedded chips,
// Copyright 2010 Alex Norman
//
// This file is part of avr-midi.
//
// avr-midi is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
// avr-midi is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with avr-midi.  If not, see <http://www.gnu.org/licenses/>.

#include "midi.h"
#include <string.h>  //for memcpy

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#ifndef NULL
#    define NULL 0
#endif

bool midi_is_statusbyte(uint8_t theByte) { return (bool)(theByte & MIDI_STATUSMASK); }

bool midi_is_realtime(uint8_t theByte) { return (theByte >= MIDI_CLOCK); }

midi_packet_length_t midi_packet_length(uint8_t status) {
    switch (status & 0xF0) {
        case MIDI_CC:
        case MIDI_NOTEON:
        case MIDI_NOTEOFF:
        case MIDI_AFTERTOUCH:
        case MIDI_PITCHBEND:
            return THREE;
        case MIDI_PROGCHANGE:
        case MIDI_CHANPRESSURE:
        case MIDI_SONGSELECT:
            return TWO;
        case 0xF0:
            switch (status) {
                case MIDI_CLOCK:
                case MIDI_TICK:
                case MIDI_START:
                case MIDI_CONTINUE:
                case MIDI_STOP:
                case MIDI_ACTIVESENSE:
                case MIDI_RESET:
                case MIDI_TUNEREQUEST:
                    return ONE;
                case MIDI_SONGPOSITION:
                    return THREE;
                case MIDI_TC_QUARTERFRAME:
                case MIDI_SONGSELECT:
                    return TWO;
                case SYSEX_END:
                case SYSEX_BEGIN:
                default:
                    return UNDEFINED;
            }
        default:
            return UNDEFINED;
    }
}

void midi_send_cc(MidiDevice* device, uint8_t chan, uint8_t num, uint8_t val) {
    // CC Status: 0xB0 to 0xBF where the low nibble is the MIDI channel.
    // CC Data: Controller Num, Controller Val
    device->send_func(device, 3, MIDI_CC | (chan & MIDI_CHANMASK), num & 0x7F, val & 0x7F);
}

void midi_send_noteon(MidiDevice* device, uint8_t chan, uint8_t num, uint8_t vel) {
    // Note Data: Note Num, Note Velocity
    device->send_func(device, 3, MIDI_NOTEON | (chan & MIDI_CHANMASK), num & 0x7F, vel & 0x7F);
}

void midi_send_noteoff(MidiDevice* device, uint8_t chan, uint8_t num, uint8_t vel) {
    // Note Data: Note Num, Note Velocity
    device->send_func(device, 3, MIDI_NOTEOFF | (chan & MIDI_CHANMASK), num & 0x7F, vel & 0x7F);
}

void midi_send_aftertouch(MidiDevice* device, uint8_t chan, uint8_t note_num, uint8_t amt) { device->send_func(device, 3, MIDI_AFTERTOUCH | (chan & MIDI_CHANMASK), note_num & 0x7F, amt & 0x7F); }

// XXX does this work right?
// amt in range -0x2000, 0x1fff
// uAmt should be in range..
// 0x0000 to 0x3FFF
void midi_send_pitchbend(MidiDevice* device, uint8_t chan, int16_t amt) {
    uint16_t uAmt;
    // check range
    if (amt > 0x1fff) {
        uAmt = 0x3FFF;
    } else if (amt < -0x2000) {
        uAmt = 0;
    } else {
        uAmt = amt + 0x2000;
    }
    device->send_func(device, 3, MIDI_PITCHBEND | (chan & MIDI_CHANMASK), uAmt & 0x7F, (uAmt >> 7) & 0x7F);
}

void midi_send_programchange(MidiDevice* device, uint8_t chan, uint8_t num) { device->send_func(device, 2, MIDI_PROGCHANGE | (chan & MIDI_CHANMASK), num & 0x7F, 0); }

void midi_send_channelpressure(MidiDevice* device, uint8_t chan, uint8_t amt) { device->send_func(device, 2, MIDI_CHANPRESSURE | (chan & MIDI_CHANMASK), amt & 0x7F, 0); }

void midi_send_clock(MidiDevice* device) { device->send_func(device, 1, MIDI_CLOCK, 0, 0); }

void midi_send_tick(MidiDevice* device) { device->send_func(device, 1, MIDI_TICK, 0, 0); }

void midi_send_start(MidiDevice* device) { device->send_func(device, 1, MIDI_START, 0, 0); }

void midi_send_continue(MidiDevice* device) { device->send_func(device, 1, MIDI_CONTINUE, 0, 0); }

void midi_send_stop(MidiDevice* device) { device->send_func(device, 1, MIDI_STOP, 0, 0); }

void midi_send_activesense(MidiDevice* device) { device->send_func(device, 1, MIDI_ACTIVESENSE, 0, 0); }

void midi_send_reset(MidiDevice* device) { device->send_func(device, 1, MIDI_RESET, 0, 0); }

void midi_send_tcquarterframe(MidiDevice* device, uint8_t time) { device->send_func(device, 2, MIDI_TC_QUARTERFRAME, time & 0x7F, 0); }

// XXX is this right?
void midi_send_songposition(MidiDevice* device, uint16_t pos) { device->send_func(device, 3, MIDI_SONGPOSITION, pos & 0x7F, (pos >> 7) & 0x7F); }

void midi_send_songselect(MidiDevice* device, uint8_t song) { device->send_func(device, 2, MIDI_SONGSELECT, song & 0x7F, 0); }

void midi_send_tunerequest(MidiDevice* device) { device->send_func(device, 1, MIDI_TUNEREQUEST, 0, 0); }

void midi_send_byte(MidiDevice* device, uint8_t b) { device->send_func(device, 1, b, 0, 0); }

void midi_send_data(MidiDevice* device, uint16_t count, uint8_t byte0, uint8_t byte1, uint8_t byte2) {
    // ensure that the count passed along is always 3 or lower
    if (count > 3) {
        // TODO how to do this correctly?
    }
    device->send_func(device, count, byte0, byte1, byte2);
}

void midi_send_array(MidiDevice* device, uint16_t count, uint8_t* array) {
    uint16_t i;
    for (i = 0; i < count; i += 3) {
        uint8_t  b[3]    = {0, 0, 0};
        uint16_t to_send = count - i;
        to_send          = (to_send > 3) ? 3 : to_send;
        memcpy(b, array + i, to_send);
        midi_send_data(device, to_send, b[0], b[1], b[2]);
    }
}

void midi_register_cc_callback(MidiDevice* device, midi_three_byte_func_t func) { device->input_cc_callback = func; }

void midi_register_noteon_callback(MidiDevice* device, midi_three_byte_func_t func) { device->input_noteon_callback = func; }

void midi_register_noteoff_callback(MidiDevice* device, midi_three_byte_func_t func) { device->input_noteoff_callback = func; }

void midi_register_aftertouch_callback(MidiDevice* device, midi_three_byte_func_t func) { device->input_aftertouch_callback = func; }

void midi_register_pitchbend_callback(MidiDevice* device, midi_three_byte_func_t func) { device->input_pitchbend_callback = func; }

void midi_register_songposition_callback(MidiDevice* device, midi_three_byte_func_t func) { device->input_songposition_callback = func; }

void midi_register_progchange_callback(MidiDevice* device, midi_two_byte_func_t func) { device->input_progchange_callback = func; }

void midi_register_chanpressure_callback(MidiDevice* device, midi_two_byte_func_t func) { device->input_chanpressure_callback = func; }

void midi_register_songselect_callback(MidiDevice* device, midi_two_byte_func_t func) { device->input_songselect_callback = func; }

void midi_register_tc_quarterframe_callback(MidiDevice* device, midi_two_byte_func_t func) { device->input_tc_quarterframe_callback = func; }

void midi_register_realtime_callback(MidiDevice* device, midi_one_byte_func_t func) { device->input_realtime_callback = func; }

void midi_register_tunerequest_callback(MidiDevice* device, midi_one_byte_func_t func) { device->input_tunerequest_callback = func; }

void midi_register_sysex_callback(MidiDevice* device, midi_sysex_func_t func) { device->input_sysex_callback = func; }

void midi_register_fallthrough_callback(MidiDevice* device, midi_var_byte_func_t func) { device->input_fallthrough_callback = func; }

void midi_register_catchall_callback(MidiDevice* device, midi_var_byte_func_t func) { device->input_catchall_callback = func; }
