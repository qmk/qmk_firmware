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

#include "keymap.h"

// List of keycodes for the plover HID.
enum steno_keycodes {
    PLV__MIN = QK_PLOVER_HID,
    PLV_SL = PLV__MIN,
    PLV_TL,
    PLV_KL,
    PLV_PL,
    PLV_WL,
    PLV_HL,
    PLV_RL,
    PLV_A,
    PLV_O,
    PLV_STR,
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
    PLV_NUM,
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
    PLV_X27,
    PLV_X28,
    PLV_X29,
    PLV_X30,
    PLV_X31,
    PLV_X32,
    PLV_X33,
    PLV_X34,
    PLV_X35,
    PLV_X36,
    PLV_X37,
    PLV_X38,
    PLV_X39,
    PLV_X40,
    PLV_X41,
    PLV__MAX = PLV_X41,
};
