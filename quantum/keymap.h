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
#include "platform_deps.h"
#include "action.h"
#include "keycode.h"
#include "report.h"
#include "host.h"
#include "debug.h"
#include "keycode_config.h"
#include "gpio.h" // for pin_t

#include "quantum_keycodes.h"

// translates key to keycode
uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key);

#ifdef ENCODER_MAP_ENABLE
// Ensure we have a forward declaration for the encoder map
#    include "encoder.h"
#endif

#include "keymap_introspection.h"
