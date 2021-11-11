/* Copyright 2021 Cutie Club
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

/* ==== MODS ==== */
// BACKSPACE
#define BACKSPACE k00_14
#define BACKSPACE_MATRIX KC_NO, k00_14

// SPLIT BACKSPACE
#define SPLIT_BACKSPACE k00_13, k00_14
#define SPLIT_BACKSPACE_MATRIX SPLIT_BACKSPACE

// CAPS
#define CAPS k02_00
#define CAPS_MATRIX CAPS

// ESC
#define ESC k00_00
#define ESC_MATRIX ESC

// TAB
#define TAB k01_00
#define TAB_MATRIX TAB

// ENTER
#define ISO_ENTER k02_12, k02_13
#define ISO_ENTER_MATRIX k02_12, k02_13, KC_NO
#define ANSI_ENTER k02_13
#define ANSI_ENTER_MATRIX KC_NO, k02_13, KC_NO

// LSHIFT
#define LSHIFT k03_00
#define LSHIFT_MATRIX k03_00, KC_NO

#define SPLIT_LSHIFT k03_00, k03_01
#define SPLIT_LSHIFT_MATRIX SPLIT_LSHIFT

// RSHIFT
#define RSHIFT k03_12
#define RSHIFT_MATRIX k03_12, KC_NO, KC_NO

#define SPLIT_RSHIFT k03_12, k03_13
#define SPLIT_RSHIFT_MATRIX k03_12, k03_13, KC_NO

// LEFT CTRL CLUSTER
#define LEFT_CTRL_CLUSTER k04_00, k04_01, k04_02
#define LEFT_CTRL_CLUSTER_MATRIX k04_00, k04_01, k04_02

#define LEFT_CTRL_CLUSTER_HHKB k04_01, k04_02
#define LEFT_CTRL_CLUSTER_HHKB_MATRIX KC_NO, k04_01, k04_02

// RIGHT CTRL CLUSTER
#define RIGHT_CTRL_CLUSTER k04_10, k04_11, k04_12, k04_13
#define RIGHT_CTRL_CLUSTER_MATRIX k04_10, k04_11, k04_12, k04_13, KC_NO

#define RIGHT_CTRL_CLUSTER_TSANGAN k04_11, k04_12, k04_13
#define RIGHT_CTRL_CLUSTER_TSANGAN_MATRIX KC_NO, k04_11, k04_12, k04_13, KC_NO

#define RIGHT_CTRL_CLUSTER_HHKB k04_11, k04_12
#define RIGHT_CTRL_CLUSTER_HHKB_MATRIX KC_NO, k04_11, k04_12, KC_NO, KC_NO

// SPACE
#define SPACE k04_06
#define SPACE_MATRIX KC_NO, KC_NO, KC_NO, k04_06, KC_NO, KC_NO, KC_NO

#define SPLIT_SPACE k04_04, k04_06, k04_08
#define SPLIT_SPACE_MATRIX KC_NO, k04_04, KC_NO, k04_06, KC_NO, k04_08, KC_NO

/* ==== ALPHAS ==== */
#define ALPHAS_R0 k00_01, k00_02, k00_03, k00_04, k00_05, k00_06, k00_07, k00_08, k00_09, k00_10, k00_11, k00_12
#define ALPHAS_R0_MATRIX ALPHAS_R0

#define ALPHAS_R1_ANSI k01_01, k01_02, k01_03, k01_04, k01_05, k01_06, k01_07, k01_08, k01_09, k01_10, k01_11, k01_12, k01_13
#define ALPHAS_R1_ANSI_MATRIX ALPHAS_R1_ANSI, KC_NO

#define ALPHAS_R1_ISO k01_01, k01_02, k01_03, k01_04, k01_05, k01_06, k01_07, k01_08, k01_09, k01_10, k01_11, k01_12
#define ALPHAS_R1_ISO_MATRIX ALPHAS_R1_ISO, KC_NO, KC_NO

#define ALPHAS_R2 k02_01, k02_02, k02_03, k02_04, k02_05, k02_06, k02_07, k02_08, k02_09, k02_10, k02_11
#define ALPHAS_R2_MATRIX ALPHAS_R2

#define ALPHAS_R3 k03_02, k03_03, k03_04, k03_05, k03_06, k03_07, k03_08, k03_09, k03_10, k03_11
#define ALPHAS_R3_MATRIX ALPHAS_R3
