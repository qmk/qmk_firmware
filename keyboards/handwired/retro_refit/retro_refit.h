#pragma once

#include "quantum.h"

// This macro is an example of using a non-standard row-column matrix. The
// keyboard in question had 11 rows and 8 columns, but the rows were not all
// horizontal, and the columns were not all vertical. For example, row 2
// contained "Print Screen", "N", "M", ",", ".", "/", "Right Shift", and
// "Left Alt". Column 0 contained "F6", "7", "O", "'", "Q", "D", "B",
// "Left Alt", "Up Arrow", and "Down Arrow".
//
// The macro makes programming the keys easier and in a more straight-forward
// manner because it realigns the keys into a 6x15 sensible keyboard layout
// instead of the obtuse 11x8 matrix.

#define LAYOUT( \
  K77, K05, K04, K03, K02, K01, K00, KA7, KA6, KA5, KA4, KA3, KA2, K11, K94, \
  K27, K76, K75, K74, K73, K72, K71, K70, K67, K66, K65, K64, K63, K62, KA1, \
  K61, K60, K57, K56, K55, K54, K53, K52, K51, K50, K47, K46, K45,      K97, \
  K43, K42, K41, K40, K37, K36, K35, K34, K33, K32, K31, K30,      K44, K87, \
  K26,      K24, K23, K22, K21, K20, K17, K16, K15, K14, K13, K12, KA0, K91, \
  K10, K06, K25,                K07,                K86, K85, K95, K90, K93  \
) { \
  {  K00,    K01,    K02,    K03,    K04,    K05,  K06,    K07  }, \
  {  K10,    K11,    K12,    K13,    K14,    K15,  K16,    K17  }, \
  {  K20,    K21,    K22,    K23,    K24,    K25,  K26,    K27  }, \
  {  K30,    K31,    K32,    K33,    K34,    K35,  K36,    K37  }, \
  {  K40,    K41,    K42,    K43,    K44,    K45,  K46,    K47  }, \
  {  K50,    K51,    K52,    K53,    K54,    K55,  K56,    K57  }, \
  {  K60,    K61,    K62,    K63,    K64,    K65,  K66,    K67  }, \
  {  K70,    K71,    K72,    K73,    K74,    K75,  K76,    K77  }, \
  {  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  K85,  K86,    K87  }, \
  {  K90,    K91,    KC_NO,  K93,    K94,    K95,  KC_NO,  K97  }, \
  {  KA0,    KA1,    KA2,    KA3,    KA4,    KA5,  KA6,    KA7  } \
}
