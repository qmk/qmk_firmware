/* Copyright 2024 @ Keychron (https://www.keychron.com)
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
#include "game_controller_common.h"
// bit 0~1: basic mode
// bit 2~4: adv mode
// bit 5~15: axis

// a-advance mode, b-mode
#define JSM(a, m) ((a << 3 | AKM_GAMEPAD) << 2) | (m & 3)
#define TGM(m) (AKM_TOGGLE << 2) | (m & 3)

#define AX(x) JSM(x, 0)
#define BTN(x) JSM((x + GC_BUTTON_0), 0)
/* Xbox mapping
 BTN(0) - A
 BTN(1) - B
 BTN(2) - X
 BTN(3) - Y
 BTN(4) - LB
 BTN(5) - RB
 BTN(6) - View
 BTN(7) - Menu
 BTN(8) - L3
 BTN(9) - R3
 BTN(10) - Up
 BTN(11) - Down
 BTN(12) - Left
 BTN(13) - Right
 BTN(14) - Xbox
 */

/* Xinput buttons */
#define XB_A BTN(0)
#define XB_B BTN(1)
#define XB_X BTN(2)
#define XB_Y BTN(3)
#define XB_LB BTN(4)
#define XB_RB BTN(5)
#define XB_VIEW BTN(6)
#define XB_MEMU BTN(7)
#define XB_L3 BTN(8)
#define XB_R3 BTN(9)
#define XB_UP BTN(10)
#define XB_DOWN BTN(11)
#define XB_LEFT BTN(12)
#define XB_RGHT BTN(13)
#define XB_XBOX BTN(14)
#define XB_LT AX(4)
#define XB_RT AX(5)
/* Left Stick */
#define LS_LEFT AX(0)
#define LS_RGHT AX(1)
#define LS_UP AX(3)
#define LS_DOWN AX(2)
/* Right Stick */
#define RS_LEFT AX(6)
#define RS_RGHT AX(7)
#define RS_UP AX(9)
#define RS_DOWN AX(8)
