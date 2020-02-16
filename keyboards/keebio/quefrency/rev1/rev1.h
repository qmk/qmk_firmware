#pragma once

#include "quefrency.h"

#include "quantum.h"


#ifdef USE_I2C
#include <stddef.h>
#ifdef __AVR__
  #include <avr/io.h>
  #include <avr/interrupt.h>
#endif
#endif

#define LAYOUT( \
  LA1, LA2, LA3, LA4, LA5, LA6, LA7, RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, \
  LB1, LB2, LB3, LB4, LB5, LB6,      RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8, \
  LC1, LC2, LC3, LC4, LC5, LC6,      RC1, RC2, RC3, RC4, RC5, RC6,      RC8, \
  LD1,      LD3, LD4, LD5, LD6, LD7, RD1, RD2, RD3, RD4,      RD6, RD7, RD8, \
  LE1, LE2, LE3,      LE5,      LE7, RE1, RE2,      RE4, RE5, RE6, RE7, RE8 \
  ) \
  { \
    { LA1, LA2, LA3, LA4, LA5, LA6, LA7, KC_NO }, \
    { LB1, LB2, LB3, LB4, LB5, LB6, KC_NO, KC_NO }, \
    { LC1, LC2, LC3, LC4, LC5, LC6, KC_NO, KC_NO }, \
    { LD1, KC_NO, LD3, LD4, LD5, LD6, LD7, KC_NO }, \
    { LE1, LE2, LE3, KC_NO, LE5, KC_NO, LE7, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8 }, \
    { RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8 }, \
    { RC1, RC2, RC3, RC4, RC5, RC6, KC_NO, RC8 }, \
    { RD1, RD2, RD3, RD4, KC_NO, RD6, RD7, RD8 }, \
    { RE1, RE2, KC_NO, RE4, RE5, RE6, RE7, RE8 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO } \
  }

#define LAYOUT_65( \
  LA1, LA2, LA3, LA4, LA5, LA6, LA7, RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, RA9, \
  LB1, LB2, LB3, LB4, LB5, LB6,      RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8, RB9, \
  LC1, LC2, LC3, LC4, LC5, LC6,      RC1, RC2, RC3, RC4, RC5, RC6,      RC8, RC9, \
  LD1,      LD3, LD4, LD5, LD6, LD7, RD1, RD2, RD3, RD4,      RD6, RD7, RD8, RD9, \
  LE1, LE2, LE3,      LE5,      LE7, RE1, RE2,      RE4, RE5, RE6, RE7, RE8, RE9 \
  ) \
  { \
    { LA1, LA2, LA3, LA4, LA5, LA6, LA7, KC_NO }, \
    { LB1, LB2, LB3, LB4, LB5, LB6, KC_NO, KC_NO }, \
    { LC1, LC2, LC3, LC4, LC5, LC6, KC_NO, KC_NO }, \
    { LD1, KC_NO, LD3, LD4, LD5, LD6, LD7, KC_NO }, \
    { LE1, LE2, LE3, KC_NO, LE5, KC_NO, LE7, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8 }, \
    { RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8 }, \
    { RC1, RC2, RC3, RC4, RC5, RC6, RC9, RC8 }, \
    { RD1, RD2, RD3, RD4, RD9, RD6, RD7, RD8 }, \
    { RE1, RE2, RE9, RE4, RE5, RE6, RE7, RE8 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RA9, RB9 } \
  }

#define LAYOUT_60_with_macro( \
  LA9, LA8, LA1, LA2, LA3, LA4, LA5, LA6, LA7, RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, \
  LB9, LB8, LB1, LB2, LB3, LB4, LB5, LB6,      RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8, \
  LC9, LC8, LC1, LC2, LC3, LC4, LC5, LC6,      RC1, RC2, RC3, RC4, RC5, RC6,      RC8, \
  LD9, LD8, LD1,      LD3, LD4, LD5, LD6, LD7, RD1, RD2, RD3, RD4,      RD6, RD7, RD8, \
  LE9, LE8, LE1, LE2, LE3,      LE5,      LE7, RE1, RE2,      RE4, RE5, RE6, RE7, RE8 \
  ) \
  { \
    { LA1, LA2, LA3, LA4, LA5, LA6, LA7, LA8 }, \
    { LB1, LB2, LB3, LB4, LB5, LB6, LB9, LB8 }, \
    { LC1, LC2, LC3, LC4, LC5, LC6, LC9, LC8 }, \
    { LD1, LD9, LD3, LD4, LD5, LD6, LD7, LD8 }, \
    { LE1, LE2, LE3, LA9, LE5, LE9, LE7, LE8 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8 }, \
    { RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8 }, \
    { RC1, RC2, RC3, RC4, RC5, RC6, KC_NO, RC8 }, \
    { RD1, RD2, RD3, RD4, KC_NO, RD6, RD7, RD8 }, \
    { RE1, RE2, KC_NO, RE4, RE5, RE6, RE7, RE8 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO } \
  }


#define LAYOUT_65_with_macro( \
  LA9, LA8, LA1, LA2, LA3, LA4, LA5, LA6, LA7, RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, RA9, \
  LB9, LB8, LB1, LB2, LB3, LB4, LB5, LB6,      RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8, RB9, \
  LC9, LC8, LC1, LC2, LC3, LC4, LC5, LC6,      RC1, RC2, RC3, RC4, RC5, RC6,      RC8, RC9, \
  LD9, LD8, LD1,      LD3, LD4, LD5, LD6, LD7, RD1, RD2, RD3, RD4,      RD6, RD7, RD8, RD9, \
  LE9, LE8, LE1, LE2, LE3,      LE5,      LE7, RE1, RE2,      RE4, RE5, RE6, RE7, RE8, RE9 \
  ) \
  { \
    { LA1, LA2, LA3, LA4, LA5, LA6, LA7, LA8 }, \
    { LB1, LB2, LB3, LB4, LB5, LB6, LB9, LB8 }, \
    { LC1, LC2, LC3, LC4, LC5, LC6, LC9, LC8 }, \
    { LD1, LD9, LD3, LD4, LD5, LD6, LD7, LD8 }, \
    { LE1, LE2, LE3, LA9, LE5, LE9, LE7, LE8 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8 }, \
    { RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8 }, \
    { RC1, RC2, RC3, RC4, RC5, RC6, RC9, RC8 }, \
    { RD1, RD2, RD3, RD4, RD9, RD6, RD7, RD8 }, \
    { RE1, RE2, RE9, RE4, RE5, RE6, RE7, RE8 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RA9, RB9 } \
  }
