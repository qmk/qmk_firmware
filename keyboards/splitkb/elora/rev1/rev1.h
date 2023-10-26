/* Copyright 2023 splitkb.com <support@splitkb.com>
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

#include "elora.h"

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

// KC_NOs are used for encoders:
// Pin  A   B   C   D   E   F   G   H
// Left:
//   { __, __, __, __, __, __, A1, B1 },
//   { A3, B3, A2, B2, __, __, __, __ }
// Right:
//   { A1, B1, __, __, __, __, __, __ },
//   { __, __, __, __, A2, B2, A3, B3 }

#define LAYOUT( \
    MX101, MX105, MX109, MX113, MX117, MX121,        LPED1, RPED1,        MX221, MX217, MX213, MX209, MX205, MX201, \
    MX102, MX106, MX110, MX114, MX118, MX122,        LPED2, RPED2,        MX222, MX218, MX214, MX210, MX206, MX202, \
    MX103, MX107, MX111, MX115, MX119, MX123,        LPED3, RPED3,        MX223, MX219, MX215, MX211, MX207, MX203, \
    MX104, MX108, MX112, MX116, MX120, MX124, MX131, MX130, MX230, MX231, MX224, MX220, MX216, MX212, MX208, MX204, \
                         MX125, MX126, MX127, MX128, MX129, MX229, MX228, MX227, MX226, MX225                       \
) \
{ \
    { MX131, LPED1, LPED2, LPED3, MX130, MX129, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, MX128, MX127, MX126, MX125 }, \
    { MX118, MX117, MX121, MX122, MX123, MX124, MX120, MX119 }, \
    { MX110, MX109, MX113, MX114, MX115, MX116, MX112, MX111 }, \
    { MX102, MX101, MX105, MX106, MX107, MX108, MX104, MX103 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
                                                                \
    { KC_NO, KC_NO, MX229, MX230, RPED3, RPED2, RPED1, MX231 }, \
    { MX225, MX226, MX227, MX228, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { MX219, MX220, MX224, MX223, MX222, MX221, MX217, MX218 }, \
    { MX211, MX212, MX216, MX215, MX214, MX213, MX209, MX210 }, \
    { MX203, MX204, MX208, MX207, MX206, MX205, MX201, MX202 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
} //    A      B      C      D      E      F      G      H

#define LAYOUT_myr( \
    MX101, MX105, MX109, MX113, MX117, MX121,        LPED1, RPED1,        MX221, MX217, MX213, MX209, MX205, MX201, \
    MX102, MX106, MX110, MX114, MX118, MX122,        LPED2, RPED2,        MX222, MX218, MX214, MX210, MX206, MX202, \
    MX103, MX107, MX111, MX115, MX119, MX123,        LPED3, RPED3,        MX223, MX219, MX215, MX211, MX207, MX203, \
    MX104, MX108, MX112, MX116, MX120, MX124, MX131, MX130, MX230, MX231, MX224, MX220, MX216, MX212, MX208, MX204, \
                         MX125, MX126, MX127, MX128, MX129, MX229, MX228, MX227, MX226, MX225,                      \
    MYRL1, MYRL2, MYRL3, MYRL4,        MYRL5,               MYRR1, MYRR2, MYRR3, MYRR4,        MYRR5                \
) \
{ \
    { MX131, LPED1, LPED2, LPED3, MX130, MX129, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, MX128, MX127, MX126, MX125 }, \
    { MX118, MX117, MX121, MX122, MX123, MX124, MX120, MX119 }, \
    { MX110, MX109, MX113, MX114, MX115, MX116, MX112, MX111 }, \
    { MX102, MX101, MX105, MX106, MX107, MX108, MX104, MX103 }, \
    { MYRL1, MYRL2, MYRL3, MYRL4, MYRL5, KC_NO, KC_NO, KC_NO }, \
                                                                \
    { KC_NO, KC_NO, MX229, MX230, RPED3, RPED2, RPED1, MX231 }, \
    { MX225, MX226, MX227, MX228, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { MX219, MX220, MX224, MX223, MX222, MX221, MX217, MX218 }, \
    { MX211, MX212, MX216, MX215, MX214, MX213, MX209, MX210 }, \
    { MX203, MX204, MX208, MX207, MX206, MX205, MX201, MX202 }, \
    { MYRR1, MYRR2, MYRR3, MYRR4, MYRR5, KC_NO, KC_NO, KC_NO }, \
} //    A      B      C      D      E      F      G      H


//// Custom pins, might be useful in a keymap
// Wired to input of last shift register, overrides 10k pullup/pulldown
#define ELORA_SELFTEST_PIN GP14

// Can be used for USB current detection
#define ELORA_CC1_PIN      GP28
#define ELORA_CC2_PIN      GP29
