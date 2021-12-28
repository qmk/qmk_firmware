/* Copyright 2016 Matthias Schmitt
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

// clang-format off

/*
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ^ │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ ` │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ X │ V │ L │ C │ W │ K │ H │ G │ F │ Q │ ß │ ´ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │  L3  │ U │ I │ A │ E │ O │ S │ N │ R │ T │ D │ Y │ L3│    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │L4 │ Ü │ Ö │ Ä │ P │ Z │ B │ M │ , │ . │ J │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │ L4 │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define NE_CIRC KC_GRV  // ^ (dead)
#define NE_1    KC_1    // 1
#define NE_2    KC_2    // 2
#define NE_3    KC_3    // 3
#define NE_4    KC_4    // 4
#define NE_5    KC_5    // 5
#define NE_6    KC_6    // 6
#define NE_7    KC_7    // 7
#define NE_8    KC_8    // 8
#define NE_9    KC_9    // 9
#define NE_0    KC_0    // 0
#define NE_MINS KC_MINS // -
#define NE_GRV  KC_EQL  // ` (dead)
// Row 2
#define NE_X    KC_Q    // X
#define NE_V    KC_W    // V
#define NE_L    KC_E    // L
#define NE_C    KC_R    // C
#define NE_W    KC_T    // W
#define NE_K    KC_Y    // K
#define NE_H    KC_U    // H
#define NE_G    KC_I    // G
#define NE_F    KC_O    // F
#define NE_Q    KC_P    // Q
#define NE_SS   KC_LBRC // ß
#define NE_ACUT KC_RBRC // ´ (dead)
// Row 3
#define NE_L3L  KC_CAPS // (layer 3)
#define NE_U    KC_A    // U
#define NE_I    KC_S    // I
#define NE_A    KC_D    // A
#define NE_E    KC_F    // E
#define NE_O    KC_G    // O
#define NE_S    KC_H    // S
#define NE_N    KC_J    // N
#define NE_R    KC_K    // R
#define NE_T    KC_L    // T
#define NE_D    KC_SCLN // D
#define NE_Y    KC_QUOT // Y
#define NE_L3R  KC_NUHS // (layer 3)
// Row 4
#define NE_L4L  KC_NUBS // (layer 4)
#define NE_UDIA KC_Z    // Ü
#define NE_ODIA KC_X    // Ö
#define NE_ADIA KC_C    // Ä
#define NE_P    KC_V    // P
#define NE_Z    KC_B    // Z
#define NE_B    KC_N    // B
#define NE_M    KC_M    // M
#define NE_COMM KC_COMM // ,
#define NE_DOT  KC_DOT  // .
#define NE_J    KC_SLSH // J
// Row 5
#define NE_L4R  KC_ALGR // (layer 4)
