/* Copyright 2021
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

/**
 * \file
 *
 * \defgroup send_string Send String API
 *
 * \brief These functions allow you to create macros by typing out sequences of keystrokes.
 * \{
 */

#include <stdint.h>

#include "progmem.h"
#include "send_string_keycodes.h"

// Look-Up Tables (LUTs) to convert ASCII character to keycode sequence.
extern const uint8_t ascii_to_shift_lut[16];
extern const uint8_t ascii_to_altgr_lut[16];
extern const uint8_t ascii_to_dead_lut[16];
extern const uint8_t ascii_to_keycode_lut[128];

// clang-format off
#define KCLUT_ENTRY(a, b, c, d, e, f, g, h) \
    ( ((a) ? 1 : 0) << 0 \
    | ((b) ? 1 : 0) << 1 \
    | ((c) ? 1 : 0) << 2 \
    | ((d) ? 1 : 0) << 3 \
    | ((e) ? 1 : 0) << 4 \
    | ((f) ? 1 : 0) << 5 \
    | ((g) ? 1 : 0) << 6 \
    | ((h) ? 1 : 0) << 7 )
// clang-format on

/**
 * \brief Type out a string of ASCII characters.
 *
 * This function simply calls `send_string_with_delay(string, TAP_CODE_DELAY)`.
 *
 * Most keycodes from the basic keycode range are also supported by way of a special sequence - see `send_string_keycodes.h`.
 *
 * \param string The string to type out.
 */
void send_string(const char *string);

/**
 * \brief Type out a string of ASCII characters, with a delay between each character.
 *
 * \param string The string to type out.
 * \param interval The amount of time, in milliseconds, to wait before typing the next character. Note this can be set to 0 to ensure no delay, regardless of what TAP_CODE_DELAY is set to.
 */
void send_string_with_delay(const char *string, uint8_t interval);

/**
 * \brief Type out an ASCII character.
 *
 * This function simply calls `send_char_with_delay(string, TAP_CODE_DELAY)`.
 *
 * \param ascii_code The character to type.
 */
void send_char(char ascii_code);

/**
 * \brief Type out an ASCII character, with a delay between any modifiers.
 *
 * \param ascii_code The character to type.
 * \param interval The amount of time, in milliseconds, to wait in between key presses. Note this can be set to 0 to ensure no delay, regardless of what TAP_CODE_DELAY is set to.
 */
void send_char_with_delay(char ascii_code, uint8_t interval);

/**
 * \brief Type out an eight digit (unsigned 32-bit) hexadecimal value.
 *
 * The format is `[0-9a-f]{8}`, eg. `00000000` through `ffffffff`.
 *
 * \param number The value to type, from 0 to 4,294,967,295.
 */
void send_dword(uint32_t number);

/**
 * \brief Type out a four digit (unsigned 16-bit) hexadecimal value.
 *
 * The format is `[0-9a-f]{4}`, eg. `0000` through `ffff`.
 *
 * \param number The value to type, from 0 to 65,535.
 */
void send_word(uint16_t number);

/**
 * \brief Type out a two digit (8-bit) hexadecimal value.
 *
 * The format is `[0-9a-f]{2}`, eg. `00` through `ff`.
 *
 * \param number The value to type, from 0 to 255.
 */
void send_byte(uint8_t number);

/**
 * \brief Type out a single hexadecimal digit.
 *
 * The format is `[0-9a-f]{1}`, eg. `0` through `f`.
 *
 * \param number The value to type, from 0 to 15.
 */
void send_nibble(uint8_t number);

/**
 * \brief Type a pseudorandom character from the set `A-Z`, `a-z`, `0-9`, `+` and `/`.
 */
void tap_random_base64(void);

#if defined(__AVR__) || defined(__DOXYGEN__)
/**
 * \brief Type out a PROGMEM string of ASCII characters.
 *
 * On ARM devices, this function is simply an alias for send_string_with_delay(string, 0).
 *
 * \param string The string to type out.
 */
void send_string_P(const char *string);

/**
 * \brief Type out a PROGMEM string of ASCII characters, with a delay between each character.
 *
 * On ARM devices, this function is simply an alias for send_string_with_delay(string, interval).
 *
 * \param string The string to type out.
 * \param interval The amount of time, in milliseconds, to wait before typing the next character.
 */
void send_string_with_delay_P(const char *string, uint8_t interval);
#else
#    define send_string_P(string) send_string_with_delay(string, 0)
#    define send_string_with_delay_P(string, interval) send_string_with_delay(string, interval)
#endif

/**
 * \brief Shortcut macro for send_string_with_delay_P(PSTR(string), 0).
 *
 * On ARM devices, this define evaluates to send_string_with_delay(string, 0).
 */
#define SEND_STRING(string) send_string_with_delay_P(PSTR(string), 0)

/**
 * \brief Shortcut macro for send_string_with_delay_P(PSTR(string), interval).
 *
 * On ARM devices, this define evaluates to send_string_with_delay(string, interval).
 */
#define SEND_STRING_DELAY(string, interval) send_string_with_delay_P(PSTR(string), interval)

/** \} */
