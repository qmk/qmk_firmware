#ifndef REV1_H
#define REV1_H

#include QMK_KEYBOARD_H

//void promicro_bootloader_jmp(bool program);
#include "quantum.h"


#ifdef USE_I2C
#include <stddef.h>
#ifdef __AVR__
    #include <avr/io.h>
    #include <avr/interrupt.h>
#endif
#endif

//void promicro_bootloader_jmp(bool program);

#define KEYMAP( \
    L00, L01, L02, L03, L04, L05,           R00, R01, R02, R03, R04, R05, \
    L10, L11, L12, L13, L14, L15,           R10, R11, R12, R13, R14, R15, \
    L20, L21, L22, L23, L24, L25,           R20, R21, R22, R23, R24, R25, \
    L30, L31, L32, L33, L34, L35, LT4, RT4, R30, R31, R32, R33, R34, R35, \
                        LT1, LT2, LT3, RT3, RT2, RT1 \
    ) \
    { \
        { L00, L01, L02, L03, L04, L05 }, \
        { L10, L11, L12, L13, L14, L15 }, \
        { L20, L21, L22, L23, L24, L25 }, \
        { L30, L31, L32, L33, L34, L35 }, \
        { KC_NO, KC_NO, LT4, LT1, LT2, LT3 }, \
        { R05, R04, R03, R02, R01, R00 }, \
        { R15, R14, R13, R12, R11, R10 }, \
        { R25, R24, R23, R22, R21, R20 }, \
        { R35, R34, R33, R32, R31, R30 }, \
        { KC_NO, KC_NO, RT4, RT1, RT2, RT3 } \
    }

#endif
