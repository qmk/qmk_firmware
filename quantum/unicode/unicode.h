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
#include "unicode_keycodes.h"

typedef union {
    uint8_t raw;
    struct {
        uint8_t input_mode : 8;
    };
} unicode_config_t;

_Static_assert(sizeof(unicode_config_t) == sizeof(uint8_t), "Unicode EECONFIG out of spec.");

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

void    unicode_input_mode_init(void);
uint8_t get_unicode_input_mode(void);
void    set_unicode_input_mode(uint8_t mode);
void    cycle_unicode_input_mode(int8_t offset);
void    persist_unicode_input_mode(void);

void unicode_input_mode_set_user(uint8_t input_mode);
void unicode_input_mode_set_kb(uint8_t input_mode);

void unicode_input_start(void);
void unicode_input_finish(void);
void unicode_input_cancel(void);

void register_hex(uint16_t hex);
void register_hex32(uint32_t hex);
void register_unicode(uint32_t code_point);

void send_unicode_string(const char *str);
