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

#define _____ KC_NO

#include "quantum.h"
#include "common/remote_kb.h"
#include "common/bitc_led.h"

#ifdef VIA_ENABLE
enum custom_keycodes {
    DISC_MUTE = QK_USER_0,
    SUPER_ALT_TAB
};
#else
enum custom_keycodes {
    DISC_MUTE = SAFE_RANGE,
    SUPER_ALT_TAB
};
#endif

// clang-format off
#define LAYOUT_all( \
       R1C7L, R1C6L, R1C5L, R1C4L, R1C3L, R1C2L, R1C1L,    R1C8R, R1C7R, R1C6R, R1C5R, R1C4R, R1C3R, R1C2R, R1C1R,        \
R2C8L, R2C7L, R2C6L, R2C5L, R2C4L, R2C3L, R2C2L, R2C1L,    R2C8R, R2C7R, R2C6R, R2C5R, R2C4R, R2C3R, R2C2R, R2C1R, R3CXR, \
R3C8L, R3C7L, R3C6L, R3C5L, R3C4L, R3C3L,        R3C1L,    R3C8R, R3C7R, R3C6R, R3C5R, R3C4R, R3C3R, R3C2R, R4C1R, R3C1R, \
R4C8L, R4C7L, R4C6L, R4C5L, R4C4L, R4C3L,        R4C1L,    R4C8R, R4C7R, R4C6R, R4C5R, R4C4R, R4C3R, R4C2R,        R5C1R, \
R5C8L, R5C7L, R5C6L, R5C5L, R5C4L, R5C3L, R5C2L, R5C1L,    R5C8R, R5C7R, R5C6R, R5C5R, R5C4R, R5C3R,        R5C2R, R6C1R, \
R6C8L, R6C7L, R6C6L, R6C5L,        R6C3L,        R6C1L,    R6C8R,               R6C7R, R6C6R, R6C5R, R6C4R, R6C3R, R6C2R  \
) { \
   /* Left */ \
   {_____, R1C7L, R1C6L, R1C5L, R1C4L, R1C3L, R1C2L, R1C1L, _____}, \
   {R2C8L, R2C7L, R2C6L, R2C5L, R2C4L, R2C3L, R2C2L, R2C1L, _____}, \
   {R3C8L, R3C7L, R3C6L, R3C5L, R3C4L, R3C3L, _____, R3C1L, _____}, \
   {R4C8L, R4C7L, R4C6L, R4C5L, R4C4L, R4C3L, _____, R4C1L, _____}, \
   {R5C8L, R5C7L, R5C6L, R5C5L, R5C4L, R5C3L, R5C2L, R5C1L, _____}, \
   {R6C8L, R6C7L, R6C6L, R6C5L, _____, R6C3L, _____, R6C1L, _____}, \
   /* Right */ \
   {R1C8R, R1C7R, R1C6R, R1C5R, R1C4R, R1C3R, R1C2R, R1C1R, _____}, \
   {R2C8R, R2C7R, R2C6R, R2C5R, R2C4R, R2C3R, R2C2R, R2C1R, _____}, \
   {R3C8R, R3C7R, R3C6R, R3C5R, R3C4R, R3C3R, R3C2R, R3C1R, R3CXR}, \
   {R4C8R, R4C7R, R4C6R, R4C5R, R4C4R, R4C3R, R4C2R, R4C1R, _____}, \
   {R5C8R, R5C7R, R5C6R, R5C5R, R5C4R, R5C3R, R5C2R, R5C1R, _____}, \
   {R6C8R, R6C7R, R6C6R, R6C5R, R6C4R, R6C3R, R6C2R, R6C1R, _____}  \
}

#define LAYOUT_iso( \
       R1C7L, R1C6L, R1C5L, R1C4L, R1C3L, R1C2L, R1C1L,    R1C8R, R1C7R, R1C6R, R1C5R, R1C4R, R1C3R, R1C2R, R1C1R,        \
R2C8L, R2C7L, R2C6L, R2C5L, R2C4L, R2C3L, R2C2L, R2C1L,    R2C8R, R2C7R, R2C6R, R2C5R, R2C4R, R2C3R,     R2C2R,    R3CXR, \
R3C8L, R3C7L, R3C6L, R3C5L, R3C4L, R3C3L,        R3C1L,    R3C8R, R3C7R, R3C6R, R3C5R, R3C4R, R3C3R, R3C2R, R4C1R, R3C1R, \
R4C8L, R4C7L, R4C6L, R4C5L, R4C4L, R4C3L,        R4C1L,    R4C8R, R4C7R, R4C6R, R4C5R, R4C4R, R4C3R, R4C2R,        R5C1R, \
R5C8L, R5C7L, R5C6L, R5C5L, R5C4L, R5C3L, R5C2L, R5C1L,    R5C8R, R5C7R, R5C6R, R5C5R, R5C4R, R5C3R,        R5C2R, R6C1R, \
R6C8L, R6C7L, R6C6L, R6C5L,        R6C3L,        R6C1L,    R6C8R,               R6C7R, R6C6R, R6C5R, R6C4R, R6C3R, R6C2R  \
) { /* Left */ \
   {_____, R1C7L, R1C6L, R1C5L, R1C4L, R1C3L, R1C2L, R1C1L, _____}, \
   {R2C8L, R2C7L, R2C6L, R2C5L, R2C4L, R2C3L, R2C2L, R2C1L, _____}, \
   {R3C8L, R3C7L, R3C6L, R3C5L, R3C4L, R3C3L, _____, R3C1L, _____}, \
   {R4C8L, R4C7L, R4C6L, R4C5L, R4C4L, R4C3L, _____, R4C1L, _____}, \
   {R5C8L, R5C7L, R5C6L, R5C5L, R5C4L, R5C3L, R5C2L, R5C1L ,_____}, \
   {R6C8L, R6C7L, R6C6L, R6C5L, _____, R6C3L, _____, R6C1L, _____}, \
   /* Right */ \
   {R1C8R, R1C7R, R1C6R, R1C5R, R1C4R, R1C3R, R1C2R, R1C1R, _____}, \
   {R2C8R, R2C7R, R2C6R, R2C5R, R2C4R, R2C3R, R2C2R, _____, _____}, \
   {R3C8R, R3C7R, R3C6R, R3C5R, R3C4R, R3C3R, R3C2R, R3C1R, R3CXR}, \
   {R4C8R, R4C7R, R4C6R, R4C5R, R4C4R, R4C3R, R4C2R, R4C1R, _____}, \
   {R5C8R, R5C7R, R5C6R, R5C5R, R5C4R, R5C3R, R5C2R, R5C1R, _____}, \
   {R6C8R, R6C7R, R6C6R, R6C5R, R6C4R, R6C3R, R6C2R, R6C1R, _____}  \
}

#define LAYOUT_ansi( \
       R1C7L, R1C6L, R1C5L, R1C4L, R1C3L, R1C2L, R1C1L,    R1C8R, R1C7R, R1C6R, R1C5R, R1C4R, R1C3R, R1C2R, R1C1R,        \
R2C8L, R2C7L, R2C6L, R2C5L, R2C4L, R2C3L, R2C2L, R2C1L,    R2C8R, R2C7R, R2C6R, R2C5R, R2C4R, R2C3R,     R2C2R,    R3CXR, \
R3C8L, R3C7L, R3C6L, R3C5L, R3C4L, R3C3L,        R3C1L,    R3C8R, R3C7R, R3C6R, R3C5R, R3C4R, R3C3R, R3C2R, R4C1R, R3C1R, \
R4C8L, R4C7L, R4C6L, R4C5L, R4C4L, R4C3L,        R4C1L,    R4C8R, R4C7R, R4C6R, R4C5R, R4C4R, R4C3R, R4C2R,        R5C1R, \
R5C8L,     R5C7L,    R5C5L, R5C4L, R5C3L, R5C2L, R5C1L,    R5C8R, R5C7R, R5C6R, R5C5R, R5C4R, R5C3R,        R5C2R, R6C1R, \
R6C8L, R6C7L, R6C6L, R6C5L,        R6C3L,        R6C1L,    R6C8R,               R6C7R, R6C6R, R6C5R, R6C4R, R6C3R, R6C2R  \
) { /* Left */ \
   {_____, R1C7L, R1C6L, R1C5L, R1C4L, R1C3L, R1C2L, R1C1L, _____}, \
   {R2C8L, R2C7L, R2C6L, R2C5L, R2C4L, R2C3L, R2C2L, R2C1L, _____}, \
   {R3C8L, R3C7L, R3C6L, R3C5L, R3C4L, R3C3L, _____, R3C1L, _____}, \
   {R4C8L, R4C7L, R4C6L, R4C5L, R4C4L, R4C3L, _____, R4C1L, _____}, \
   {R5C8L, R5C7L, _____, R5C5L, R5C4L, R5C3L, R5C2L, R5C1L, _____}, \
   {R6C8L, R6C7L, R6C6L, R6C5L, _____, R6C3L, _____, R6C1L, _____}, \
   /* Right */ \
   {R1C8R, R1C7R, R1C6R, R1C5R, R1C4R, R1C3R, R1C2R, R1C1R, _____}, \
   {R2C8R, R2C7R, R2C6R, R2C5R, R2C4R, R2C3R, R2C2R, _____, _____}, \
   {R3C8R, R3C7R, R3C6R, R3C5R, R3C4R, R3C3R, R3C2R, R3C1R, R3CXR}, \
   {R4C8R, R4C7R, R4C6R, R4C5R, R4C4R, R4C3R, R4C2R, R4C1R, _____}, \
   {R5C8R, R5C7R, R5C6R, R5C5R, R5C4R, R5C3R, R5C2R, R5C1R, _____}, \
   {R6C8R, R6C7R, R6C6R, R6C5R, R6C4R, R6C3R, R6C2R, R6C1R, _____}  \
}
// clang-format on
