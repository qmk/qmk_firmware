/* Copyright 2021 dnaq
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

#include <stdint.h>
#include <stdbool.h>

/**
 * \enum plover_hid_button_t
 *
 * An enumeration of the possible Plover HID bit indexes.
 *
 * \note Index order is protocol-mandated and must match plover-machine-hid STENO_KEY_CHART position.
 */
typedef enum {
    PLV_BTN_S1,
    PLV_BTN_TL,
    PLV_BTN_KL,
    PLV_BTN_PL,
    PLV_BTN_WL,
    PLV_BTN_HL,
    PLV_BTN_RL,
    PLV_BTN_A,
    PLV_BTN_O,
    PLV_BTN_ST1,
    PLV_BTN_E,
    PLV_BTN_U,
    PLV_BTN_FR,
    PLV_BTN_RR,
    PLV_BTN_PR,
    PLV_BTN_BR,
    PLV_BTN_LR,
    PLV_BTN_GR,
    PLV_BTN_TR,
    PLV_BTN_SR,
    PLV_BTN_DR,
    PLV_BTN_ZR,
    PLV_BTN_N1,
    PLV_BTN_S2,
    PLV_BTN_ST2,
    PLV_BTN_ST3,
    PLV_BTN_ST4,
    PLV_BTN_N2,
    PLV_BTN_N3,
    PLV_BTN_N4,
    PLV_BTN_N5,
    PLV_BTN_N6,
    PLV_BTN_N7,
    PLV_BTN_N8,
    PLV_BTN_N9,
    PLV_BTN_NA,
    PLV_BTN_NB,
    PLV_BTN_NC,
    PLV_BTN_X1,
    PLV_BTN_X2,
    PLV_BTN_X3,
    PLV_BTN_X4,
    PLV_BTN_X5,
    PLV_BTN_X6,
    PLV_BTN_X7,
    PLV_BTN_X8,
    PLV_BTN_X9,
    PLV_BTN_X10,
    PLV_BTN_X11,
    PLV_BTN_X12,
    PLV_BTN_X13,
    PLV_BTN_X14,
    PLV_BTN_X15,
    PLV_BTN_X16,
    PLV_BTN_X17,
    PLV_BTN_X18,
    PLV_BTN_X19,
    PLV_BTN_X20,
    PLV_BTN_X21,
    PLV_BTN_X22,
    PLV_BTN_X23,
    PLV_BTN_X24,
    PLV_BTN_X25,
    PLV_BTN_X26,
    PLV_BTN_COUNT, // Number of available buttons (always leave at the end)
} plover_hid_button_t;

void plover_hid_update(uint8_t button, bool pressed);
void plover_hid_task(void);
