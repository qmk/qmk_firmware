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

/**
 * @file
 * @brief Device implementation functions
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup midi_device Functions used when implementing your own midi device.
 *
 * You use the functions when you are implementing your own midi device.
 *
 * You set a send function to actually send bytes via your device, this method
 * is called when you call a send function with this device, for instance
 * midi_send_cc
 *
 * You use the midi_device_input to process input data from the device and pass
 * it through the device's associated callbacks.
 *
 * You use the midi_device_set_pre_input_process_func if you want to have a
 * function called at the beginning of the device's process function, generally
 * to poll for input and pass that into midi_device_input
 *
 * @{
 */

#include "midi_function_types.h"
#include "bytequeue/bytequeue.h"
#define MIDI_INPUT_QUEUE_LENGTH 192

typedef enum { IDLE, ONE_BYTE_MESSAGE = 1, TWO_BYTE_MESSAGE = 2, THREE_BYTE_MESSAGE = 3, SYSEX_MESSAGE } input_state_t;

typedef void (*midi_no_byte_func_t)(MidiDevice* device);

/**
 * \struct _midi_device
 *
 * @brief This structure represents the input and output functions and
 * processing data for a midi device.
 *
 * A device can represent an actual physical device [serial port, usb port] or
 * something virtual.
 * You should not need to modify this structure directly.
 */
struct _midi_device {
    // output send function
    midi_var_byte_func_t send_func;

    //********input callbacks
    // three byte funcs
    midi_three_byte_func_t input_cc_callback;
    midi_three_byte_func_t input_noteon_callback;
    midi_three_byte_func_t input_noteoff_callback;
    midi_three_byte_func_t input_aftertouch_callback;
    midi_three_byte_func_t input_pitchbend_callback;
    midi_three_byte_func_t input_songposition_callback;
    // two byte funcs
    midi_two_byte_func_t input_progchange_callback;
    midi_two_byte_func_t input_chanpressure_callback;
    midi_two_byte_func_t input_songselect_callback;
    midi_two_byte_func_t input_tc_quarterframe_callback;
    // one byte funcs
    midi_one_byte_func_t input_realtime_callback;
    midi_one_byte_func_t input_tunerequest_callback;

    // sysex
    midi_sysex_func_t input_sysex_callback;

    // only called if more specific callback is not matched
    midi_var_byte_func_t input_fallthrough_callback;
    // called if registered, independent of other callbacks
    midi_var_byte_func_t input_catchall_callback;

    // pre input processing function
    midi_no_byte_func_t pre_input_process_callback;

    // for internal input processing
    uint8_t       input_buffer[3];
    input_state_t input_state;
    uint16_t      input_count;

    // for queueing data between the input and the processing functions
    uint8_t     input_queue_data[MIDI_INPUT_QUEUE_LENGTH];
    byteQueue_t input_queue;
};

/**
 * @brief Process input bytes.  This function parses bytes and calls the
 * appropriate callbacks associated with the given device.  You use this
 * function if you are creating a custom device and you want to have midi
 * input.
 *
 * @param device the midi device to associate the input with
 * @param cnt the number of bytes you are processing
 * @param input the bytes to process
 */
void midi_device_input(MidiDevice* device, uint8_t cnt, uint8_t* input);

/**
 * @brief Set the callback function that will be used for sending output
 * data bytes.  This is only used if you're creating a custom device.
 * You'll most likely want the callback function to disable interrupts so
 * that you can call the various midi send functions without worrying about
 * locking.
 *
 * \param device the midi device to associate this callback with
 * \param send_func the callback function that will do the sending
 */
void midi_device_set_send_func(MidiDevice* device, midi_var_byte_func_t send_func);

/**
 * @brief Set a callback which is called at the beginning of the
 * midi_device_process call.  This can be used to poll for input
 * data and send the data through the midi_device_input function.
 * You'll probably only use this if you're creating a custom device.
 *
 * \param device the midi device to associate this callback with
 * \param midi_no_byte_func_t the actual callback function
 */
void midi_device_set_pre_input_process_func(MidiDevice* device, midi_no_byte_func_t pre_process_func);

/**@}*/

#ifdef __cplusplus
}
#endif
