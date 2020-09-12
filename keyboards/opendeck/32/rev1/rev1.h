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
#define RGB_DISABLE_N_PIN D2
#define RGB_IRQ_N_PIN D3

// If you want something similar to what Taran from LMG does in https://github.com/TaranVH/2nd-keyboard
// you can create a "wrapper key" by uncommenting the row below and chosing your wrapper keycode.
// You can then change the keymap in ../keymaps/default/keymap.c to adjust what key is sent inside the
// wrapper.
// Note: The default is to not wrap and to send F13-F24 with combinations of shift/control/alt as these
// are immediately usable in most software (e.g. OBS and DCSB for streaming) without using AHK.
//#define KC_WRAPPER_KEY KC_F24

#define LAYOUT_32( \
    k00, k01, k02, k03, k04, k05, k06, k07, \
    k08, k09, k0A, k0B, k0C, k0D, k0E, k0F, \
    k10, k11, k12, k13, k14, k15, k16, k17, \
    k18, k19, k1A, k1B, k1C, k1D, k1E, k1F  \
) { \
  {k00, k01, k02, k03, k04, k05, k06, k07 }, \
  {k08, k09, k0A, k0B, k0C, k0D, k0E, k0F }, \
  {k10, k11, k12, k13, k14, k15, k16, k17}, \
  {k18, k19, k1A, k1B, k1C, k1D, k1E, k1F}  \
}

#define KEYMAP LAYOUT_32
#define LAYOUT LAYOUT_32
