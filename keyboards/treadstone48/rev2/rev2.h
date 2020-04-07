/* Copyright 2020 marksard
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

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

// full Keymap
// (TRRS jack on the left half is to the right, TRRS jack on the right half is to the left)
#define LAYOUT_full( \
  L00, L01, L02, L03, L04, L05, L40, L41, L42, L43, L44, L45, \
  L10, L11, L12, L13, L14, L15, L50, L51, L52, L53, L54, L55, \
  L20, L21, L22, L23, L24, L25, L60, L61, L62, L63, L64, L65, \
  L30, L31, L32, L33, L34, L35, L70, L71, L72, L73, L74, L75 \
  ) \
  { \
    { L45, L44, L43, L42, L41, L40 }, \
    { L55, L54, L53, L52, L51, L50 }, \
    { L65, L64, L63, L62, L61, L60 }, \
    { L75, L74, L73, L72, L71, L70 }, \
    { L05, L04, L03, L02, L01, L00 }, \
    { L15, L14, L13, L12, L11, L10 }, \
    { L25, L24, L23, L22, L21, L20 }, \
    { L35, L34, L33, L32, L31, L30 } \
  }

#define K_N KC_NO

//////////////////////////////////////////////////////////////////////////////
// When only use Treadstone48.
// L75 is ExtraKey
//////////////////////////////////////////////////////////////////////////////
#define LAYOUT_base( \
  L00, L01, L02, L03, L04, L05, L40, L41, L42, L43, L44, L45, \
  L10, L11, L12, L13, L14, L15, L50, L51, L52, L53, L54, L55, \
  L20, L21, L22, L23, L24, L25, L60, L61, L62, L63, L64, L65, \
  L30, L31, L32, L33, L34, L35, L70, L71, L72, L73, L74, L75  \
  ) \
  LAYOUT_full( \
    L00, L01, L02, L03, L04, L05, L40, L41, L42, L43, L44, L45, \
    L10, L11, L12, L13, L14, L15, L50, L51, L52, L53, L54, L55, \
    L20, L21, L22, L23, L24, L25, L60, L61, L62, L63, L64, L65, \
    L30, L31, L32, L33, L34, L35, L70, L71, L72, L73, L74, L75  \
  )

// Used to create a keymap using only KC_ prefixed keys
#define LAYOUT_base_kc( \
  L00, L01, L02, L03, L04, L05, L40, L41, L42, L43, L44, L45, \
  L10, L11, L12, L13, L14, L15, L50, L51, L52, L53, L54, L55, \
  L20, L21, L22, L23, L24, L25, L60, L61, L62, L63, L64, L65, \
  L30, L31, L32, L33, L34, L35, L70, L71, L72, L73, L74, L75  \
  ) \
  LAYOUT_base( \
    KC_##L00, KC_##L01, KC_##L02, KC_##L03, KC_##L04, KC_##L05, KC_##L40, KC_##L41, KC_##L42, KC_##L43, KC_##L44, KC_##L45, \
    KC_##L10, KC_##L11, KC_##L12, KC_##L13, KC_##L14, KC_##L15, KC_##L50, KC_##L51, KC_##L52, KC_##L53, KC_##L54, KC_##L55, \
    KC_##L20, KC_##L21, KC_##L22, KC_##L23, KC_##L24, KC_##L25, KC_##L60, KC_##L61, KC_##L62, KC_##L63, KC_##L64, KC_##L65, \
    KC_##L30, KC_##L31, KC_##L32, KC_##L33, KC_##L34, KC_##L35, KC_##L70, KC_##L71, KC_##L72, KC_##L73, KC_##L74, KC_##L75  \
  )
//////////////////////////////////////////////////////////////////////////////
