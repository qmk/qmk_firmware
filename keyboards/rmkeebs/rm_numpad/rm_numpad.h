/* Copyright 2021 RuckerMachine
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
#define ___ KC_NO

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

/* rm_numpad default layout
 * .-------------------.
 * |PAUS|PREV|NEXT|MUTE|
 * |-------------------|
 * |NLCK|   /|   *|   -|
 * |-------------------|
 * |   7|   8|   9|    |
 * |--------------|    |
 * |   4|   5|   6|   +|
 * |-------------------|
 * |   1|   2|   3|    |
 * |--------------|    |
 * |        0|   .| Ent|
 * '-------------------'
 */

#define LAYOUT_numpad_6x4( \
    k00, k01, k02, k03, \
    k10, k11, k12, k13, \
    k20, k21, k22, \
    k30, k31, k32, k24,\
    k40, k41, k42, \
       k51,   k53, k44 \
) { \
    { k00, k01, k02, k03, ___ }, \
    { k10, k11, k12, k13, ___ }, \
    { k20, k21, k22, ___, k24 }, \
    { k30, k31, k32, ___, ___ }, \
    { k40, k41, k42, ___, k44 }, \
    { ___, k51, ___, k53, ___ } \
}

/* rm_numpad ortho layout
 * .-------------------.
 * |PAUS|PREV|NEXT|MUTE|
 * |-------------------|
 * |NLCK|   /|   *|   -|
 * |-------------------|
 * |   7|   8|   9|   =|
 * |-------------------|
 * |   4|   5|   6|   +|
 * |-------------------|
 * |   1|   2|   3| Ent|
 * |-------------------|
 * |   0|  00|   .| Del|
 * '-------------------'
 */

#define LAYOUT_ortho_6x4( \
    k00, k01, k02, k03, \
    k10, k11, k12, k13, \
    k20, k21, k22, k23, \
    k30, k31, k32, k33, \
    k40, k41, k42, k43, \
    k50, k52, k53, k54 \
) { \
    { k00, k01, k02, k03, ___ }, \
    { k10, k11, k12, k13, ___ }, \
    { k20, k21, k22, k23, ___ }, \
    { k30, k31, k32, k33, ___ }, \
    { k40, k41, k42, k43, ___ }, \
    { k50, ___, k52, k53, k54 } \
}


/* rm_numpad split plus layout
 * .-------------------.
 * |PAUS|PREV|NEXT|MUTE|
 * |-------------------|
 * |NLCK|   /|   *|   -|
 * |-------------------|
 * |   7|   8|   9|   =|
 * |-------------------|
 * |   4|   5|   6|   +|
 * |-------------------|
 * |   1|   2|   3| Ent|
 * |--------------|    |
 * |        0|   .|    |
 * '-------------------'
 */

#define LAYOUT_split_plus_6x4( \
    k00, k01, k02, k03, \
    k10, k11, k12, k13, \
    k20, k21, k22, k23, \
    k30, k31, k32, k33, \
    k40, k41, k42, \
    k51,      k53, k44 \
) { \
    { k00, k01, k02, k03, ___ }, \
    { k10, k11, k12, k13, ___ }, \
    { k20, k21, k22, k23, ___ }, \
    { k30, k31, k32, k33, ___ }, \
    { k40, k41, k42, ___, k44 }, \
    { ___, k51, ___, k53, ___ } \
}

