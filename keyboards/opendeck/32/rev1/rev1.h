/* Copyright 2020 cmdremily
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

#include "quantum.h"

#define POWER_LED_PIN F1

// If you want something similar to what Taran from LMG does in https://github.com/TaranVH/2nd-keyboard
// you can create a "wrapper key" by uncommenting the row below and chosing your wrapper keycode.
// You can then change the keymap in ../keymaps/default/keymap.c to adjust what key is sent inside the
// wrapper.
// Note: The default is to not wrap and to send F13-F24 with combinations of shift/control/alt as these
// are immediately usable in most software (e.g. OBS and DCSB for streaming) without using AHK.
//#define KC_WRAPPER_KEY KC_F24
