/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

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

/* FIXME: Add doxygen comments for the behavioral defines in here. */

/* TODO: Refactoring */
typedef enum { ONESHOT, CONSOLE, MOUSEKEY } command_state_t;
extern command_state_t command_state;

/* This allows to extend commands. Return false when command is not processed. */
bool command_extra(uint8_t code);
bool command_console_extra(uint8_t code);

#ifdef COMMAND_ENABLE
uint8_t numkey2num(uint8_t code);
bool    command_proc(uint8_t code);
#else
#    define command_proc(code) false
#endif

#ifndef IS_COMMAND
#    define IS_COMMAND() (get_mods() == MOD_MASK_SHIFT)
#endif

#ifndef MAGIC_KEY_SWITCH_LAYER_WITH_FKEYS
#    define MAGIC_KEY_SWITCH_LAYER_WITH_FKEYS true
#endif

#ifndef MAGIC_KEY_SWITCH_LAYER_WITH_NKEYS
#    define MAGIC_KEY_SWITCH_LAYER_WITH_NKEYS true
#endif

#ifndef MAGIC_KEY_SWITCH_LAYER_WITH_CUSTOM
#    define MAGIC_KEY_SWITCH_LAYER_WITH_CUSTOM false
#endif

#ifndef MAGIC_KEY_HELP
#    define MAGIC_KEY_HELP H
#endif

#ifndef MAGIC_KEY_HELP_ALT
#    define MAGIC_KEY_HELP_ALT SLASH
#endif

#ifndef MAGIC_KEY_DEBUG
#    define MAGIC_KEY_DEBUG D
#endif

#ifndef MAGIC_KEY_DEBUG_MATRIX
#    define MAGIC_KEY_DEBUG_MATRIX X
#endif

#ifndef MAGIC_KEY_DEBUG_KBD
#    define MAGIC_KEY_DEBUG_KBD K
#endif

#ifndef MAGIC_KEY_DEBUG_MOUSE
#    define MAGIC_KEY_DEBUG_MOUSE M
#endif

#ifndef MAGIC_KEY_VERSION
#    define MAGIC_KEY_VERSION V
#endif

#ifndef MAGIC_KEY_STATUS
#    define MAGIC_KEY_STATUS S
#endif

#ifndef MAGIC_KEY_CONSOLE
#    define MAGIC_KEY_CONSOLE C
#endif

#ifndef MAGIC_KEY_LAYER0
#    define MAGIC_KEY_LAYER0 0
#endif

#ifndef MAGIC_KEY_LAYER0_ALT
#    define MAGIC_KEY_LAYER0_ALT GRAVE
#endif

#ifndef MAGIC_KEY_LAYER1
#    define MAGIC_KEY_LAYER1 1
#endif

#ifndef MAGIC_KEY_LAYER2
#    define MAGIC_KEY_LAYER2 2
#endif

#ifndef MAGIC_KEY_LAYER3
#    define MAGIC_KEY_LAYER3 3
#endif

#ifndef MAGIC_KEY_LAYER4
#    define MAGIC_KEY_LAYER4 4
#endif

#ifndef MAGIC_KEY_LAYER5
#    define MAGIC_KEY_LAYER5 5
#endif

#ifndef MAGIC_KEY_LAYER6
#    define MAGIC_KEY_LAYER6 6
#endif

#ifndef MAGIC_KEY_LAYER7
#    define MAGIC_KEY_LAYER7 7
#endif

#ifndef MAGIC_KEY_LAYER8
#    define MAGIC_KEY_LAYER8 8
#endif

#ifndef MAGIC_KEY_LAYER9
#    define MAGIC_KEY_LAYER9 9
#endif

#ifndef MAGIC_KEY_BOOTLOADER
#    define MAGIC_KEY_BOOTLOADER B
#endif

#ifndef MAGIC_KEY_BOOTLOADER_ALT
#    define MAGIC_KEY_BOOTLOADER_ALT ESC
#endif

#ifndef MAGIC_KEY_LOCK
#    define MAGIC_KEY_LOCK CAPS
#endif

#ifndef MAGIC_KEY_EEPROM
#    define MAGIC_KEY_EEPROM E
#endif

#ifndef MAGIC_KEY_EEPROM_CLEAR
#    define MAGIC_KEY_EEPROM_CLEAR BSPACE
#endif

#ifndef MAGIC_KEY_NKRO
#    define MAGIC_KEY_NKRO N
#endif

#ifndef MAGIC_KEY_SLEEP_LED
#    define MAGIC_KEY_SLEEP_LED Z

#endif

#define XMAGIC_KC(key) KC_##key
#define MAGIC_KC(key) XMAGIC_KC(key)
