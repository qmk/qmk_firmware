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

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

/**
 * @file
 * @brief Sysex utility functions
 *
 * These functions are for converting data to and from a "midi-safe" format,
 * which can be use to send data with sysex messages.  Sysex messages may only
 * contain data where the to bit is not set.
 *
 * An "encoded" midi message is one that contains all of the data from its
 * original state, but does not have any of the top bits set.
 *
 * Every 7 bytes of decoded data is converted into 8 bytes of encoded data and
 * visa-versa.  If you'd like to operate on small segments, make sure that you
 * encode in 7 byte increments and decode in 8 byte increments.
 *
 */

/** @defgroup sysex_tools Sysex utility functions
 * @{
 */

/**
 * @brief Compute the length of a message after it is encoded.
 *
 * @param decoded_length The length, in bytes, of the message to encode.
 *
 * @return The length, in bytes, of the message after encodeing.
 */
uint16_t sysex_encoded_length(uint16_t decoded_length);

/**
 * @brief Compute the length of a message after it is decoded.
 *
 * @param encoded_length The length, in bytes, of the encoded message.
 *
 * @return The length, in bytes, of the message after it is decoded.
 */
uint16_t sysex_decoded_length(uint16_t encoded_length);

/**
 * @brief Encode data so that it can be transmitted safely in a sysex message.
 *
 * @param encoded The output data buffer, must be at least sysex_encoded_length(length) bytes long.
 * @param source The input buffer of data to be encoded.
 * @param length The number of bytes from the input buffer to encode.
 *
 * @return number of bytes encoded.
 */
uint16_t sysex_encode(uint8_t *encoded, const uint8_t *source, uint16_t length);

/**
 * @brief Decode encoded data.
 *
 * @param decoded The output data buffer, must be at least sysex_decoded_length(length) bytes long.
 * @param source The input buffer of data to be decoded.
 * @param length The number of bytes from the input buffer to decode.
 *
 * @return number of bytes decoded.
 */
uint16_t sysex_decode(uint8_t *decoded, const uint8_t *source, uint16_t length);

/**@}*/

#ifdef __cplusplus
}
#endif
