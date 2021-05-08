#pragma once

#include "quantum.h"
#ifdef KEYBOARD_rgbkb_sol_rev1
#include "rev1.h"
#else
#include "rev2.h"
#endif


#define LAYOUT( \
  L00, L01, L02, L03, L04, L05, L06, R06, R00, R01, R02, R03, R04, R05, \
  L10, L11, L12, L13, L14, L15, L16, R16, R10, R11, R12, R13, R14, R15, \
  L20, L21, L22, L23, L24, L25, L26, R26, R20, R21, R22, R23, R24, R25, \
  L30, L31, L32, L33, L34, L35, L36, R36, R30, R31, R32, R33, R34, R35, \
  L40, L41, L42, L43, L44, L45, L46, R46, R40, R41, R42, R43, R44, R45, \
                           L55, L56, R56, R50 \
  ) \
  { \
    { L00, L01, L02, L03, L04, L05, L06 }, \
    { L10, L11, L12, L13, L14, L15, L16 }, \
    { L20, L21, L22, L23, L24, L25, L26 }, \
    { L30, L31, L32, L33, L34, L35, L36 }, \
    { L40, L41, L42, L43, L44, L45, L46 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, L55, L56 }, \
    { R05, R04, R03, R02, R01, R00, R06 }, \
    { R15, R14, R13, R12, R11, R10, R16 }, \
    { R25, R24, R23, R22, R21, R20, R26 }, \
    { R35, R34, R33, R32, R31, R30, R36 }, \
    { R45, R44, R43, R42, R41, R40, R46 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, R50, R56 } \
  }

#define ENCODER_LAYOUT( \
  E10, E11, \
  E20, E21 \
) \
{ \
  { E10, E11 }, \
  { E20, E21 } \
}

#define EXTRA_ENCODER_LAYOUT( \
  E10, E11, \
  E20, E21, \
  E30, E31, \
  E40, E41, \
  E50, E51, \
  E60, E61  \
) \
{ \
  { E10, E11 }, \
  { E20, E21 }, \
  { E30, E31 }, \
  { E40, E41 }, \
  { E50, E51 }, \
  { E60, E61 } \
}
