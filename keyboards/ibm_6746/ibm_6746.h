/* Copyright 2023 Justin (@Justin-sandwich)
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

//  This is what is printed on each keycap:
//  Mar_Rel  +-        1 2 3 4 5 6 7 8 9 0 - #  Backspace  Paper_Up   
//  Lmar     Tab       Q W E R T Y U I O P ½ [  CRtn       Paper_Down 
//  Rmar     Lock      A S D F G H J K L ; * ⅔             Micro_Up
//  T_Set    LShift >< Z X C V B N M , . /?      RShift    Micro_Down
//  T_Clr              Code  Space               <X        Line_Space (dead)

//  K3N (right shift) is skipped as it is electronically identical to K3B (left shift).
//  K4P (line space) is skipped as it is not found on the keyboard electronically.

#define LAYOUT(	
	       K0A,  K0B,K0C,K0D,K0E,K0F,K0G,K0H,K0I,K0J,K0K,K0L,K0M,K0N,K0O,  K0P, \
	       K1A,  K1B,K1C,K1D,K1E,K1F,K1G,K1H,K1I,K1J,K1K,K1L,K1M,K1N,K1O,  K1P, \
	       K2A,  K2B,K2C,K2D,K2E,K2F,K2G,K2H,K2I,K2J,K2K,K2L,K2M,K2N,      K2P, \
	       K3A,  K3B,K3C,K3D,K3E,K3F,K3G,K3H,K3I,K3J,K3K,K3L,K3M,          K3P, \
	       K4A,          K4D,        K4G,                            K4O        \
) \
{ \
    {KC_NO, K4A,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K2G, K2H, KC_NO, KC_NO, K2M, KC_NO}, \
    {KC_NO, KC_NO, K3A,   KC_NO, K2C,   K2D,   K2E,   K2F, K2I, K2J,   K2K,   K2L, K2P  }, \
    {KC_NO, KC_NO, K0A,   KC_NO, K0B,   KC_NO, KC_NO, K0G, K0H, K0N,   KC_NO, K0M, K0O  }, \
    {KC_NO, KC_NO, KC_NO, KC_NO, K0C,   K0D,   K0E,   K0F, K0I, K0J,   K0K,   K0L, K0P  }, \
    {KC_NO, K1A,   K1B,   KC_NO, K1C,   K1D,   K1E,   K1F, K1I, K1J,   K1K,   K1L, K1P  }, \
    {KC_NO, KC_NO, K2A,   KC_NO, KC_NO, KC_NO, KC_NO, K1G, K1H, K1N,   KC_NO, K1M, KC_NO}, \
    {KC_NO, K3P,   K2B,   KC_NO, K3D,   K3E,   K3F,   K3G, K3J, K3K,   K3L,   K2N, K1O  }, \
    {K4D,   K4G,   K4O,   K3B,   K3C,   KC_NO, KC_NO, K3H, K3I, KC_NO, KC_NO, K3M, KC_NO}, \ 
}