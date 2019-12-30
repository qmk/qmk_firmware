#ifndef ORTHO_SPLIT_2U_H
#define ORTHO_SPLIT_2U_H

#include "quantum.h"

#define ___ KC_NO

/* probably not going to work...
#define LAYOUT( \
      K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F, \
      K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C,    K1D,   K1F, \
         K21,   K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E, K2F, \
         K31,   K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C,    K3D,   K3F, \
         K41,   K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B,    K4C,   K4E, K4F, \
         K51,   K52, K53, K54,    K56,      K57,   K59, K5A,    K5B,   K5D, K5E, K5F  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, ___, K1F }, \
    { ___, K21, K22, K23, K24, K25, K26, K17, K28, K29, K2A, K2B, K2C, K2D, K2E, K2F }, \
    { ___, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, ___, K3F }, \
    { ___, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, K4C, ___, K4E, K4F }, \
    { ___, K51, K52, K53, K54, ___, K56, K57, ___, K59, K5A, K5B, ___, K5D, K5E, K5F }, \
}
*/

#define LAYOUT( \
  LA1, LA2, LA3, LA4, LA5, LA6, LA7, RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, RA9, \
  LB1, LB2, LB3, LB4, LB5, LB6, LB7, RB1, RB2, RB3, RB4, RB5, RB6,    RB7,   RB9, \
     LC2,   LC3, LC4, LC5, LC6, LC7, RC1, RC2, RC3, RC4, RC5, RC6, RC7, RC8, RC9, \
     LD2,   LD3, LD4, LD5, LD6, LD7, RD1, RD2, RD3, RD4, RD5, RD6,    RD7,   RD9, \
     LE2,   LE3, LE4, LE5, LE6, LE7, RE1, RE2, RE3, RE4, RE5,    RE6,   RE8, RE9, \
     LF2,   LF3, LF4, LF5,    LF6,      RF1,   RF3, RF4,    RF5,   RF7, RF8, RF9  \
  ) \
  { \
    { LA1, LA2, LA3, LA4, LA5, LA6, LA7, ___, ___ }, \
    { LB1, LB2, LB3, LB4, LB5, LB6, LB7, ___, ___ }, \
    { ___, LC2, LC3, LC4, LC5, LC6, LC7, ___, ___ }, \
    { ___, LD2, LD3, LD4, LD5, LD6, LD7, ___, ___ }, \
    { ___, LE2, LE3, LE4, LE5, LE6, LE7, ___, ___ }, \
    { ___, LF2, LF3, LF4, LF5, LF6, ___, ___, ___ }, \
    { RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, RA9 }, \
    { RB1, RB2, RB3, RB4, RB5, RB6, RB7, ___, RB9 }, \
    { RC1, RC2, RC3, RC4, RC5, RC6, RC7, RC8, RC9 }, \
    { RD1, RD2, RD3, RD4, RD5, RD6, RD7, ___, RD9 }, \
    { RE1, RE2, RE3, RE4, RE5, RE6, ___, RE8, RE9 }, \
    { RF1, ___, RF3, RF4, RF5, ___, RF7, RF8, RF9 }, \
  }

#endif // ORTHO_SPLIT_2U_H
