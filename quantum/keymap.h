/*
Copyright 2012-2016 Jun Wako <wakojun@gmail.com>

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

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "action.h"
#if defined(__AVR__)
#    include <avr/pgmspace.h>
#elif defined PROTOCOL_CHIBIOS
// We need to ensure that chibios is include before redefining reset
#    include <ch.h>
#endif
#include "keycode.h"
#include "report.h"
#include "host.h"
// #include "print.h"
#include "debug.h"
#include "util.h"
#include "keycode_config.h"

// ChibiOS uses RESET in its FlagStatus enumeration
// Therefore define it as QK_BOOTLOADER here, to avoid name collision
#if defined(PROTOCOL_CHIBIOS)
#    define RESET QK_BOOTLOADER
#endif
// Gross hack, remove me and change RESET keycode to QK_BOOT
#if defined(__AVR_AT90USB647__) || defined(__AVR_AT90USB1287__)
#    undef RESET
#endif

#include "quantum_keycodes.h"

// translates key to keycode
uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key);

extern const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS];

#if defined(ENCODER_ENABLE)
#    ifdef SPLIT_KEYBOARD
#        if defined(ENCODERS_PAD_A_RIGHT)
#            define NUM_ENCODERS_LEFT (sizeof(((pin_t[])ENCODERS_PAD_A)) / sizeof(pin_t))
#            define NUM_ENCODERS_RIGHT (sizeof(((pin_t[])ENCODERS_PAD_A_RIGHT)) / sizeof(pin_t))
#        else
#            define NUM_ENCODERS_LEFT (sizeof(((pin_t[])ENCODERS_PAD_A)) / sizeof(pin_t))
#            define NUM_ENCODERS_RIGHT NUM_ENCODERS_LEFT
#        endif
#        define NUM_ENCODERS (NUM_ENCODERS_LEFT + NUM_ENCODERS_RIGHT)
#    else  // SPLIT_KEYBOARD
#        define NUM_ENCODERS (sizeof(((pin_t[])ENCODERS_PAD_A)) / sizeof(pin_t))
#        define NUM_ENCODERS_LEFT NUM_ENCODERS
#        define NUM_ENCODERS_RIGHT 0
#    endif  // SPLIT_KEYBOARD
#    define NUM_ENCODERS_MAX_PER_SIDE MAX(NUM_ENCODERS_LEFT, NUM_ENCODERS_RIGHT)
#else  // defined(ENCODER_ENABLE)
#    define NUM_ENCODERS 0
#    define NUM_ENCODERS_MAX_PER_SIDE NUM_ENCODERS
#endif  // defined(ENCODER_ENABLE)
