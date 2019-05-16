/* Copyright 2018 REPLACE_WITH_YOUR_NAME
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
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#endif

#define K_N KC_NO

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
  L09, L08, L07, L06, L05, L04, L03, L02, L01, L00, \
  L19, L18, L17, L16, L15, L14, L13, L12, L11, L10, \
  L29, L28, L27, L26, L25, L24, L23, L22, L21, L20, \
                      L35, L34 \
  ) \
  { \
    { L00, L01, L02, L03, L04 }, \
    { L10, L11, L12, L13, L14 }, \
    { L20, L21, L22, L23, L24 }, \
    { K_N, K_N, K_N, K_N, L34 }, \
    { L05, L06, L07, L08, L09 }, \
    { L15, L16, L17, L18, L19 }, \
    { L25, L26, L27, L28, L29 }, \
    { L35, K_N, K_N, K_N, K_N }  \
  }

// Used to create a keymap using only KC_ prefixed keys
#define LAYOUT_kc( \
  L00, L01, L02, L03, L04, L05, L06, L07, L08, L09, \
  L10, L11, L12, L13, L14, L15, L16, L17, L18, L19, \
  L20, L21, L22, L23, L24, L25, L26, L27, L28, L29, \
                      L34, L35 \
  ) \
  LAYOUT( \
  KC_##L00, KC_##L01, KC_##L02, KC_##L03, KC_##L04, KC_##L05, KC_##L06, KC_##L07, KC_##L08, KC_##L09, \
  KC_##L10, KC_##L11, KC_##L12, KC_##L13, KC_##L14, KC_##L15, KC_##L16, KC_##L17, KC_##L18, KC_##L19, \
  KC_##L20, KC_##L21, KC_##L22, KC_##L23, KC_##L24, KC_##L25, KC_##L26, KC_##L27, KC_##L28, KC_##L29, \
                                          KC_##L34, KC_##L35 \
  )
