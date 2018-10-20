/*
  Copyright 2018 Yann Hodique <yann.hodique@gmail.com> @sigma

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

#include "quantum.h"
#include "version.h"
#include "eeprom.h"

// Define os types
enum os_types
  {
   _OS_MACOS = 0,
   _OS_LINUX,
   _OS_WINDOWS,
  };

// Define layer names
enum userspace_layers
  {
   _QWERTY = 0,
  };

typedef union {
  uint32_t raw;
  struct {
    uint8_t os_target :2;
  };
} userspace_config_t;

enum userspace_custom_keycodes
  {
   EPRM = SAFE_RANGE, // Resets EEPROM
   VRSN,              // Prints QMK Firmware and board info
   KC_QWERTY,         // Sets default layer to QWERTY
   KC_MAKE,           // Rebuild the current firmware
   KC_OS_CUT,
   KC_OS_COPY,
   KC_OS_PASTE,
   KC_OS_UNDO,
   KC_OS_REDO,
   KC_OS_LOCK,
   KC_SCRT,
   NEW_SAFE_RANGE     //use NEW_SAFE_RANGE for keymap specific codes
  };
