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

#include "process_plover_hid.h"
#include "plover_hid.h"
#include "progmem.h"
#include "util.h"
#include "compiler_support.h"

#define PLV_INVALID 0xFF

// clang-format off
static const uint8_t key_to_plover_hid[] PROGMEM = {
    PLV_INVALID, // QK_STENO_FUNCTION - Ignore
    PLV_BTN_N1,  // QK_STENO_N1
    PLV_BTN_N2,  // QK_STENO_N2
    PLV_BTN_N3,  // QK_STENO_N3
    PLV_BTN_N4,  // QK_STENO_N4
    PLV_BTN_N5,  // QK_STENO_N5
    PLV_BTN_N6,  // QK_STENO_N6
    PLV_BTN_S1,  // QK_STENO_S1
    PLV_BTN_S2,  // QK_STENO_S2
    PLV_BTN_TL,  // QK_STENO_TL
    PLV_BTN_KL,  // QK_STENO_KL
    PLV_BTN_PL,  // QK_STENO_PL
    PLV_BTN_WL,  // QK_STENO_WL
    PLV_BTN_HL,  // QK_STENO_HL
    PLV_BTN_RL,  // QK_STENO_RL
    PLV_BTN_A,   // QK_STENO_A
    PLV_BTN_O,   // QK_STENO_O
    PLV_BTN_ST1, // QK_STENO_ST1
    PLV_BTN_ST2, // QK_STENO_ST2
    PLV_INVALID, // QK_STENO_RESET1 - Ignore
    PLV_INVALID, // QK_STENO_RESET2 - Ignore
    PLV_INVALID, // QK_STENO_POWER - Ignore
    PLV_BTN_ST3, // QK_STENO_ST3
    PLV_BTN_ST4, // QK_STENO_ST4
    PLV_BTN_E,   // QK_STENO_E
    PLV_BTN_U,   // QK_STENO_U
    PLV_BTN_FR,  // QK_STENO_FR
    PLV_BTN_RR,  // QK_STENO_RR
    PLV_BTN_PR,  // QK_STENO_PR
    PLV_BTN_BR,  // QK_STENO_BR
    PLV_BTN_LR,  // QK_STENO_LR
    PLV_BTN_GR,  // QK_STENO_GR
    PLV_BTN_TR,  // QK_STENO_TR
    PLV_BTN_SR,  // QK_STENO_SR
    PLV_BTN_DR,  // QK_STENO_DR
    PLV_BTN_N7,  // QK_STENO_N7
    PLV_BTN_N8,  // QK_STENO_N8
    PLV_BTN_N9,  // QK_STENO_N9
    PLV_BTN_NA,  // QK_STENO_NA
    PLV_BTN_NB,  // QK_STENO_NB
    PLV_BTN_NC,  // QK_STENO_NC
    PLV_BTN_ZR,  // QK_STENO_ZR
    PLV_BTN_X1,  // QK_STENO_X1
    PLV_BTN_X2,  // QK_STENO_X2
    PLV_BTN_X3,  // QK_STENO_X3
    PLV_BTN_X4,  // QK_STENO_X4
    PLV_BTN_X5,  // QK_STENO_X5
    PLV_BTN_X6,  // QK_STENO_X6
    PLV_BTN_X7,  // QK_STENO_X7
    PLV_BTN_X8,  // QK_STENO_X8
    PLV_BTN_X9,  // QK_STENO_X9
    PLV_BTN_X10, // QK_STENO_X10
    PLV_BTN_X11, // QK_STENO_X11
    PLV_BTN_X12, // QK_STENO_X12
    PLV_BTN_X13, // QK_STENO_X13
    PLV_BTN_X14, // QK_STENO_X14
    PLV_BTN_X15, // QK_STENO_X15
    PLV_BTN_X16, // QK_STENO_X16
    PLV_BTN_X17, // QK_STENO_X17
    PLV_BTN_X18, // QK_STENO_X18
    PLV_BTN_X19, // QK_STENO_X19
    PLV_BTN_X20, // QK_STENO_X20
    PLV_BTN_X21, // QK_STENO_X21
    PLV_BTN_X22, // QK_STENO_X22
    PLV_BTN_X23, // QK_STENO_X23
    PLV_BTN_X24, // QK_STENO_X24
    PLV_BTN_X25, // QK_STENO_X25
    PLV_BTN_X26, // QK_STENO_X26
};
// clang-format on

STATIC_ASSERT(ARRAY_SIZE(key_to_plover_hid) == (QK_STENO_X26 - QK_STENO + 1), "key_to_plover_hid array size must match number of steno keys");

bool process_plover_hid(uint16_t keycode, keyrecord_t *record) {
    if (keycode < QK_STENO_FUNCTION || keycode > QK_STENO_X26) {
        return true;
    }

    uint8_t button = pgm_read_byte(&key_to_plover_hid[keycode - QK_STENO]);
    if (button == PLV_INVALID) {
        return true;
    }

    plover_hid_update(button, record->event.pressed);
    return false;
}
