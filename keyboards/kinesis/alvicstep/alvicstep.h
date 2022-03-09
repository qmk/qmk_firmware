#pragma once

#include "../kinesis.h"

#define ___ KC_NO

#define LAYOUT( \
    k02, k22, k12, k01, k21, k11, k00, k20, k10, \
    k80, k70, k60, k50, k40, k30, \
    k81, k71, k61, k51, k41, k31, \
    k82, k72, k62, k52, k42, k32, \
    k83, k73, k63, k53, k43, k33, \
         k74, k64, k54, k34, \
                             k36, k35, \
                                  k55, \
                        k56, k46, k75, \
\
    k03, k23, k13, k04, k24, k14, k05, k85, k84, \
                   k94, kA4, kB4, kD4, kE4, kF4, \
                   k95, kA5, kB5, kD5, kE5, kF5, \
                   k96, kA6, kB6, kD6, kE6, kF6, \
                   k97, kA7, kB7, kD7, kE7, kF7, \
                        k93, kB3, kD3, kE3, \
              k47, k66, \
              k67, \
              k87, k76, k86 \
) { \
    { k00, k01, k02, k03, k04, k05, ___, ___ }, \
    { k10, k11, k12, k13, k14, ___, ___, ___ }, \
    { k20, k21, k22, k23, k24, ___, ___, ___ }, \
    { k30, k31, k32, k33, k34, k35, k36, ___ }, \
    { k40, k41, k42, k43, ___, ___, k46, k47 }, \
    { k50, k51, k52, k53, k54, k55, k56, ___ }, \
    { k60, k61, k62, k63, k64, ___, k66, k67 }, \
    { k70, k71, k72, k73, k74, k75, k76, ___ }, \
    { k80, k81, k82, k83, k84, k85, k86, k87 }, \
    { ___, ___, ___, k93, k94, k95, k96, k97 }, \
    { ___, ___, ___, ___, kA4, kA5, kA6, kA7 }, \
    { ___, ___, ___, kB3, kB4, kB5, kB6, kB7 }, \
    { ___, ___, ___, ___, ___, ___, ___, ___ }, \
    { ___, ___, ___, kD3, kD4, kD5, kD6, kD7 }, \
    { ___, ___, ___, kE3, kE4, kE5, kE6, kE7 }, \
    { ___, ___, ___, ___, kF4, kF5, kF6, kF7 } \
}

#define LAYOUT_pretty( \
    k02, k22, k12, k01, k21, k11, k00, k20, k10,   k03, k23, k13, k04, k24, k14, k05, k85, k84, \
    k80, k70, k60, k50, k40, k30,                                 k94, kA4, kB4, kD4, kE4, kF4, \
    k81, k71, k61, k51, k41, k31,                                 k95, kA5, kB5, kD5, kE5, kF5, \
    k82, k72, k62, k52, k42, k32,                                 k96, kA6, kB6, kD6, kE6, kF6, \
    k83, k73, k63, k53, k43, k33,                                 k97, kA7, kB7, kD7, kE7, kF7, \
         k74, k64, k54, k34,                                           k93, kB3, kD3, kE3, \
                             k36, k35,                       k47, k66, \
                                  k55,                       k67, \
                        k56, k46, k75,                       k87, k76, k86 \
) { \
    { k00, k01, k02, k03, k04, k05, ___, ___ }, \
    { k10, k11, k12, k13, k14, ___, ___, ___ }, \
    { k20, k21, k22, k23, k24, ___, ___, ___ }, \
    { k30, k31, k32, k33, k34, k35, k36, ___ }, \
    { k40, k41, k42, k43, ___, ___, k46, k47 }, \
    { k50, k51, k52, k53, k54, k55, k56, ___ }, \
    { k60, k61, k62, k63, k64, ___, k66, k67 }, \
    { k70, k71, k72, k73, k74, k75, k76, ___ }, \
    { k80, k81, k82, k83, k84, k85, k86, k87 }, \
    { ___, ___, ___, k93, k94, k95, k96, k97 }, \
    { ___, ___, ___, ___, kA4, kA5, kA6, kA7 }, \
    { ___, ___, ___, kB3, kB4, kB5, kB6, kB7 }, \
    { ___, ___, ___, ___, ___, ___, ___, ___ }, \
    { ___, ___, ___, kD3, kD4, kD5, kD6, kD7 }, \
    { ___, ___, ___, kE3, kE4, kE5, kE6, kE7 }, \
    { ___, ___, ___, ___, kF4, kF5, kF6, kF7 } \
}

/*
  Row pin configuration

  PF0   A
  PF1   B
  PF2   C
  PF3   G   0 = U4, 1 = U5


  Matrix Map (US QWERTY keyboard layout shown)

              | row 0  | row 1  | row 2  | row 3  | row 4  | row 5  | row 6  | row 7  | row 8  | row 9  | row A  | row B  | row C  | row D  | row E  | row F
        ----------------------------------------------------------------------------------------------------------------------------------------------------
  PB0   col0  | F6     | F8     | F7     | 5%     | 4$     | 3#     | 2@     | 1!     | =+     |        |        |        |        |        |        |
  PB1   col1  | F3     | F5     | F4     | T      | R      | E      | W      | Q      | Tab    |        |        |        |        |        |        |
  PB2   col2  | Esc    | F2     | F1     | G      | F      | D      | S      | A      | CapsLk |        |        |        |        |        |        |
  PB3   col3  | F9     | F11    | F10    | B      | V      | C      | X      | Z      | LShift | Up     |        | Down   |        | [{     | ]}     |
  PB4   col4  | F12    | ScrLk  | PrtSc  | Right  |        | Left   | Insert | `~     | 1!     | 6^     | 7&     | 8*     |        | 9(     | 0)     | -_
  PB5   col5  | Pause  |        |        | LAlt   |        | Home   |        | End    | Fn     | Y      | U      | I      |        | O      | P      | \|
  PB6   col6  |        |        |        | LCtrl  | Delete | Bksp   | RCtrl  | Enter  | Space  | H      | J      | K      |        | L      | ;:     | '"
  PB7   col7  |        |        |        |        | RGUI   |        | PageUp |        | PageDn | N      | M      | ,<     |        | .>     | /?     | RShift
*/
