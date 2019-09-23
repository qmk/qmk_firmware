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

#include "midi_device.h"
#include "midi.h"

#ifndef NULL
#    define NULL 0
#endif

// forward declarations, internally used to call the callbacks
void midi_input_callbacks(MidiDevice* device, uint16_t cnt, uint8_t byte0, uint8_t byte1, uint8_t byte2);
void midi_process_byte(MidiDevice* device, uint8_t input);

void midi_device_init(MidiDevice* device) {
    device->input_state = IDLE;
    device->input_count = 0;
    bytequeue_init(&device->input_queue, device->input_queue_data, MIDI_INPUT_QUEUE_LENGTH);

    // three byte funcs
    device->input_cc_callback           = NULL;
    device->input_noteon_callback       = NULL;
    device->input_noteoff_callback      = NULL;
    device->input_aftertouch_callback   = NULL;
    device->input_pitchbend_callback    = NULL;
    device->input_songposition_callback = NULL;

    // two byte funcs
    device->input_progchange_callback      = NULL;
    device->input_chanpressure_callback    = NULL;
    device->input_songselect_callback      = NULL;
    device->input_tc_quarterframe_callback = NULL;

    // one byte funcs
    device->input_realtime_callback    = NULL;
    device->input_tunerequest_callback = NULL;

    // var byte functions
    device->input_sysex_callback       = NULL;
    device->input_fallthrough_callback = NULL;
    device->input_catchall_callback    = NULL;

    device->pre_input_process_callback = NULL;
}

void midi_device_input(MidiDevice* device, uint8_t cnt, uint8_t* input) {
    uint8_t i;
    for (i = 0; i < cnt; i++) bytequeue_enqueue(&device->input_queue, input[i]);
}

void midi_device_set_send_func(MidiDevice* device, midi_var_byte_func_t send_func) { device->send_func = send_func; }

void midi_device_set_pre_input_process_func(MidiDevice* device, midi_no_byte_func_t pre_process_func) { device->pre_input_process_callback = pre_process_func; }

void midi_device_process(MidiDevice* device) {
    // call the pre_input_process_callback if there is one
    if (device->pre_input_process_callback) device->pre_input_process_callback(device);

    // pull stuff off the queue and process
    byteQueueIndex_t len = bytequeue_length(&device->input_queue);
    uint16_t         i;
    // TODO limit number of bytes processed?
    for (i = 0; i < len; i++) {
        uint8_t val = bytequeue_get(&device->input_queue, 0);
        midi_process_byte(device, val);
        bytequeue_remove(&device->input_queue, 1);
    }
}

void midi_process_byte(MidiDevice* device, uint8_t input) {
    if (midi_is_realtime(input)) {
        // call callback, store and restore state
        input_state_t state = device->input_state;
        device->input_state = ONE_BYTE_MESSAGE;
        midi_input_callbacks(device, 1, input, 0, 0);
        device->input_state = state;
    } else if (midi_is_statusbyte(input)) {
        // store the byte
        if (device->input_state != SYSEX_MESSAGE) {
            device->input_buffer[0] = input;
            device->input_count     = 1;
        }
        switch (midi_packet_length(input)) {
            case ONE:
                device->input_state = ONE_BYTE_MESSAGE;
                ;
                midi_input_callbacks(device, 1, input, 0, 0);
                device->input_state = IDLE;
                break;
            case TWO:
                device->input_state = TWO_BYTE_MESSAGE;
                break;
            case THREE:
                device->input_state = THREE_BYTE_MESSAGE;
                break;
            case UNDEFINED:
                switch (input) {
                    case SYSEX_BEGIN:
                        device->input_state     = SYSEX_MESSAGE;
                        device->input_buffer[0] = input;
                        device->input_count     = 1;
                        break;
                    case SYSEX_END:
                        // send what is left in the input buffer, set idle
                        device->input_buffer[device->input_count % 3] = input;
                        device->input_count += 1;
                        // call the callback
                        midi_input_callbacks(device, device->input_count, device->input_buffer[0], device->input_buffer[1], device->input_buffer[2]);
                        device->input_state = IDLE;
                        break;
                    default:
                        device->input_state = IDLE;
                        device->input_count = 0;
                }

                break;
            default:
                device->input_state = IDLE;
                device->input_count = 0;
                break;
        }
    } else {
        if (device->input_state != IDLE) {
            // store the byte
            device->input_buffer[device->input_count % 3] = input;
            // increment count
            uint16_t prev = device->input_count;
            device->input_count += 1;

            switch (prev % 3) {
                case 2:
                    // call callback
                    midi_input_callbacks(device, device->input_count, device->input_buffer[0], device->input_buffer[1], device->input_buffer[2]);
                    if (device->input_state != SYSEX_MESSAGE) {
                        // set to 1, keeping status byte, allowing for running status
                        device->input_count = 1;
                    }
                    break;
                case 1:
                    if (device->input_state == TWO_BYTE_MESSAGE) {
                        // call callback
                        midi_input_callbacks(device, device->input_count, device->input_buffer[0], device->input_buffer[1], 0);
                        if (device->input_state != SYSEX_MESSAGE) {
                            // set to 1, keeping status byte, allowing for running status
                            device->input_count = 1;
                        }
                    }
                    break;
                case 0:
                default:
                    // one byte messages are dealt with directly
                    break;
            }
        }
    }
}

void midi_input_callbacks(MidiDevice* device, uint16_t cnt, uint8_t byte0, uint8_t byte1, uint8_t byte2) {
    // did we end up calling a callback?
    bool called = false;
    if (device->input_state == SYSEX_MESSAGE) {
        if (device->input_sysex_callback) {
            const uint16_t start  = ((cnt - 1) / 3) * 3;
            const uint8_t  length = (cnt - start);
            uint8_t        data[3];
            data[0] = byte0;
            data[1] = byte1;
            data[2] = byte2;
            device->input_sysex_callback(device, start, length, data);
            called = true;
        }
    } else {
        switch (cnt) {
            case 3: {
                midi_three_byte_func_t func = NULL;
                switch (byte0 & 0xF0) {
                    case MIDI_CC:
                        func = device->input_cc_callback;
                        break;
                    case MIDI_NOTEON:
                        func = device->input_noteon_callback;
                        break;
                    case MIDI_NOTEOFF:
                        func = device->input_noteoff_callback;
                        break;
                    case MIDI_AFTERTOUCH:
                        func = device->input_aftertouch_callback;
                        break;
                    case MIDI_PITCHBEND:
                        func = device->input_pitchbend_callback;
                        break;
                    case 0xF0:
                        if (byte0 == MIDI_SONGPOSITION) func = device->input_songposition_callback;
                        break;
                    default:
                        break;
                }
                if (func) {
                    // mask off the channel for non song position functions
                    if (byte0 == MIDI_SONGPOSITION)
                        func(device, byte0, byte1, byte2);
                    else
                        func(device, byte0 & 0x0F, byte1, byte2);
                    called = true;
                }
            } break;
            case 2: {
                midi_two_byte_func_t func = NULL;
                switch (byte0 & 0xF0) {
                    case MIDI_PROGCHANGE:
                        func = device->input_progchange_callback;
                        break;
                    case MIDI_CHANPRESSURE:
                        func = device->input_chanpressure_callback;
                        break;
                    case 0xF0:
                        if (byte0 == MIDI_SONGSELECT)
                            func = device->input_songselect_callback;
                        else if (byte0 == MIDI_TC_QUARTERFRAME)
                            func = device->input_tc_quarterframe_callback;
                        break;
                    default:
                        break;
                }
                if (func) {
                    // mask off the channel
                    if (byte0 == MIDI_SONGSELECT || byte0 == MIDI_TC_QUARTERFRAME)
                        func(device, byte0, byte1);
                    else
                        func(device, byte0 & 0x0F, byte1);
                    called = true;
                }
            } break;
            case 1: {
                midi_one_byte_func_t func = NULL;
                if (midi_is_realtime(byte0))
                    func = device->input_realtime_callback;
                else if (byte0 == MIDI_TUNEREQUEST)
                    func = device->input_tunerequest_callback;
                if (func) {
                    func(device, byte0);
                    called = true;
                }
            } break;
            default:
                // just in case
                if (cnt > 3) cnt = 0;
                break;
        }
    }

    // if there is fallthrough default callback and we haven't called a more specific one,
    // call the fallthrough
    if (!called && device->input_fallthrough_callback) device->input_fallthrough_callback(device, cnt, byte0, byte1, byte2);
    // always call the catch all if it exists
    if (device->input_catchall_callback) device->input_catchall_callback(device, cnt, byte0, byte1, byte2);
}
