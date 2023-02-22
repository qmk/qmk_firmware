/* Copyright 2021 Danny Nguyen <danny@keeb.io>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "sinc.h"
#include "quantum.h"

#ifdef USE_I2C
#include <stddef.h>
#ifdef __AVR__
    #include <avr/io.h>
    #include <avr/interrupt.h>
#endif
#endif

#define LAYOUT_75( \
  LF3, LF4, LF5, LF6, LF7, LF8, LF9,           RF2, RF3, RF4, RF5, RF6, RF7, RF8, \
  LA3, LA4, LA5, LA6, LA7, LA8, LA9,      RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, \
  LB3, LB4, LB5, LB6, LB7, LB8,           RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8, \
  LC3, LC4, LC5, LC6, LC7, LC8,           RC1, RC2, RC3, RC4, RC5, RC6,      RC8, \
  LD3,      LD5, LD6, LD7, LD8, LD9,      RD1, RD2, RD3, RD4, RD5,      RD7, RD8, \
  LE3, LE4, LE5, LE6, LE7, LE8,           RE1, RE2, RE3, RE4, RE5,      RE7, RE8 \
  ) \
  { \
    { KC_NO, KC_NO, LA3, LA4, LA5, LA6, LA7, LA8, LA9 }, \
    { KC_NO, KC_NO, LB3, LB4, LB5, LB6, LB7, LB8, KC_NO }, \
    { KC_NO, KC_NO, LC3, LC4, LC5, LC6, LC7, LC8, KC_NO }, \
    { KC_NO, KC_NO, LD3, KC_NO, LD5, LD6, LD7, LD8, LD9 }, \
    { KC_NO, KC_NO, LE3, LE4, LE5, LE6, LE7, LE8, KC_NO }, \
    { KC_NO, KC_NO, LF3, LF4, LF5, LF6, LF7, LF8, LF9 }, \
    { RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, KC_NO }, \
    { RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8, KC_NO }, \
    { RC1, RC2, RC3, RC4, RC5, RC6, KC_NO, RC8, KC_NO }, \
    { RD1, RD2, RD3, RD4, RD5, KC_NO, RD7, RD8, KC_NO }, \
    { RE1, RE2, RE3, RE4, RE5, KC_NO, RE7, RE8, KC_NO }, \
    { KC_NO, RF2, RF3, RF4, RF5, RF6, RF7, RF8, KC_NO } \
  }

#define LAYOUT_80( \
  LF3, LF4, LF5, LF6, LF7, LF8, LF9,           RF2, RF3, RF4, RF5, RF6, RF7, RF8, RF9, \
  LA3, LA4, LA5, LA6, LA7, LA8, LA9,      RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, RA9, \
  LB3, LB4, LB5, LB6, LB7, LB8,           RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8, RB9, \
  LC3, LC4, LC5, LC6, LC7, LC8,           RC1, RC2, RC3, RC4, RC5, RC6,      RC8, RC9, \
  LD3,      LD5, LD6, LD7, LD8, LD9,      RD1, RD2, RD3, RD4, RD5,      RD7, RD8, RD9, \
  LE3, LE4, LE5, LE6, LE7, LE8,           RE1, RE2, RE3, RE4, RE5,      RE7, RE8, RE9 \
  ) \
  { \
    { KC_NO, KC_NO, LA3, LA4, LA5, LA6, LA7, LA8, LA9 }, \
    { KC_NO, KC_NO, LB3, LB4, LB5, LB6, LB7, LB8, KC_NO }, \
    { KC_NO, KC_NO, LC3, LC4, LC5, LC6, LC7, LC8, KC_NO }, \
    { KC_NO, KC_NO, LD3, KC_NO, LD5, LD6, LD7, LD8, LD9 }, \
    { KC_NO, KC_NO, LE3, LE4, LE5, LE6, LE7, LE8, KC_NO }, \
    { KC_NO, KC_NO, LF3, LF4, LF5, LF6, LF7, LF8, LF9 }, \
    { RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, RA9 }, \
    { RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8, RB9 }, \
    { RC1, RC2, RC3, RC4, RC5, RC6, KC_NO, RC8, RC9 }, \
    { RD1, RD2, RD3, RD4, RD5, KC_NO, RD7, RD8, RD9 }, \
    { RE1, RE2, RE3, RE4, RE5, KC_NO, RE7, RE8, RE9 }, \
    { KC_NO, RF2, RF3, RF4, RF5, RF6, RF7, RF8, RF9 } \
  }

#define LAYOUT_75_with_macro( \
  LF1,      LF3, LF4, LF5, LF6, LF7, LF8, LF9,           RF2, RF3, RF4, RF5, RF6, RF7, RF8, \
  LA1, LA2, LA3, LA4, LA5, LA6, LA7, LA8, LA9,      RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, \
  LB1, LB2, LB3, LB4, LB5, LB6, LB7, LB8,           RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8, \
  LC1, LC2, LC3, LC4, LC5, LC6, LC7, LC8,           RC1, RC2, RC3, RC4, RC5, RC6,      RC8, \
  LD1, LD2, LD3,      LD5, LD6, LD7, LD8, LD9,      RD1, RD2, RD3, RD4, RD5,      RD7, RD8, \
  LE1, LE2, LE3, LE4, LE5, LE6, LE7, LE8,           RE1, RE2, RE3, RE4, RE5,      RE7, RE8 \
  ) \
  { \
    { LA1, LA2, LA3, LA4, LA5, LA6, LA7, LA8, LA9 }, \
    { LB1, LB2, LB3, LB4, LB5, LB6, LB7, LB8, KC_NO }, \
    { LC1, LC2, LC3, LC4, LC5, LC6, LC7, LC8, KC_NO }, \
    { LD1, LD2, LD3, KC_NO, LD5, LD6, LD7, LD8, LD9 }, \
    { LE1, LE2, LE3, LE4, LE5, LE6, LE7, LE8, KC_NO }, \
    { LF1, KC_NO, LF3, LF4, LF5, LF6, LF7, LF8, LF9 }, \
    { RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, KC_NO }, \
    { RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8, KC_NO }, \
    { RC1, RC2, RC3, RC4, RC5, RC6, KC_NO, RC8, KC_NO }, \
    { RD1, RD2, RD3, RD4, RD5, KC_NO, RD7, RD8, KC_NO }, \
    { RE1, RE2, RE3, RE4, RE5, KC_NO, RE7, RE8, KC_NO }, \
    { KC_NO, RF2, RF3, RF4, RF5, RF6, RF7, RF8, KC_NO } \
  }

#define LAYOUT_80_with_macro( \
  LF1,      LF3, LF4, LF5, LF6, LF7, LF8, LF9,           RF2, RF3, RF4, RF5, RF6, RF7, RF8, RF9, \
  LA1, LA2, LA3, LA4, LA5, LA6, LA7, LA8, LA9,      RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, RA9, \
  LB1, LB2, LB3, LB4, LB5, LB6, LB7, LB8,           RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8, RB9, \
  LC1, LC2, LC3, LC4, LC5, LC6, LC7, LC8,           RC1, RC2, RC3, RC4, RC5, RC6,      RC8, RC9, \
  LD1, LD2, LD3,      LD5, LD6, LD7, LD8, LD9,      RD1, RD2, RD3, RD4, RD5,      RD7, RD8, RD9, \
  LE1, LE2, LE3, LE4, LE5, LE6, LE7, LE8,           RE1, RE2, RE3, RE4, RE5,      RE7, RE8, RE9 \
  ) \
  { \
    { LA1, LA2, LA3, LA4, LA5, LA6, LA7, LA8, LA9 }, \
    { LB1, LB2, LB3, LB4, LB5, LB6, LB7, LB8, KC_NO }, \
    { LC1, LC2, LC3, LC4, LC5, LC6, LC7, LC8, KC_NO }, \
    { LD1, LD2, LD3, KC_NO, LD5, LD6, LD7, LD8, LD9 }, \
    { LE1, LE2, LE3, LE4, LE5, LE6, LE7, LE8, KC_NO }, \
    { LF1, KC_NO, LF3, LF4, LF5, LF6, LF7, LF8, LF9 }, \
    { RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, RA9 }, \
    { RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8, RB9 }, \
    { RC1, RC2, RC3, RC4, RC5, RC6, KC_NO, RC8, RC9 }, \
    { RD1, RD2, RD3, RD4, RD5, KC_NO, RD7, RD8, RD9 }, \
    { RE1, RE2, RE3, RE4, RE5, KC_NO, RE7, RE8, RE9 }, \
    { KC_NO, RF2, RF3, RF4, RF5, RF6, RF7, RF8, RF9 } \
  }

#define LAYOUT_75_iso( \
  LF3, LF4, LF5, LF6, LF7, LF8, LF9,           RF2, RF3, RF4, RF5, RF6, RF7, RF8, \
  LA3, LA4, LA5, LA6, LA7, LA8, LA9,      RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, \
  LB3, LB4, LB5, LB6, LB7, LB8,           RB1, RB2, RB3, RB4, RB5, RB6, RB7,      \
  LC3, LC4, LC5, LC6, LC7, LC8,           RC1, RC2, RC3, RC4, RC5, RC6, RC7, RC8, \
  LD3, LD4, LD5, LD6, LD7, LD8, LD9,      RD1, RD2, RD3, RD4, RD5,      RD7, RD8, \
  LE3, LE4, LE5, LE6, LE7, LE8,           RE1, RE2, RE3, RE4, RE5,      RE7, RE8 \
  ) \
  { \
    { KC_NO, KC_NO, LA3, LA4, LA5, LA6, LA7, LA8, LA9 }, \
    { KC_NO, KC_NO, LB3, LB4, LB5, LB6, LB7, LB8, KC_NO }, \
    { KC_NO, KC_NO, LC3, LC4, LC5, LC6, LC7, LC8, KC_NO }, \
    { KC_NO, KC_NO, LD3, LD4, LD5, LD6, LD7, LD8, LD9 }, \
    { KC_NO, KC_NO, LE3, LE4, LE5, LE6, LE7, LE8, KC_NO }, \
    { KC_NO, KC_NO, LF3, LF4, LF5, LF6, LF7, LF8, LF9 }, \
    { RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, KC_NO }, \
    { RB1, RB2, RB3, RB4, RB5, RB6, RB7, KC_NO, KC_NO }, \
    { RC1, RC2, RC3, RC4, RC5, RC6, RC7, RC8, KC_NO }, \
    { RD1, RD2, RD3, RD4, RD5, KC_NO, RD7, RD8, KC_NO }, \
    { RE1, RE2, RE3, RE4, RE5, KC_NO, RE7, RE8, KC_NO }, \
    { KC_NO, RF2, RF3, RF4, RF5, RF6, RF7, RF8, KC_NO } \
  }

#define LAYOUT_80_iso( \
  LF3, LF4, LF5, LF6, LF7, LF8, LF9,           RF2, RF3, RF4, RF5, RF6, RF7, RF8, RF9, \
  LA3, LA4, LA5, LA6, LA7, LA8, LA9,      RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, RA9, \
  LB3, LB4, LB5, LB6, LB7, LB8,           RB1, RB2, RB3, RB4, RB5, RB6, RB7,      RB9, \
  LC3, LC4, LC5, LC6, LC7, LC8,           RC1, RC2, RC3, RC4, RC5, RC6, RC7, RC8, RC9, \
  LD3, LD4, LD5, LD6, LD7, LD8, LD9,      RD1, RD2, RD3, RD4, RD5,      RD7, RD8, RD9, \
  LE3, LE4, LE5, LE6, LE7, LE8,           RE1, RE2, RE3, RE4, RE5,      RE7, RE8, RE9 \
  ) \
  { \
    { KC_NO, KC_NO, LA3, LA4, LA5, LA6, LA7, LA8, LA9 }, \
    { KC_NO, KC_NO, LB3, LB4, LB5, LB6, LB7, LB8, KC_NO }, \
    { KC_NO, KC_NO, LC3, LC4, LC5, LC6, LC7, LC8, KC_NO }, \
    { KC_NO, KC_NO, LD3, LD4, LD5, LD6, LD7, LD8, LD9 }, \
    { KC_NO, KC_NO, LE3, LE4, LE5, LE6, LE7, LE8, KC_NO }, \
    { KC_NO, KC_NO, LF3, LF4, LF5, LF6, LF7, LF8, LF9 }, \
    { RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, RA9 }, \
    { RB1, RB2, RB3, RB4, RB5, RB6, RB7, KC_NO, RB9 }, \
    { RC1, RC2, RC3, RC4, RC5, RC6, RC7, RC8, RC9 }, \
    { RD1, RD2, RD3, RD4, RD5, KC_NO, RD7, RD8, RD9 }, \
    { RE1, RE2, RE3, RE4, RE5, KC_NO, RE7, RE8, RE9 }, \
    { KC_NO, RF2, RF3, RF4, RF5, RF6, RF7, RF8, RF9 } \
  }

#define LAYOUT_75_iso_with_macro( \
  LF1,      LF3, LF4, LF5, LF6, LF7, LF8, LF9,           RF2, RF3, RF4, RF5, RF6, RF7, RF8, \
  LA1, LA2, LA3, LA4, LA5, LA6, LA7, LA8, LA9,      RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, \
  LB1, LB2, LB3, LB4, LB5, LB6, LB7, LB8,           RB1, RB2, RB3, RB4, RB5, RB6, RB7,      \
  LC1, LC2, LC3, LC4, LC5, LC6, LC7, LC8,           RC1, RC2, RC3, RC4, RC5, RC6, RC7, RC8, \
  LD1, LD2, LD3, LD4, LD5, LD6, LD7, LD8, LD9,      RD1, RD2, RD3, RD4, RD5,      RD7, RD8, \
  LE1, LE2, LE3, LE4, LE5, LE6, LE7, LE8,           RE1, RE2, RE3, RE4, RE5,      RE7, RE8 \
  ) \
  { \
    { LA1, LA2, LA3, LA4, LA5, LA6, LA7, LA8, LA9 }, \
    { LB1, LB2, LB3, LB4, LB5, LB6, LB7, LB8, KC_NO }, \
    { LC1, LC2, LC3, LC4, LC5, LC6, LC7, LC8, KC_NO }, \
    { LD1, LD2, LD3, LD4, LD5, LD6, LD7, LD8, LD9 }, \
    { LE1, LE2, LE3, LE4, LE5, LE6, LE7, LE8, KC_NO }, \
    { LF1, KC_NO, LF3, LF4, LF5, LF6, LF7, LF8, LF9 }, \
    { RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, KC_NO }, \
    { RB1, RB2, RB3, RB4, RB5, RB6, RB7, KC_NO, KC_NO }, \
    { RC1, RC2, RC3, RC4, RC5, RC6, RC7, RC8, KC_NO }, \
    { RD1, RD2, RD3, RD4, RD5, KC_NO, RD7, RD8, KC_NO }, \
    { RE1, RE2, RE3, RE4, RE5, KC_NO, RE7, RE8, KC_NO }, \
    { KC_NO, RF2, RF3, RF4, RF5, RF6, RF7, RF8, KC_NO } \
  }

#define LAYOUT_80_iso_with_macro( \
  LF1,      LF3, LF4, LF5, LF6, LF7, LF8, LF9,           RF2, RF3, RF4, RF5, RF6, RF7, RF8, RF9, \
  LA1, LA2, LA3, LA4, LA5, LA6, LA7, LA8, LA9,      RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, RA9, \
  LB1, LB2, LB3, LB4, LB5, LB6, LB7, LB8,           RB1, RB2, RB3, RB4, RB5, RB6, RB7,      RB9, \
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
    { LF1, KC_NO, LF3, LF4, LF5, LF6, LF7, LF8, LF9 }, \
    { RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, RA9 }, \
    { RB1, RB2, RB3, RB4, RB5, RB6, RB7, KC_NO, RB9 }, \
    { RC1, RC2, RC3, RC4, RC5, RC6, RC7, RC8, RC9 }, \
    { RD1, RD2, RD3, RD4, RD5, KC_NO, RD7, RD8, RD9 }, \
    { RE1, RE2, RE3, RE4, RE5, KC_NO, RE7, RE8, RE9 }, \
    { KC_NO, RF2, RF3, RF4, RF5, RF6, RF7, RF8, RF9 } \
  }

#define LAYOUT_all( \
  LF1,      LF3, LF4, LF5, LF6, LF7, LF8, LF9,           RF2, RF3, RF4, RF5, RF6, RF7, RF8, RF9, \
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
    { LF1, KC_NO, LF3, LF4, LF5, LF6, LF7, LF8, LF9 }, \
    { RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, RA9 }, \
    { RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8, RB9 }, \
    { RC1, RC2, RC3, RC4, RC5, RC6, RC7, RC8, RC9 }, \
    { RD1, RD2, RD3, RD4, RD5, KC_NO, RD7, RD8, RD9 }, \
    { RE1, RE2, RE3, RE4, RE5, KC_NO, RE7, RE8, RE9 }, \
    { KC_NO, RF2, RF3, RF4, RF5, RF6, RF7, RF8, RF9 } \
  }
