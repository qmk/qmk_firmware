/* Copyright 2020 Ross Montsinger
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

/* This is a shortcut to help you visually see your layout.
 * The first section contains all of the arguments representing the
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

#define LAYOUT_all( \
    KA1, KH1, KA2, KH2, KA3, KH3,      KA5, KH5, KA6, KH6, KA7, KH7
    KB1, KG1, KB2, KG2, KB3, KG3, KB4, KB5, KG5, KB6, KG6, KB7, KG7
    KC1, KF1, KC2, KF2, KC3, KF3, KC4, KC5, KF5, KC6, KF6, KC7, KF7
    KD1, KE1, KD2, KE2, KD3, KE3, KD4, KD5, KE5, KD6, KE6, KD7, KE7
    ) { \
  { KA1, KA2, KA3, KC_NO, KA5, KA6, KA7}, \
  { KB1, KB2, KB3, KB4, KB5, KB6, KB7 }, \
  { KC1, KC2, KC3, KC4, KC5, KC6, KC7 }, \
  { KD1, KD2, KD3, KD4, KD5, KD6, KD7 }, \
  { KE1, KE2, KE3, KE4, KE5, KE6, KE7 }, \
  { KF1, KF2, KF3, KC_NO, KF5, KF6, KF7 }, \
  { KG1, KG2, KG3, KC_NO, KG5, KG6, KG7 }, \
  { KH1, KH2, KH3, KC_NO, KH5, KH6, KH7 } \
}
