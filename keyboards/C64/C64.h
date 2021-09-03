/* Copyright 2021 Dean Woodyatt
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
#define xxx KC_NO

// Enable this for ProMicro built-in LEDS
// #define tx_led B0
// #define rx_led D5

// STANDARD COMMODORE 64 KEYBOARD LAYOUT
//   ,-------------------------------------------------------------------------------.     ,-----.
//   |LEFT|  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |  0 |  + |  - |  £ |HOME| Del|     |  F1 |
//   |-------------------------------------------------------------------------------|     |-----|
//   | CTRL  |  Q |  W |  E |  R |  T |  Y |  U | I |  O |  P |  @ |  * | UP | RESTO |     |  F3 |
//  ,|-------------------------------------------------------------------------------|.    |-----|
//  |RNSTP|SFTLK|  A |  S |  D |  F |  G |  H |  J |  K |  L |  : |  ; |  = |  Enter   |   |  F5 |
//  |----------------------------------------------------------------------------------|   |-----|
//  | COMM|  LSFT |  Z |  X |  C |  V |  B |  N |  M |  , |  . |  / |  RSFT | UD |  LR |   |  F7 |
//  |----------------------------------------------------------------------------------|   `-----'
//  |                |                      SPACE                 |                    |
//  `----------------------------------------------------------------------------------'
// JOYSTICK 1  , UP, DOWN, LEFT, RIGHT, SPACE, Enter
// JOYSTICK 2  , UP, DOWN, LEFT, RIGHT, SPACE, Enter

// REPLACE COLUMN 8 WITH REQUIRED KEYPRESSES, I.E. W A S D ENTER
// REPLACE ROW 8 WITH REQUIRED KEYPRESSES. I.E. Q,A,O,P, SPACE

#define LAYOUT( \
    k10, k00, k70, k01, k71, k02, k72, k03, k73, k04, k74, k05, k75, k06, k76, k07, k47,  \
    k20,   k60, k11, k61, k12, k62, k13, k63, k14, k64, k15, k65, k16, k66,  k88,   k57,  \
    k30,     k21, k51, k22, k52, k23, k53, k24, k54, k25, k55, k26, k56,   k17,     k67,  \
    k50,   k31, k41, k32, k42, k33, k43, k34, k44, k35, k45, k36,   k46, k37, k27,  k77,  \
                                        k40,                                              \
    k80,  k81,  k82,  k83,  k84,  k85,                                                    \
    k08,  k18,  k28,  k38,  k48,  k58                                                     \
    ) \
{ \
    { k00,  k01,   k02,   k03,   k04,   k05,   k06,   k07,   k08   },   \
    { k10,  k11,   k12,   k13,   k14,   k15,   k16,   k17,   k18   },   \
    { k20,  k21,   k22,   k23,   k24,   k25,   k26,   k27,   k28   },   \
    { k30,  k31,   k32,   k33,   k34,   k35,   k36,   k37,   k38   },   \
    { k40,  k41,   k42,   k43,   k44,   k45,   k46,   k47,   k48   },   \
    { k50,  k51,   k52,   k53,   k54,   k55,   k56,   k57,   k58   },   \
    { k60,  k61,   k62,   k63,   k64,   k65,   k66,   k67,   xxx   },   \
    { k70,  k71,   k72,   k73,   k74,   k75,   k76,   k77,   xxx   },   \
    { k80,  k81,   k82,   k83,   k84,   k85,   xxx,   xxx,   k88   }    \
} 


