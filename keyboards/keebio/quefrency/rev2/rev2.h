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

#define LAYOUT_60( \
  LA3, LA4, LA5, LA6, LA7, LA8, LA9,      RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, \
  LB3, LB4, LB5, LB6, LB7, LB8,           RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8, \
  LC3, LC4, LC5, LC6, LC7, LC8,           RC1, RC2, RC3, RC4, RC5, RC6,      RC8, \
  LD3,      LD5, LD6, LD7, LD8, LD9,      RD1, RD2, RD3, RD4, RD5,      RD7, RD8, \
  LE3, LE4, LE5, LE6,      LE8,           RE1, RE2, RE3, RE4, RE5,      RE7, RE8 \
  ) \
  { \
    { KC_NO, KC_NO, LA3, LA4, LA5, LA6, LA7, LA8, LA9 }, \
    { KC_NO, KC_NO, LB3, LB4, LB5, LB6, LB7, LB8, KC_NO }, \
    { KC_NO, KC_NO, LC3, LC4, LC5, LC6, LC7, LC8, KC_NO }, \
    { KC_NO, KC_NO, LD3, KC_NO, LD5, LD6, LD7, LD8, LD9 }, \
    { KC_NO, KC_NO, LE3, LE4, LE5, LE6, KC_NO, LE8, KC_NO }, \
    { RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, KC_NO }, \
    { RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8, KC_NO }, \
    { RC1, RC2, RC3, RC4, RC5, RC6, KC_NO, RC8, KC_NO }, \
    { RD1, RD2, RD3, RD4, RD5, KC_NO, RD7, RD8, KC_NO }, \
    { RE1, RE2, RE3, RE4, RE5, KC_NO, RE7, RE8, KC_NO } \
  }

#define LAYOUT LAYOUT_60    // For backwards compatibility with Rev. 1

#define LAYOUT_65( \
  LA3, LA4, LA5, LA6, LA7, LA8, LA9,      RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, RA9, \
  LB3, LB4, LB5, LB6, LB7, LB8,           RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8, RB9, \
  LC3, LC4, LC5, LC6, LC7, LC8,           RC1, RC2, RC3, RC4, RC5, RC6,      RC8, RC9, \
  LD3,      LD5, LD6, LD7, LD8, LD9,      RD1, RD2, RD3, RD4, RD5,      RD7, RD8, RD9, \
  LE3, LE4, LE5, LE6,      LE8,           RE1, RE2, RE3, RE4, RE5,      RE7, RE8, RE9 \
  ) \
  { \
    { KC_NO, KC_NO, LA3, LA4, LA5, LA6, LA7, LA8, LA9 }, \
    { KC_NO, KC_NO, LB3, LB4, LB5, LB6, LB7, LB8, KC_NO }, \
    { KC_NO, KC_NO, LC3, LC4, LC5, LC6, LC7, LC8, KC_NO }, \
    { KC_NO, KC_NO, LD3, KC_NO, LD5, LD6, LD7, LD8, LD9 }, \
    { KC_NO, KC_NO, LE3, LE4, LE5, LE6, KC_NO, LE8, KC_NO }, \
    { RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, RA9 }, \
    { RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8, RB9 }, \
    { RC1, RC2, RC3, RC4, RC5, RC6, KC_NO, RC8, RC9 }, \
    { RD1, RD2, RD3, RD4, RD5, KC_NO, RD7, RD8, RD9 }, \
    { RE1, RE2, RE3, RE4, RE5, KC_NO, RE7, RE8, RE9 } \
  }

#define LAYOUT_60_with_macro( \
  LA1, LA2, LA3, LA4, LA5, LA6, LA7, LA8, LA9,      RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, \
  LB1, LB2, LB3, LB4, LB5, LB6, LB7, LB8,           RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8, \
  LC1, LC2, LC3, LC4, LC5, LC6, LC7, LC8,           RC1, RC2, RC3, RC4, RC5, RC6,      RC8, \
  LD1, LD2, LD3,      LD5, LD6, LD7, LD8, LD9,      RD1, RD2, RD3, RD4, RD5,      RD7, RD8, \
  LE1, LE2, LE3, LE4, LE5, LE6,      LE8,           RE1, RE2, RE3, RE4, RE5,      RE7, RE8 \
  ) \
  { \
    { LA1, LA2, LA3, LA4, LA5, LA6, LA7, LA8, LA9 }, \
    { LB1, LB2, LB3, LB4, LB5, LB6, LB7, LB8, KC_NO }, \
    { LC1, LC2, LC3, LC4, LC5, LC6, LC7, LC8, KC_NO }, \
    { LD1, LD2, LD3, KC_NO, LD5, LD6, LD7, LD8, LD9 }, \
    { LE1, LE2, LE3, LE4, LE5, LE6, KC_NO, LE8, KC_NO }, \
    { RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, KC_NO }, \
    { RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8, KC_NO }, \
    { RC1, RC2, RC3, RC4, RC5, RC6, KC_NO, RC8, KC_NO }, \
    { RD1, RD2, RD3, RD4, RD5, KC_NO, RD7, RD8, KC_NO }, \
    { RE1, RE2, RE3, RE4, RE5, KC_NO, RE7, RE8, KC_NO } \
  }

#define LAYOUT_65_with_macro( \
  LA1, LA2, LA3, LA4, LA5, LA6, LA7, LA8, LA9,      RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, RA9, \
  LB1, LB2, LB3, LB4, LB5, LB6, LB7, LB8,           RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8, RB9, \
  LC1, LC2, LC3, LC4, LC5, LC6, LC7, LC8,           RC1, RC2, RC3, RC4, RC5, RC6,      RC8, RC9, \
  LD1, LD2, LD3,      LD5, LD6, LD7, LD8, LD9,      RD1, RD2, RD3, RD4, RD5,      RD7, RD8, RD9, \
  LE1, LE2, LE3, LE4, LE5, LE6,      LE8,           RE1, RE2, RE3, RE4, RE5,      RE7, RE8, RE9 \
  ) \
  { \
    { LA1, LA2, LA3, LA4, LA5, LA6, LA7, LA8, LA9 }, \
    { LB1, LB2, LB3, LB4, LB5, LB6, LB7, LB8, KC_NO }, \
    { LC1, LC2, LC3, LC4, LC5, LC6, LC7, LC8, KC_NO }, \
    { LD1, LD2, LD3, KC_NO, LD5, LD6, LD7, LD8, LD9 }, \
    { LE1, LE2, LE3, LE4, LE5, LE6, KC_NO, LE8, KC_NO }, \
    { RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, RA9 }, \
    { RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8, RB9 }, \
    { RC1, RC2, RC3, RC4, RC5, RC6, KC_NO, RC8, RC9 }, \
    { RD1, RD2, RD3, RD4, RD5, KC_NO, RD7, RD8, RD9 }, \
    { RE1, RE2, RE3, RE4, RE5, KC_NO, RE7, RE8, RE9 } \
  }

#define LAYOUT_60_iso( \
  LA3, LA4, LA5, LA6, LA7, LA8, LA9,      RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, \
  LB3, LB4, LB5, LB6, LB7, LB8,           RB1, RB2, RB3, RB4, RB5, RB6, RB7,      \
  LC3, LC4, LC5, LC6, LC7, LC8,           RC1, RC2, RC3, RC4, RC5, RC6, RC7, RC8, \
  LD3, LD4, LD5, LD6, LD7, LD8, LD9,      RD1, RD2, RD3, RD4, RD5,      RD7, RD8, \
  LE3, LE4, LE5, LE6,      LE8,           RE1, RE2, RE3, RE4, RE5,      RE7, RE8 \
  ) \
  { \
    { KC_NO, KC_NO, LA3, LA4, LA5, LA6, LA7, LA8, LA9 }, \
    { KC_NO, KC_NO, LB3, LB4, LB5, LB6, LB7, LB8, KC_NO }, \
    { KC_NO, KC_NO, LC3, LC4, LC5, LC6, LC7, LC8, KC_NO }, \
    { KC_NO, KC_NO, LD3, LD4, LD5, LD6, LD7, LD8, LD9 }, \
    { KC_NO, KC_NO, LE3, LE4, LE5, LE6, KC_NO, LE8, KC_NO }, \
    { RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, KC_NO }, \
    { RB1, RB2, RB3, RB4, RB5, RB6, RB7, KC_NO, KC_NO }, \
    { RC1, RC2, RC3, RC4, RC5, RC6, RC7, RC8, KC_NO }, \
    { RD1, RD2, RD3, RD4, RD5, KC_NO, RD7, RD8, KC_NO }, \
    { RE1, RE2, RE3, RE4, RE5, KC_NO, RE7, RE8, KC_NO } \
  }

#define LAYOUT_65_iso( \
  LA3, LA4, LA5, LA6, LA7, LA8, LA9,      RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, RA9, \
  LB3, LB4, LB5, LB6, LB7, LB8,           RB1, RB2, RB3, RB4, RB5, RB6, RB7,      RB9, \
  LC3, LC4, LC5, LC6, LC7, LC8,           RC1, RC2, RC3, RC4, RC5, RC6, RC7, RC8, RC9, \
  LD3, LD4, LD5, LD6, LD7, LD8, LD9,      RD1, RD2, RD3, RD4, RD5,      RD7, RD8, RD9, \
  LE3, LE4, LE5, LE6,      LE8,           RE1, RE2, RE3, RE4, RE5,      RE7, RE8, RE9 \
  ) \
  { \
    { KC_NO, KC_NO, LA3, LA4, LA5, LA6, LA7, LA8, LA9 }, \
    { KC_NO, KC_NO, LB3, LB4, LB5, LB6, LB7, LB8, KC_NO }, \
    { KC_NO, KC_NO, LC3, LC4, LC5, LC6, LC7, LC8, KC_NO }, \
    { KC_NO, KC_NO, LD3, LD4, LD5, LD6, LD7, LD8, LD9 }, \
    { KC_NO, KC_NO, LE3, LE4, LE5, LE6, KC_NO, LE8, KC_NO }, \
    { RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, RA9 }, \
    { RB1, RB2, RB3, RB4, RB5, RB6, RB7, KC_NO, RB9 }, \
    { RC1, RC2, RC3, RC4, RC5, RC6, RC7, RC8, RC9 }, \
    { RD1, RD2, RD3, RD4, RD5, KC_NO, RD7, RD8, RD9 }, \
    { RE1, RE2, RE3, RE4, RE5, KC_NO, RE7, RE8, RE9 } \
  }

#define LAYOUT_60_iso_with_macro( \
  LA1, LA2, LA3, LA4, LA5, LA6, LA7, LA8, LA9,      RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, \
  LB1, LB2, LB3, LB4, LB5, LB6, LB7, LB8,           RB1, RB2, RB3, RB4, RB5, RB6, RB7,      \
  LC1, LC2, LC3, LC4, LC5, LC6, LC7, LC8,           RC1, RC2, RC3, RC4, RC5, RC6, RC7, RC8, \
  LD1, LD2, LD3, LD4, LD5, LD6, LD7, LD8, LD9,      RD1, RD2, RD3, RD4, RD5,      RD7, RD8, \
  LE1, LE2, LE3, LE4, LE5, LE6,      LE8,           RE1, RE2, RE3, RE4, RE5,      RE7, RE8 \
  ) \
  { \
    { LA1, LA2, LA3, LA4, LA5, LA6, LA7, LA8, LA9 }, \
    { LB1, LB2, LB3, LB4, LB5, LB6, LB7, LB8, KC_NO }, \
    { LC1, LC2, LC3, LC4, LC5, LC6, LC7, LC8, KC_NO }, \
    { LD1, LD2, LD3, LD4, LD5, LD6, LD7, LD8, LD9 }, \
    { LE1, LE2, LE3, LE4, LE5, LE6, KC_NO, LE8, KC_NO }, \
    { RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, KC_NO }, \
    { RB1, RB2, RB3, RB4, RB5, RB6, RB7, KC_NO, KC_NO }, \
    { RC1, RC2, RC3, RC4, RC5, RC6, RC7, RC8, KC_NO }, \
    { RD1, RD2, RD3, RD4, RD5, KC_NO, RD7, RD8, KC_NO }, \
    { RE1, RE2, RE3, RE4, RE5, KC_NO, RE7, RE8, KC_NO } \
  }

#define LAYOUT_65_iso_with_macro( \
  LA1, LA2, LA3, LA4, LA5, LA6, LA7, LA8, LA9,      RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, RA9, \
  LB1, LB2, LB3, LB4, LB5, LB6, LB7, LB8,           RB1, RB2, RB3, RB4, RB5, RB6, RB7,      RB9, \
  LC1, LC2, LC3, LC4, LC5, LC6, LC7, LC8,           RC1, RC2, RC3, RC4, RC5, RC6, RC7, RC8, RC9, \
  LD1, LD2, LD3, LD4, LD5, LD6, LD7, LD8, LD9,      RD1, RD2, RD3, RD4, RD5,      RD7, RD8, RD9, \
  LE1, LE2, LE3, LE4, LE5, LE6,      LE8,           RE1, RE2, RE3, RE4, RE5,      RE7, RE8, RE9 \
  ) \
  { \
    { LA1, LA2, LA3, LA4, LA5, LA6, LA7, LA8, LA9 }, \
    { LB1, LB2, LB3, LB4, LB5, LB6, LB7, LB8, KC_NO }, \
    { LC1, LC2, LC3, LC4, LC5, LC6, LC7, LC8, KC_NO }, \
    { LD1, LD2, LD3, LD4, LD5, LD6, LD7, LD8, LD9 }, \
    { LE1, LE2, LE3, LE4, LE5, LE6, KC_NO, LE8, KC_NO }, \
    { RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, RA9 }, \
    { RB1, RB2, RB3, RB4, RB5, RB6, RB7, KC_NO, RB9 }, \
    { RC1, RC2, RC3, RC4, RC5, RC6, RC7, RC8, RC9 }, \
    { RD1, RD2, RD3, RD4, RD5, KC_NO, RD7, RD8, RD9 }, \
    { RE1, RE2, RE3, RE4, RE5, KC_NO, RE7, RE8, RE9 } \
  }

#define LAYOUT_all( \
  LA1, LA2, LA3, LA4, LA5, LA6, LA7, LA8, LA9,      RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, RA9, \
  LB1, LB2, LB3, LB4, LB5, LB6, LB7, LB8,           RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8, RB9, \
  LC1, LC2, LC3, LC4, LC5, LC6, LC7, LC8,           RC1, RC2, RC3, RC4, RC5, RC6, RC7, RC8, RC9, \
  LD1, LD2, LD3, LD4, LD5, LD6, LD7, LD8, LD9,      RD1, RD2, RD3, RD4, RD5,      RD7, RD8, RD9, \
  LE1, LE2, LE3, LE4, LE5, LE6, LE7, LE8,           RE1, RE2, RE3, RE4, RE5,      RE7, RE8, RE9 \
  ) \
  { \
    { LA1, LA2, LA3, LA4, LA5, LA6, LA7, LA8, LA9 }, \
    { LB1, LB2, LB3, LB4, LB5, LB6, LB7, LB8, KC_NO }, \
    { LC1, LC2, LC3, LC4, LC5, LC6, LC7, LC8, KC_NO }, \
    { LD1, LD2, LD3, LD4, LD5, LD6, LD7, LD8, LD9 }, \
    { LE1, LE2, LE3, LE4, LE5, LE6, LE7, LE8, KC_NO }, \
    { RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, RA9 }, \
    { RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8, RB9 }, \
    { RC1, RC2, RC3, RC4, RC5, RC6, RC7, RC8, RC9 }, \
    { RD1, RD2, RD3, RD4, RD5, KC_NO, RD7, RD8, RD9 }, \
    { RE1, RE2, RE3, RE4, RE5, KC_NO, RE7, RE8, RE9 } \
  }
