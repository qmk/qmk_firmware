/* Copyright 2021 Jay Greco
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

#define ___ KC_NO

#include "quantum.h"
#include "common/remote_kb.h"
#include "common/bitc_led.h"

#define LAYOUT( \
                      K01, K02, K03, \
    E1CCW, E1CW, K10, K11, K12, K13, \
    E2CCW, E2CW, K20, K21, K22, K23, \
    E3CCW, E3CW, K30, K31, K32, K33, \
    E4CCW, E4CW, K40, K41, K42, K43  \
) \
{ \
    { ___,   ___,  ___, K01, K02, K03 }, \
    { E1CCW, E1CW, K10, K11, K12, K13 }, \
    { E2CCW, E2CW, K20, K21, K22, K23 }, \
    { E3CCW, E3CW, K30, K31, K32, K33 }, \
    { E4CCW, E4CW, K40, K41, K42, K43 }  \
}
