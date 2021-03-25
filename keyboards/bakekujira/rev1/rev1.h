/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include "bakekujira.h"
#include "split_util.h"

#define XXX KC_NO

#define has_usb() is_keyboard_master()
#define is_master is_keyboard_master()

#define XXX KC_NO

#define LAYOUT_split( \
  L00, L01, L02, L03, L04, L05, L06,      R00, R01, R02, R03, R04, R05,      R07,    R08, R09, R0A, \
  L10,      L12, L13, L14, L15,           R10, R11, R12, R13, R14, R15, R16, R17,    R18, R19, R1A, \
  L20,      L22, L23, L24, L25, L26,      R20, R21, R22, R23, R24, R25, R26,                        \
       L31, L32, L33, L34, L35, L36,      R30, R31, R32, R33, R34,      R36,              R39,      \
  L40, L41, L42, L43,           L46,      R40,           R43, R44,      R46, R47,    R48, R49, R4A  \
) { \
    { L00, L01, L02, L03, L04, L05, L06, XXX,    XXX, XXX, XXX }, \
    { L10, XXX, L12, L13, L14, L15, XXX, XXX,    XXX, XXX, XXX }, \
    { L20, XXX, L22, L23, L24, L25, L26, XXX,    XXX, XXX, XXX }, \
    { XXX, L31, L32, L33, L34, L35, L36, XXX,    XXX, XXX, XXX }, \
    { L40, L41, L42, L43, XXX, XXX, L46, XXX,    XXX, XXX, XXX }, \
    \
    { R00, R01, R02, R03, R04, R05, XXX, R07,    R08, R09, R0A }, \
    { R10, R11, R12, R13, R14, R15, R16, R17,    R18, R19, R1A }, \
    { R20, R21, R22, R23, R24, R25, R26, XXX,    XXX, XXX, XXX }, \
    { R30, R31, R32, R33, R34, XXX, R36, XXX,    XXX, R39, XXX }, \
    { R40, XXX, XXX, R43, R44, XXX, R46, R47,    R48, R49, R4A }  \
}
