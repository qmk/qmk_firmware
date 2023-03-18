#pragma once

#include "quantum.h"

#define LAYOUT( \
    LA1, LA2, LA3, LA4, LA5, LA6,           RA6, RA5, RA4, RA3, RA2, RA1, \
    LB1, LB2, LB3, LB4, LB5, LB6,           RB6, RB5, RB4, RB3, RB2, RB1, \
    LC1, LC2, LC3, LC4, LC5, LC6,           RC6, RC5, RC4, RC3, RC2, RC1, \
    LD1, LD2, LD3, LD4, LD5, LD6, LE6, RE6, RD6, RD5, RD4, RD3, RD2, RD1, \
                        LE3, LE4, LE5, RE5, RE4, RE3 \
    ) \
    { \
        { LA1, LA2, LA3, LA4, LA5, LA6 }, \
        { LB1, LB2, LB3, LB4, LB5, LB6 }, \
        { LC1, LC2, LC3, LC4, LC5, LC6 }, \
        { LD1, LD2, LD3, LD4, LD5, LD6 }, \
        { KC_NO, KC_NO, LE3, LE4, LE5, LE6 }, \
        { RA1, RA2, RA3, RA4, RA5, RA6 }, \
        { RB1, RB2, RB3, RB4, RB5, RB6 }, \
        { RC1, RC2, RC3, RC4, RC5, RC6 }, \
        { RD1, RD2, RD3, RD4, RD5, RD6 }, \
        { KC_NO, KC_NO, RE3, RE4, RE5, RE6 } \
    }
