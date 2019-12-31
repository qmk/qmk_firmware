#ifndef ORTHO_SPLIT_2U_H
#define ORTHO_SPLIT_2U_H

#include "quantum.h"

#define ___ KC_NO

#define LAYOUT( \
  LA1, LA2, LA3, LA4, LA5, LA6, LA7, RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, RA9, \
  LB1, LB2, LB3, LB4, LB5, LB6, LB7, RB1, RB2, RB3, RB4, RB5, RB6,    RB7,   RB9, \
     LC2,   LC3, LC4, LC5, LC6, LC7, RC1, RC2, RC3, RC4, RC5, RC6, RC7, RC8, RC9, \
     LD2,   LD3, LD4, LD5, LD6, LD7, RD1, RD2, RD3, RD4, RD5, RD6,    RD7,   RD9, \
     LE2,   LE3, LE4, LE5, LE6, LE7, RE1, RE2, RE3, RE4, RE5,    RE6,   RE8, RE9, \
     LF2,   LF3, LF4, LF5,    LF7,      RF1,   RF3, RF4,    RF5,   RF7, RF8, RF9  \
  ) \
  { \
    { LA1, LA2, LA3, LA4, LA5, LA6, LA7 }, \
    { LB1, LB2, LB3, LB4, LB5, LB6, LB7 }, \
    { ___, LC2, LC3, LC4, LC5, LC6, LC7 }, \
    { ___, LD2, LD3, LD4, LD5, LD6, LD7 }, \
    { ___, LE2, LE3, LE4, LE5, LE6, LE7 }, \
    { ___, LF2, LF3, LF4, LF5, ___, LF7 }, \
    { RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, RA9 }, \
    { RB1, RB2, RB3, RB4, RB5, RB6, RB7, ___, RB9 }, \
    { RC1, RC2, RC3, RC4, RC5, RC6, RC7, RC8, RC9 }, \
    { RD1, RD2, RD3, RD4, RD5, RD6, RD7, ___, RD9 }, \
    { RE1, RE2, RE3, RE4, RE5, RE6, ___, RE8, RE9 }, \
    { RF1, ___, RF3, RF4, RF5, ___, RF7, RF8, RF9 }  \
  }

#endif // ORTHO_SPLIT_2U_H
