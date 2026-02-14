/* Copyright 2017 Joseph Wasson
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

#include "keycodes.h"

// List of keycodes for the plover HID.
enum steno_keycodes {
    PLV__MIN = QK_PLOVER_HID,
    PLV_S1 = PLV__MIN,
    PLV_TL,
    PLV_KL,
    PLV_PL,
    PLV_WL,
    PLV_HL,
    PLV_RL,
    PLV_A,
    PLV_O,
    PLV_ST1,
    PLV_E,
    PLV_U,
    PLV_FR,
    PLV_RR,
    PLV_PR,
    PLV_BR,
    PLV_LR,
    PLV_GR,
    PLV_TR,
    PLV_SR,
    PLV_DR,
    PLV_ZR,
    PLV_N1,
    PLV_S2,
    PLV_ST2,
    PLV_ST3,
    PLV_ST4,
    PLV_N2,
    PLV_N3,
    PLV_N4,
    PLV_N5,
    PLV_N6,
    PLV_N7,
    PLV_N8,
    PLV_N9,
    PLV_NA,
    PLV_NB,
    PLV_NC,
    PLV_X1,
    PLV_X2,
    PLV_X3,
    PLV_X4,
    PLV_X5,
    PLV_X6,
    PLV_X7,
    PLV_X8,
    PLV_X9,
    PLV_X10,
    PLV_X11,
    PLV_X12,
    PLV_X13,
    PLV_X14,
    PLV_X15,
    PLV_X16,
    PLV_X17,
    PLV_X18,
    PLV_X19,
    PLV_X20,
    PLV_X21,
    PLV_X22,
    PLV_X23,
    PLV_X24,
    PLV_X25,
    PLV_X26,
    PLV__MAX = PLV_X26,
};
