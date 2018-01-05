#ifndef KINESIS_STAPELBERG_H
#define KINESIS_STAPELBERG_H

#include "quantum.h"

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguments as on the physical keyboard
// The second converts the arguments into the 2-D scanned array

#define KEYMAP(                           \
    kC0,kD0,kE0,kC1,kD1,kE1,kC2,kD2,kE2,  \
    k00,k10,k20,k30,k40,k50,              \
    k01,k11,k21,k31,k41,k51,              \
    k02,k12,k22,k32,k42,k52,              \
    k03,k13,k23,k33,k43,k53,              \
        k14,k24,k34,k54,                  \
                        k56,k55,          \
                            k35,          \
                    k36,k46,k25,          \
    kC3,kD3,kE3,kC4,kD4,kE4,kC5,kE5,kD5,  \
        k60,k70,k80,k90,kA0,kB0,          \
        k61,k71,k81,k91,kA1,kB1,          \
        k62,k72,k82,k92,kA2,kB2,          \
        k63,k73,k83,k93,kA3,kB3,          \
            k64,k84,k94,kA4,              \
    k96,k85,                              \
    k86,                                  \
    k66,k75,k65                           \
) {                                       \
        { k00,    k01,    k02,    k03,    KC_NO,  KC_NO,  KC_NO }, \
        { k10,    k11,    k12,    k13,    k14,    KC_NO,  KC_NO }, \
        { k20,    k21,    k22,    k23,    k24,    k25,    KC_NO }, \
        { k30,    k31,    k32,    k33,    k34,    k35,    k36   }, \
        { k40,    k41,    k42,    k43,    KC_NO,  KC_NO,  k46   }, \
        { k50,    k51,    k52,    k53,    k54,    k55,    k56   }, \
        { k60,    k61,    k62,    k63,    k64,    k65,    k66   }, \
        { k70,    k71,    k72,    k73,    KC_NO,  k75,    KC_NO }, \
        { k80,    k81,    k82,    k83,    k84,    k85,    k86   }, \
        { k90,    k91,    k92,    k93,    k94,    KC_NO,  k96   }, \
        { kA0,    kA1,    kA2,    kA3,    kA4,    KC_NO,  KC_NO }, \
        { kB0,    kB1,    kB2,    kB3,    KC_NO,  KC_NO,  KC_NO }, \
        { kC0,    kC1,    kC2,    kC3,    kC4,    kC5,    KC_NO }, \
        { kD0,    kD1,    kD2,    kD3,    kD4,    kD5,    KC_NO }, \
        { kE0,    kE1,    kE2,    kE3,    kE4,    kE5,    KC_NO } \
}

/*
This is the Stapelberg matrix as published at
https://github.com/stapelberg/kinesis-firmware/blob/master/kb_kinesis/config.kspec
Along with the pins for each row and column
             PB0 PB1 PB2 PB3 PB4 PB5 PB6
             kx0 kx1 kx2 kx3 kx4 kx5 kx6
PD0 k0x Row: EQL TAB CAP LSH X2  --  --
PD1 k1x Row: 1   Q   A   Z   BQ  --  --
PD2 k2x Row: 2   W   S   X   INS END --
PD3 k3x Row: 3   E   D   C   LFT HOM BAK
PD4 k4x Row: 4   R   F   V   --  --  DEL
PD5 k5x Row: 5   T   G   B   RT  LAL LCT
PD6 k6x Row: 6   Y   H   N   UP  SPC PGD
PD7 k7x Row: 7   U   J   M   --  RET --
PB0 k8x Row: 8   I   K   COM DWN RCT PGU
PB1 k9x Row: 9   O   L   PER LBR --  RAL
PB2 kAx Row: 0   P   SEM SLA RBR --  --
PB3 kBx Row: MIN BSL APO RSH X1  --  --
PB4 kCx Row: ESC F3  F6  F9  F12 PAU --
PB5 kDx Row: F1  F4  F7  F10 PRT PRG --
PB6 kEx Row: F2  F5  F8  F11 SLK KEY --
*/



#endif
