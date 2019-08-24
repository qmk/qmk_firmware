#pragma once

#include "quantum.h"

#ifdef KEYBOARD_keebio_quefrency_rev1
    #include "rev1.h"
#endif

// Used to create a keymap using only KC_ prefixed keys
#define LAYOUT_kc( \
    LA1, LA2, LA3, LA4, LA5, LA6, RA1, RA2, RA3, RA4, RA5, RA6, RA7, \
    LB1, LB2, LB3, LB4, LB5, LB6, RB1, RB2, RB3, RB4, RB5,      RB7, \
    LC1, LC2, LC3, LC4, LC5, LC6, RC1,      RC3, RC4, RC5, RC6, RC7, \
    LD1, LD2, LD3, LD4, LD5,      RD1,      RD4, RD5, RD6, RD7 \
    ) \
    LAYOUT( \
        KC_##LA1, KC_##LA2, KC_##LA3, KC_##LA4, KC_##LA5, KC_##LA6, KC_##RA1, KC_##RA2, KC_##RA3, KC_##RA4, KC_##RA5, KC_##RA6, KC_##RA7, \
        KC_##LB1, KC_##LB2, KC_##LB3, KC_##LB4, KC_##LB5, KC_##LB6, KC_##RB1, KC_##RB2, KC_##RB3, KC_##RB4, KC_##RB5,           KC_##RB7, \
        KC_##LC1, KC_##LC2, KC_##LC3, KC_##LC4, KC_##LC5, KC_##LC6, KC_##RC1,           KC_##RC3, KC_##RC4, KC_##RC5, KC_##RC6, KC_##RC7, \
        KC_##LD1, KC_##LD2, KC_##LD3, KC_##LD4, KC_##LD5,           KC_##RD1,                     KC_##RD4, KC_##RD5, KC_##RD6, KC_##RD7 \
        )

#define LAYOUT_65_kc(                                                   \
    LA1, LA2, LA3, LA4, LA5, LA6, LA7, RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, RA9, \
    LB1, LB2, LB3, LB4, LB5, LB6,      RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8, RB9, \
    LC1, LC2, LC3, LC4, LC5, LC6,      RC1, RC2, RC3, RC4, RC5, RC6,      RC8, RC9, \
    LD1,      LD3, LD4, LD5, LD6, LD7, RD1, RD2, RD3, RD4,      RD6, RD7, RD8, RD9, \
    LE1, LE2, LE3,      LE5,      LE7, RE1, RE2,      RE4, RE5, RE6, RE7, RE8, RE9 \
    ) \
    { \
        { KC_##LA1, KC_##LA2, KC_##LA3, KC_##LA4, KC_##LA5, KC_##LA6, KC_##LA7, KC_NO }, \
        { KC_##LB1, KC_##LB2, KC_##LB3, KC_##LB4, KC_##LB5, KC_##LB6, KC_NO, KC_NO }, \
        { KC_##LC1, KC_##LC2, KC_##LC3, KC_##LC4, KC_##LC5, KC_##LC6, KC_NO, KC_NO }, \
        { KC_##LD1, KC_NO, KC_##LD3, KC_##LD4, KC_##LD5, KC_##LD6, KC_##LD7, KC_NO }, \
        { KC_##LE1, KC_##LE2, KC_##LE3, KC_NO, KC_##LE5, KC_NO, KC_##LE7, KC_NO }, \
        { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
        { KC_##RA1, KC_##RA2, KC_##RA3, KC_##RA4, KC_##RA5, KC_##RA6, KC_##RA7, KC_##RA8 }, \
        { KC_##RB1, KC_##RB2, KC_##RB3, KC_##RB4, KC_##RB5, KC_##RB6, KC_##RB7, KC_##RB8 }, \
        { KC_##RC1, KC_##RC2, KC_##RC3, KC_##RC4, KC_##RC5, KC_##RC6, KC_##RC9, KC_##RC8 }, \
        { KC_##RD1, KC_##RD2, KC_##RD3, KC_##RD4, KC_##RD9, KC_##RD6, KC_##RD7, KC_##RD8 }, \
        { KC_##RE1, KC_##RE2, KC_##RE9, KC_##RE4, KC_##RE5, KC_##RE6, KC_##RE7, KC_##RE8 }, \
        { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_##RA9, KC_##RB9 } \
    }

#define LAYOUT_60_with_macro_kc(                                        \
    LA9, LA8, LA1, LA2, LA3, LA4, LA5, LA6, LA7, RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, \
    LB9, LB8, LB1, LB2, LB3, LB4, LB5, LB6,      RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8, \
    LC9, LC8, LC1, LC2, LC3, LC4, LC5, LC6,      RC1, RC2, RC3, RC4, RC5, RC6,      RC8, \
    LD9, LD8, LD1,      LD3, LD4, LD5, LD6, LD7, RD1, RD2, RD3, RD4,      RD6, RD7, RD8, \
    LE9, LE8, LE1, LE2, LE3,      LE5,      LE7, RE1, RE2,      RE4, RE5, RE6, RE7, RE8 \
    ) \
    { \
        { KC_##LA1, KC_##LA2, KC_##LA3, KC_##LA4, KC_##LA5, KC_##LA6, KC_##LA7, KC_##LA8 }, \
        { KC_##LB1, KC_##LB2, KC_##LB3, KC_##LB4, KC_##LB5, KC_##LB6, KC_##LB9, KC_##LB8 }, \
        { KC_##LC1, KC_##LC2, KC_##LC3, KC_##LC4, KC_##LC5, KC_##LC6, KC_##LC9, KC_##LC8 }, \
        { KC_##LD1, KC_##LD9, KC_##LD3, KC_##LD4, KC_##LD5, KC_##LD6, KC_##LD7, KC_##LD8 }, \
        { KC_##LE1, KC_##LE2, KC_##LE3, KC_##LA9, KC_##LE5, KC_##LE9, KC_##LE7, KC_##LE8 }, \
        { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
        { KC_##RA1, KC_##RA2, KC_##RA3, KC_##RA4, KC_##RA5, KC_##RA6, KC_##RA7, KC_##RA8 }, \
        { KC_##RB1, KC_##RB2, KC_##RB3, KC_##RB4, KC_##RB5, KC_##RB6, KC_##RB7, KC_##RB8 }, \
        { KC_##RC1, KC_##RC2, KC_##RC3, KC_##RC4, KC_##RC5, KC_##RC6, KC_NO, KC_##RC8 }, \
        { KC_##RD1, KC_##RD2, KC_##RD3, KC_##RD4, KC_NO, KC_##RD6, KC_##RD7, KC_##RD8 }, \
        { KC_##RE1, KC_##RE2, KC_NO, KC_##RE4, KC_##RE5, KC_##RE6, KC_##RE7, KC_##RE8 }, \
        { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO } \
    }

#define LAYOUT_65_with_macro_kc(                                        \
    LA9, LA8, LA1, LA2, LA3, LA4, LA5, LA6, LA7, RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, RA9, \
    LB9, LB8, LB1, LB2, LB3, LB4, LB5, LB6,      RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8, RB9, \
    LC9, LC8, LC1, LC2, LC3, LC4, LC5, LC6,      RC1, RC2, RC3, RC4, RC5, RC6,      RC8, RC9, \
    LD9, LD8, LD1,      LD3, LD4, LD5, LD6, LD7, RD1, RD2, RD3, RD4,      RD6, RD7, RD8, RD9, \
    LE9, LE8, LE1, LE2, LE3,      LE5,      LE7, RE1, RE2,      RE4, RE5, RE6, RE7, RE8, RE9 \
    ) \
    { \
        { KC_##LA1, KC_##LA2, KC_##LA3, KC_##LA4, KC_##LA5, KC_##LA6, KC_##LA7, KC_##LA8 }, \
        { KC_##LB1, KC_##LB2, KC_##LB3, KC_##LB4, KC_##LB5, KC_##LB6, KC_##LB9, KC_##LB8 }, \
        { KC_##LC1, KC_##LC2, KC_##LC3, KC_##LC4, KC_##LC5, KC_##LC6, KC_##LC9, KC_##LC8 }, \
        { KC_##LD1, KC_##LD9, KC_##LD3, KC_##LD4, KC_##LD5, KC_##LD6, KC_##LD7, KC_##LD8 }, \
        { KC_##LE1, KC_##LE2, KC_##LE3, KC_##LA9, KC_##LE5, KC_##LE9, KC_##LE7, KC_##LE8 }, \
        { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
        { KC_##RA1, KC_##RA2, KC_##RA3, KC_##RA4, KC_##RA5, KC_##RA6, KC_##RA7, KC_##RA8 }, \
        { KC_##RB1, KC_##RB2, KC_##RB3, KC_##RB4, KC_##RB5, KC_##RB6, KC_##RB7, KC_##RB8 }, \
        { KC_##RC1, KC_##RC2, KC_##RC3, KC_##RC4, KC_##RC5, KC_##RC6, KC_##RC9, KC_##RC8 }, \
        { KC_##RD1, KC_##RD2, KC_##RD3, KC_##RD4, KC_##RD9, KC_##RD6, KC_##RD7, KC_##RD8 }, \
        { KC_##RE1, KC_##RE2, KC_##RE9, KC_##RE4, KC_##RE5, KC_##RE6, KC_##RE7, KC_##RE8 }, \
        { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_##RA9, KC_##RB9 } \
    }
