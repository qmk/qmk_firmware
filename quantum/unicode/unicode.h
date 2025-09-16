/* Copyright 2022
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

#pragma once

#include <stdint.h>

#include "compiler_support.h"
#include "unicode_keycodes.h"

/**
 * \file
 *
 * \defgroup unicode Unicode
 * \{
 */

typedef union unicode_config_t {
    uint8_t raw;
    struct {
        uint8_t input_mode : 8;
    };
} unicode_config_t;

STATIC_ASSERT(sizeof(unicode_config_t) == sizeof(uint8_t), "Unicode EECONFIG out of spec.");

extern unicode_config_t unicode_config;

enum unicode_input_modes {
    UNICODE_MODE_MACOS,      // macOS using Unicode Hex Input
    UNICODE_MODE_LINUX,      // Linux using IBus
    UNICODE_MODE_WINDOWS,    // Windows using EnableHexNumpad
    UNICODE_MODE_BSD,        // BSD (not implemented)
    UNICODE_MODE_WINCOMPOSE, // Windows using WinCompose (https://github.com/samhocevar/wincompose)
    UNICODE_MODE_EMACS,      // Emacs is an operating system in search of a good text editor

    UNICODE_MODE_COUNT // Number of available input modes (always leave at the end)
};

void unicode_input_mode_init(void);

/**
 * \brief Get the current Unicode input mode.
 *
 * \return The currently active Unicode input mode.
 */
uint8_t get_unicode_input_mode(void);

/**
 * \brief Set the Unicode input mode.
 *
 * \param mode The input mode to set.
 */
void set_unicode_input_mode(uint8_t mode);

/**
 * \brief Change to the next Unicode input mode.
 */
void unicode_input_mode_step(void);

/**
 * \brief Change to the previous Unicode input mode.
 */
void unicode_input_mode_step_reverse(void);

/**
 * \brief User-level callback, invoked when the input mode is changed.
 *
 * \param input_mode The new input mode.
 */
void unicode_input_mode_set_user(uint8_t input_mode);

/**
 * \brief Keyboard-level callback, invoked when the input mode is changed.
 *
 * \param input_mode The new input mode.
 */
void unicode_input_mode_set_kb(uint8_t input_mode);

/**
 * \brief Begin the Unicode input sequence. The exact behavior depends on the currently selected input mode.
 */
void unicode_input_start(void);

/**
 * \brief Complete the Unicode input sequence. The exact behavior depends on the currently selected input mode.
 */
void unicode_input_finish(void);

/**
 * \brief Cancel the Unicode input sequence. The exact behavior depends on the currently selected input mode.
 */
void unicode_input_cancel(void);

/**
 * \brief Send a 16-bit hex number.
 *
 * \param hex The number to send.
 */
void register_hex(uint16_t hex);

/**
 * \brief Send a 32-bit hex number.
 *
 * \param hex The number to send.
 */
void register_hex32(uint32_t hex);

/**
 * \brief Input a single Unicode character. A surrogate pair will be sent if required by the input mode.
 *
 * \param code_point The code point of the character to send.
 */
void register_unicode(uint32_t code_point);

/**
 * \brief Send a string containing Unicode characters.
 *
 * \param str The string to send.
 */
void send_unicode_string(const char *str);

/** \} */
