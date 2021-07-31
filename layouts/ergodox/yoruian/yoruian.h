/*
 * Copyright 2016 Thomas Fitzsimmons <fitzsim@fitzsim.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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
#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"

#define LAYOUT_ergodox_YORUIAN(                                                        \
 /* Spacial positions. */                                                      \
 k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D,         \
 k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D,         \
 k20, k21, k22, k23, k24, k25,           k28, k29, k2A, k2B, k2C, k2D,         \
 k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D,         \
 k40, k41, k42, k43, k44,                     k49, k4A, k4B, k4C, k4D,         \
                          k55, k56, k57, k58,                                  \
                               k54, k59,                                       \
                     k53, k52, k51, k5C, k5B, k5A)                             \
  LAYOUT_ergodox(KC_##k00, KC_##k01, KC_##k02, KC_##k03, KC_##k04, KC_##k05, KC_##k06, \
         KC_##k10, KC_##k11, KC_##k12, KC_##k13, KC_##k14, KC_##k15, KC_##k16, \
         KC_##k20, KC_##k21, KC_##k22, KC_##k23, KC_##k24, KC_##k25,           \
         KC_##k30, KC_##k31, KC_##k32, KC_##k33, KC_##k34, KC_##k35, KC_##k36, \
         KC_##k40, KC_##k41, KC_##k42, KC_##k43, KC_##k44,                     \
                                                           KC_##k55, KC_##k56, \
                                                                     KC_##k54, \
                                                 KC_##k53, KC_##k52, KC_##k51, \
         KC_##k07, KC_##k08, KC_##k09, KC_##k0A, KC_##k0B, KC_##k0C, KC_##k0D, \
         KC_##k17, KC_##k18, KC_##k19, KC_##k1A, KC_##k1B, KC_##k1C, KC_##k1D, \
                   KC_##k28, KC_##k29, KC_##k2A, KC_##k2B, KC_##k2C, KC_##k2D, \
         KC_##k37, KC_##k38, KC_##k39, KC_##k3A, KC_##k3B, KC_##k3C, KC_##k3D, \
                             KC_##k49, KC_##k4A, KC_##k4B, KC_##k4C, KC_##k4D, \
         KC_##k57, KC_##k58,                                                   \
         KC_##k59,                                                             \
         KC_##k5C, KC_##k5B, KC_##k5A)

#define KC_ES  KC_ESC
#define KC_LC  KC_LCTL
#define KC_RC  KC_RCTL
#define KC_FF  MO(1)
#define KC_IN  KC_INS
#define KC_PS  KC_PSCR
#define KC_TR  KC_TRNS
#define KC_FT  KC_F10
#define KC_FE  KC_F11
#define KC_FW  KC_F12
