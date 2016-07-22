#ifndef KINESIS_H
#define KINESIS_H

#include "quantum.h"


// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array

#define KEYMAP(                           \
    k02,k22,k12,k01,k21,k11,k00,k20,k10,  \
    k80,k70,k60,k50,k40,k30,              \
    k81,k71,k61,k51,k41,k31,              \
    k82,k72,k62,k52,k42,k32,              \
    k83,k73,k63,k53,k43,k33,              \
        k74,k64,k54,k34,                  \
                        k36,k35,          \
                            k55,          \
                    k56,k46,k75,          \
    k03,k23,k13,k04,k24,k14,k05,k85,k84,  \
        k94,kA4,kB4,kD4,kE4,kF4,          \
        k95,kA5,kB5,kD5,kE5,kF5,          \
        k96,kA6,kB6,kD6,kE6,kF6,          \
        k97,kA7,kB7,kD7,kE7,kF7,          \
            k93,kB3,kD3,kE3,              \
    k47,k66,                              \
    k67,                                  \
    k87,k76,k86                           \
) {                                       \
        { k00,    k01,    k02,    k03,    k04,    k05,    KC_NO,   KC_NO   }, \
        { k10,    k11,    k12,    k13,    k14,    KC_NO,  KC_NO,   KC_NO   }, \
        { k20,    k21,    k22,    k23,    k24,    KC_NO,  KC_NO,   KC_NO   }, \
        { k30,    k31,    k32,    k33,    k34,    k35,    k36,     KC_NO   }, \
        { k40,    k41,    k42,    k43,    KC_NO,  KC_NO,  k46,     k47     }, \
        { k50,    k51,    k52,    k53,    k54,    k55,    k56,     KC_NO   }, \
        { k60,    k61,    k62,    k63,    k64,    KC_NO,  k66,     k67     }, \
        { k70,    k71,    k72,    k73,    k74,    k75,    k76,     KC_NO   }, \
        { k80,    k81,    k82,    k83,    KC_NO  ,KC_NO,  k86,     k87}, \
        { KC_NO,  KC_NO  ,KC_NO  ,k93,    k94,    k95,    k96,     k97}, \
        { KC_NO,  KC_NO  ,KC_NO  ,KC_NO,  kA4,    kA5,    kA6,     kA7}, \
        { KC_NO,  KC_NO  ,KC_NO  ,kB3,    kB4,    kB5,    kB6,     kB7}, \
        { KC_NO,  KC_NO  ,KC_NO  ,KC_NO,  KC_NO,  KC_NO,  k84,     k85}, \
        { KC_NO,  KC_NO  ,KC_NO  ,kD3,    kD4,    kD5,    kD6,     kD7}, \
        { KC_NO,  KC_NO  ,KC_NO  ,kE3,    kE4,    kE5,    kE6,     kE7}, \
        { KC_NO,  KC_NO  ,KC_NO  ,KC_NO,  kF4,    kF5,    kF6,     kF7} \
}


/*    4y0   A  4y1   B  4y2      4y3   D  4y4   E  4y5   F  4y6   G  4y7   H  5y0   I  5y1   J  5y2   K  5y3   L  5y4   M  5y5   N  5y6   O  5y7  P  */

/*
					0	1	2	3	4	5	6	7	8	9	A	B	C	D	E	F
                                        A       B       C       D       E       F       G       H       I       J       K       L       M       N       O       P
                                        4y0     4y1     4y2     4y3     4y4     4y5     4y6     4y7     5y0     5y1     5y2     5y3     5y4     5y5     5y6     5y7
                                        r0      r1      r2       r3 r4  r5      r6      r7      r8      r9      r10     r11     r12     r13     r14     r15
0       PB0             21      c0      f6      f8      f7      5       4       3       2       1       =+
1       PB1             22      c1      f3      f5      f4      t       r       e       w       q       TAB
2       PB2             23      c2      ESC     f2      f1      g       f       d       s       a       CL
3       PB3             24      c3      f9      f11     f10     b       v       c       x       z       LS      UP              DN              [{      ]}
4       PB4             25      c4  f12 SL      PS      RT              LT      §±      `~              6       7       8               9       0       -_
5       PB5             26      c5      PB      PGM     KPD     LA              HM              END             y       u       i               o       p       \
6       PB6             27      c6                      LC      DEL     BS      RC      ENT     SP      h       j       k               l       ;:      '"
7       PB7             28      c7                                      RA              PU              PD      n       m       ,<              .>      /?      RS
*/


#endif
