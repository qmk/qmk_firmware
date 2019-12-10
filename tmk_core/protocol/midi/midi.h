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
 * @brief The main midi functions
 *
 * This file includes all of the functions you need to set up and process a
 * midi device, send midi, and register midi callbacks.
 *
 */

#ifndef XNOR_MIDI_H
#define XNOR_MIDI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "midi_device.h"
#include "midi_function_types.h"

/**
 * @defgroup midi_device_setup_process Device initialization and processing
 * @brief These are method that you must use to initialize and run a device
 *
 * @{
 */

/**
 * @brief Initialize a device
 *
 * You must call this before using the device in question.
 *
 * @param device the device to initialize
 */
void midi_device_init(MidiDevice* device);  // [implementation in midi_device.c]

/**
 * @brief Process input data
 *
 * This method drives the input processing, you must call this method frequently
 * if you expect to have your input callbacks called.
 *
 * @param device the device to process
 */
void midi_device_process(MidiDevice* device);  // [implementation in midi_device.c]

/**@}*/

/**
 * @defgroup send_functions Midi send functions
 * @brief These are the functions you use to send midi data through a device.
 * @{
 */

/**
 * @brief Send a control change message (cc) via the given device.
 *
 * @param device the device to use for sending
 * @param chan the channel to send on, 0-15
 * @param num the cc num
 * @param val the value of that cc num
 */
void midi_send_cc(MidiDevice* device, uint8_t chan, uint8_t num, uint8_t val);

/**
 * @brief Send a note on message via the given device.
 *
 * @param device the device to use for sending
 * @param chan the channel to send on, 0-15
 * @param num the note number
 * @param vel the note velocity
 */
void midi_send_noteon(MidiDevice* device, uint8_t chan, uint8_t num, uint8_t vel);

/**
 * @brief Send a note off message via the given device.
 *
 * @param device the device to use for sending
 * @param chan the channel to send on, 0-15
 * @param num the note number
 * @param vel the note velocity
 */
void midi_send_noteoff(MidiDevice* device, uint8_t chan, uint8_t num, uint8_t vel);

/**
 * @brief Send an after touch message via the given device.
 *
 * @param device the device to use for sending
 * @param chan the channel to send on, 0-15
 * @param note_num the note number
 * @param amt the after touch amount
 */
void midi_send_aftertouch(MidiDevice* device, uint8_t chan, uint8_t note_num, uint8_t amt);

/**
 * @brief Send a pitch bend message via the given device.
 *
 * @param device the device to use for sending
 * @param chan the channel to send on, 0-15
 * @param amt the bend amount range: -8192..8191, 0 means no bend
 */
void midi_send_pitchbend(MidiDevice* device, uint8_t chan, int16_t amt);  // range -8192, 8191

/**
 * @brief Send a program change message via the given device.
 *
 * @param device the device to use for sending
 * @param chan the channel to send on, 0-15
 * @param num the program to change to
 */
void midi_send_programchange(MidiDevice* device, uint8_t chan, uint8_t num);

/**
 * @brief Send a channel pressure message via the given device.
 *
 * @param device the device to use for sending
 * @param chan the channel to send on, 0-15
 * @param amt the amount of channel pressure
 */
void midi_send_channelpressure(MidiDevice* device, uint8_t chan, uint8_t amt);

/**
 * @brief Send a clock message via the given device.
 *
 * @param device the device to use for sending
 */
void midi_send_clock(MidiDevice* device);

/**
 * @brief Send a tick message via the given device.
 *
 * @param device the device to use for sending
 */
void midi_send_tick(MidiDevice* device);

/**
 * @brief Send a start message via the given device.
 *
 * @param device the device to use for sending
 */
void midi_send_start(MidiDevice* device);

/**
 * @brief Send a continue message via the given device.
 *
 * @param device the device to use for sending
 */
void midi_send_continue(MidiDevice* device);

/**
 * @brief Send a stop message via the given device.
 *
 * @param device the device to use for sending
 */
void midi_send_stop(MidiDevice* device);

/**
 * @brief Send an active sense message via the given device.
 *
 * @param device the device to use for sending
 */
void midi_send_activesense(MidiDevice* device);

/**
 * @brief Send a reset message via the given device.
 *
 * @param device the device to use for sending
 */
void midi_send_reset(MidiDevice* device);

/**
 * @brief Send a tc quarter frame message via the given device.
 *
 * @param device the device to use for sending
 * @param time the time of this quarter frame, range 0..16383
 */
void midi_send_tcquarterframe(MidiDevice* device, uint8_t time);

/**
 * @brief Send a song position message via the given device.
 *
 * @param device the device to use for sending
 * @param pos the song position
 */
void midi_send_songposition(MidiDevice* device, uint16_t pos);

/**
 * @brief Send a song select message via the given device.
 *
 * @param device the device to use for sending
 * @param song the song to select
 */
void midi_send_songselect(MidiDevice* device, uint8_t song);

/**
 * @brief Send a tune request message via the given device.
 *
 * @param device the device to use for sending
 */
void midi_send_tunerequest(MidiDevice* device);

/**
 * @brief Send a byte via the given device.
 *
 * This is a generic method for sending data via the given midi device.
 * This would be useful for sending sysex data or messages that are not
 * implemented in this API, if there are any.  Please contact the author
 * if you find some so we can add them.
 *
 * @param device the device to use for sending
 * @param b the byte to send
 */
void midi_send_byte(MidiDevice* device, uint8_t b);

/**
 * @brief Send up to 3 bytes of data
 *
 * % 4 is applied to count so that you can use this to pass sysex through
 *
 * @param device the device to use for sending
 * @param count the count of bytes to send, %4 is applied
 * @param byte0 the first byte
 * @param byte1 the second byte, ignored if cnt % 4 != 2
 * @param byte2 the third byte, ignored if cnt % 4 != 3
 */
void midi_send_data(MidiDevice* device, uint16_t count, uint8_t byte0, uint8_t byte1, uint8_t byte2);

/**
 * @brief Send an array of formatted midi data.
 *
 * Can be used for sysex.
 *
 * @param device the device to use for sending
 * @param count the count of bytes to send
 * @param array the array of bytes
 */
void midi_send_array(MidiDevice* device, uint16_t count, uint8_t* array);

/**@}*/

/**
 * @defgroup input_callback_reg Input callback registration functions
 *
 * @brief These are the functions you use to register your input callbacks.
 *
 * The functions are called when the appropriate midi message is matched on the
 * associated device's input.
 *
 * @{
 */

// three byte funcs

/**
 * @brief Register a control change message (cc) callback.
 *
 * @param device the device associate with
 * @param func the callback function to register
 */
void midi_register_cc_callback(MidiDevice* device, midi_three_byte_func_t func);

/**
 * @brief Register a note on callback.
 *
 * @param device the device associate with
 * @param func the callback function to register
 */
void midi_register_noteon_callback(MidiDevice* device, midi_three_byte_func_t func);

/**
 * @brief Register a note off callback.
 *
 * @param device the device associate with
 * @param func the callback function to register
 */
void midi_register_noteoff_callback(MidiDevice* device, midi_three_byte_func_t func);

/**
 * @brief Register an after touch callback.
 *
 * @param device the device associate with
 * @param func the callback function to register
 */

void midi_register_aftertouch_callback(MidiDevice* device, midi_three_byte_func_t func);

/**
 * @brief Register a pitch bend callback.
 *
 * @param device the device associate with
 * @param func the callback function to register
 */
void midi_register_pitchbend_callback(MidiDevice* device, midi_three_byte_func_t func);

/**
 * @brief Register a song position callback.
 *
 * @param device the device associate with
 * @param func the callback function to register
 */
void midi_register_songposition_callback(MidiDevice* device, midi_three_byte_func_t func);

// two byte funcs

/**
 * @brief Register a program change callback.
 *
 * @param device the device associate with
 * @param func the callback function to register
 */
void midi_register_progchange_callback(MidiDevice* device, midi_two_byte_func_t func);

/**
 * @brief Register a channel pressure callback.
 *
 * @param device the device associate with
 * @param func the callback function to register
 */
void midi_register_chanpressure_callback(MidiDevice* device, midi_two_byte_func_t func);

/**
 * @brief Register a song select callback.
 *
 * @param device the device associate with
 * @param func the callback function to register
 */
void midi_register_songselect_callback(MidiDevice* device, midi_two_byte_func_t func);

/**
 * @brief Register a tc quarter frame callback.
 *
 * @param device the device associate with
 * @param func the callback function to register
 */
void midi_register_tc_quarterframe_callback(MidiDevice* device, midi_two_byte_func_t func);

// one byte funcs

/**
 * @brief Register a realtime callback.
 *
 * The callback will be called for all of the real time message types.
 *
 * @param device the device associate with
 * @param func the callback function to register
 */
void midi_register_realtime_callback(MidiDevice* device, midi_one_byte_func_t func);

/**
 * @brief Register a tune request callback.
 *
 * @param device the device associate with
 * @param func the callback function to register
 */
void midi_register_tunerequest_callback(MidiDevice* device, midi_one_byte_func_t func);

/**
 * @brief Register a sysex callback.
 *
 * @param device the device associate with
 * @param func the callback function to register
 */
void midi_register_sysex_callback(MidiDevice* device, midi_sysex_func_t func);

/**
 * @brief Register fall through callback.
 *
 * This is only called if a more specific callback is not matched and called.
 * For instance, if you don't register a note on callback but you get a note on message
 * the fall through callback will be called, if it is registered.
 *
 * @param device the device associate with
 * @param func the callback function to register
 */
void midi_register_fallthrough_callback(MidiDevice* device, midi_var_byte_func_t func);

/**
 * @brief Register a catch all callback.
 *
 * If registered, the catch all callback is called for every message that is
 * matched, even if a more specific or the fallthrough callback is registered.
 *
 * @param device the device associate with
 * @param func the callback function to register
 */
void midi_register_catchall_callback(MidiDevice* device, midi_var_byte_func_t func);

/**@}*/

/**
 * @defgroup midi_util Device independent utility functions.
 * @{
 */

/**
 * \enum midi_packet_length_t
 *
 * An enumeration of the possible packet length values.
 */
typedef enum { UNDEFINED = 0, ONE = 1, TWO = 2, THREE = 3 } midi_packet_length_t;

/**
 * @brief Test to see if the byte given is a status byte
 * @param theByte the byte to test
 * @return true if the byte given is a midi status byte
 */
bool midi_is_statusbyte(uint8_t theByte);

/**
 * @brief Test to see if the byte given is a realtime message
 * @param theByte the byte to test
 * @return true if it is a realtime message, false otherwise
 */
bool midi_is_realtime(uint8_t theByte);

/**
 * @brief Find the length of the packet associated with the status byte given
 * @param status the status byte
 * @return the length of the packet, will return UNDEFINED if the byte is not
 * a status byte or if it is a sysex status byte
 */
midi_packet_length_t midi_packet_length(uint8_t status);

/**@}*/

/**
 * @defgroup defines Midi status and miscellaneous utility #defines
 *
 * @{
 */

#define SYSEX_BEGIN 0xF0
#define SYSEX_END 0xF7

// if you and this with a byte and you get anything non-zero
// it is a status message
#define MIDI_STATUSMASK 0x80
// if you and this with a status message that contains channel info,
// you'll get the channel
#define MIDI_CHANMASK 0x0F

#define MIDI_CC 0xB0
#define MIDI_NOTEON 0x90
#define MIDI_NOTEOFF 0x80
#define MIDI_AFTERTOUCH 0xA0
#define MIDI_PITCHBEND 0xE0
#define MIDI_PROGCHANGE 0xC0
#define MIDI_CHANPRESSURE 0xD0

// midi realtime
#define MIDI_CLOCK 0xF8
#define MIDI_TICK 0xF9
#define MIDI_START 0xFA
#define MIDI_CONTINUE 0xFB
#define MIDI_STOP 0xFC
#define MIDI_ACTIVESENSE 0xFE
#define MIDI_RESET 0xFF

#define MIDI_TC_QUARTERFRAME 0xF1
#define MIDI_SONGPOSITION 0xF2
#define MIDI_SONGSELECT 0xF3
#define MIDI_TUNEREQUEST 0xF6

// This ID is for educational or development use only
#define SYSEX_EDUMANUFID 0x7D

/**@}*/

#ifdef __cplusplus
}
#endif

#endif
