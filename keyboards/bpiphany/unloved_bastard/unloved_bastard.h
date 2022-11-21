/* Copyright 2018 Alexander Fougner <fougner89 at gmail.com>
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

#define XXX KC_NO

#define LAYOUT_all( \
    KG6,      KH4, KI4, KI2, KI6, KP5, KL6, KM2, KM4, KO4, KO5, KO6, KO0,   KN5, KN7, KP7, \
    KG4, KG5, KH5, KI5, KJ5, KJ4, KK4, KK5, KL5, KM5, KF5, KF4, KL4, KO2,   KR4, KC4, KE4, \
    KG2, KG7, KH7, KI7, KJ7, KJ2, KK2, KK7, KL7, KM7, KF7, KF2, KL2, KO3,   KQ4, KC5, KE5, \
    KH2, KG3, KH3, KI3, KJ3, KJ6, KK6, KK3, KL3, KM3, KF3, KF6,      KO1, \
    KB2, KH6, KG1, KH1, KI1, KJ1, KJ0, KK0, KK1, KL1, KM1, KF0,      KB3,        KC6, \
    KP4, KN2, KN6,                KQ6,                KN0, KN3, KM0, KP1,   KC0, KQ0, KR0 \
) { \
    { XXX, XXX, KC0, XXX, XXX, KF0, XXX, XXX, XXX, KJ0, KK0, XXX, KM0, KN0, KO0, XXX, KQ0, KR0 }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, KG1, KH1, KI1, KJ1, KK1, KL1, KM1, XXX, KO1, KP1, XXX, XXX }, \
    { XXX, KB2, XXX, XXX, XXX, KF2, KG2, KH2, KI2, KJ2, KK2, KL2, KM2, KN2, KO2, XXX, XXX, XXX }, \
    { XXX, KB3, XXX, XXX, XXX, KF3, KG3, KH3, KI3, KJ3, KK3, KL3, KM3, KN3, KO3, XXX, XXX, XXX }, \
    { XXX, XXX, KC4, XXX, KE4, KF4, KG4, KH4, KI4, KJ4, KK4, KL4, KM4, XXX, KO4, KP4, KQ4, KR4 }, \
    { XXX, XXX, KC5, XXX, KE5, KF5, KG5, KH5, KI5, KJ5, KK5, KL5, KM5, KN5, KO5, KP5, XXX, XXX }, \
    { XXX, XXX, KC6, XXX, XXX, KF6, KG6, KH6, KI6, KJ6, KK6, KL6, XXX, KN6, KO6, XXX, KQ6, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, KF7, KG7, KH7, KI7, KJ7, KK7, KL7, KM7, KN7, XXX, KP7, XXX, XXX } \
}

#define LAYOUT_tkl_ansi( \
    KG6,      KH4, KI4, KI2, KI6, KP5, KL6, KM2, KM4, KO4, KO5, KO6, KO0,   KN5, KN7, KP7, \
    KG4, KG5, KH5, KI5, KJ5, KJ4, KK4, KK5, KL5, KM5, KF5, KF4, KL4, KO2,   KR4, KC4, KE4, \
    KG2, KG7, KH7, KI7, KJ7, KJ2, KK2, KK7, KL7, KM7, KF7, KF2, KL2, KO3,   KQ4, KC5, KE5, \
    KH2, KG3, KH3, KI3, KJ3, KJ6, KK6, KK3, KL3, KM3, KF3, KF6,      KO1, \
    KB2,      KG1, KH1, KI1, KJ1, KJ0, KK0, KK1, KL1, KM1, KF0,      KB3,        KC6, \
    KP4, KN2, KN6,                KQ6,                KN0, KN3, KM0, KP1,   KC0, KQ0, KR0 \
) { \
    { XXX, XXX, KC0, XXX, XXX, KF0, XXX, XXX, XXX, KJ0, KK0, XXX, KM0, KN0, KO0, XXX, KQ0, KR0 }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, KG1, KH1, KI1, KJ1, KK1, KL1, KM1, XXX, KO1, KP1, XXX, XXX }, \
    { XXX, KB2, XXX, XXX, XXX, KF2, KG2, KH2, KI2, KJ2, KK2, KL2, KM2, KN2, KO2, XXX, XXX, XXX }, \
    { XXX, KB3, XXX, XXX, XXX, KF3, KG3, KH3, KI3, KJ3, KK3, KL3, KM3, KN3, KO3, XXX, XXX, XXX }, \
    { XXX, XXX, KC4, XXX, KE4, KF4, KG4, KH4, KI4, KJ4, KK4, KL4, KM4, XXX, KO4, KP4, KQ4, KR4 }, \
    { XXX, XXX, KC5, XXX, KE5, KF5, KG5, KH5, KI5, KJ5, KK5, KL5, KM5, KN5, KO5, KP5, XXX, XXX }, \
    { XXX, XXX, KC6, XXX, XXX, KF6, KG6, XXX, KI6, KJ6, KK6, KL6, XXX, KN6, KO6, XXX, KQ6, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, KF7, KG7, KH7, KI7, KJ7, KK7, KL7, KM7, KN7, XXX, KP7, XXX, XXX } \
}

#define LAYOUT_tkl_iso( \
    KG6,      KH4, KI4, KI2, KI6, KP5, KL6, KM2, KM4, KO4, KO5, KO6, KO0,   KN5, KN7, KP7, \
    KG4, KG5, KH5, KI5, KJ5, KJ4, KK4, KK5, KL5, KM5, KF5, KF4, KL4, KO2,   KR4, KC4, KE4, \
    KG2, KG7, KH7, KI7, KJ7, KJ2, KK2, KK7, KL7, KM7, KF7, KF2, KL2,        KQ4, KC5, KE5, \
    KH2, KG3, KH3, KI3, KJ3, KJ6, KK6, KK3, KL3, KM3, KF3, KF6, KO3, KO1, \
    KB2, KH6, KG1, KH1, KI1, KJ1, KJ0, KK0, KK1, KL1, KM1, KF0,      KB3,        KC6, \
    KP4, KN2, KN6,                KQ6,                KN0, KN3, KM0, KP1,   KC0, KQ0, KR0 \
) { \
    { XXX, XXX, KC0, XXX, XXX, KF0, XXX, XXX, XXX, KJ0, KK0, XXX, KM0, KN0, KO0, XXX, KQ0, KR0 }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, KG1, KH1, KI1, KJ1, KK1, KL1, KM1, XXX, KO1, KP1, XXX, XXX }, \
    { XXX, KB2, XXX, XXX, XXX, KF2, KG2, KH2, KI2, KJ2, KK2, KL2, KM2, KN2, KO2, XXX, XXX, XXX }, \
    { XXX, KB3, XXX, XXX, XXX, KF3, KG3, KH3, KI3, KJ3, KK3, KL3, KM3, KN3, KO3, XXX, XXX, XXX }, \
    { XXX, XXX, KC4, XXX, KE4, KF4, KG4, KH4, KI4, KJ4, KK4, KL4, KM4, XXX, KO4, KP4, KQ4, KR4 }, \
    { XXX, XXX, KC5, XXX, KE5, KF5, KG5, KH5, KI5, KJ5, KK5, KL5, KM5, KN5, KO5, KP5, XXX, XXX }, \
    { XXX, XXX, KC6, XXX, XXX, KF6, KG6, KH6, KI6, KJ6, KK6, KL6, XXX, KN6, KO6, XXX, KQ6, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, KF7, KG7, KH7, KI7, KJ7, KK7, KL7, KM7, KN7, XXX, KP7, XXX, XXX } \
}

#define LAYOUT LAYOUT_all
