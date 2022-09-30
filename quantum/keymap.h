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
#include "keycode_config.h"
#include "gpio.h" // for pin_t

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

// Gross hack, remove me and change RESET keycode to QK_BOOT
#if defined(MCU_RP)
#    undef RESET
#endif

// translates key to keycode
uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key);

extern const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS];

#ifdef ENCODER_MAP_ENABLE
// Ensure we have a forward declaration for the encoder map
#    include "encoder.h"
#endif

#include "keymap_introspection.h"
