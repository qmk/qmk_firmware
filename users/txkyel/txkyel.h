/* Copyright 2021 Kyle Xiao
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
#include "tap_dance.h"

#ifdef TAP_DANCE_ENABLE
// Tap Dance declarations for use in keymaps
enum hold_ctl_enum {
    HC_A = 1,
    HC_B,
    HC_C,
    HC_D,
    HC_E,
    HC_F,
    HC_G,
    HC_H,
    HC_I,
    HC_J,
    HC_K,
    HC_L,
    HC_M,
    HC_N,
    HC_O,
    HC_P,
    HC_Q,
    HC_R,
    HC_S,
    HC_T,
    HC_U,
    HC_V,
    HC_W,
    HC_X,
    HC_Y,
    HC_Z,
    HC_BSPC,
    HC_DEL,
    HC_LEFT,
    HC_RGHT,
    TH_ESC_TAB,
    TH_HOME_BSLS,
    TH_END_PIPE,
    TH_QUOT_GRV,
};
#endif
