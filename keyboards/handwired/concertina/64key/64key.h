#pragma once

#include "quantum.h"

/*
The matrix is constructed for ease of soldering and for density.
It uses the same coordinate system as the program that defines
the case model (the DMOTE application), but not the same coordinates.

The nomenclature is <side><cluster>_<column><row>.

L: Left hand.
R: Right hand.
T: Thumb cluster.
M: Main cluster.

Numbers increase going to the right and away from the user on the
right-hand side of the keyboard, looking directly at each of the two
key clusters (main and thumb), one by one.
This coordinate system is mirrored for the left-hand side.
*/

#define LAYOUT_64key( \
                  LT_32, LT_22, LT_12,        \
                  LT_31, LT_21, LT_11, LT_01, \
                         LT_20, LT_10, LT_00, \
                                              \
                  LM_34, LM_24, LM_14, LM_04, \
    LM_53, LM_43, LM_33, LM_23, LM_13, LM_03, \
    LM_52, LM_42, LM_32, LM_22, LM_12, LM_02, \
    LM_51, LM_41, LM_31, LM_21, LM_11,        \
                         LM_20,               \
                                              \
           RT_12, RT_22, RT_32,               \
    RT_01, RT_11, RT_21, RT_31,               \
    RT_00, RT_10, RT_20,                      \
                                              \
    RM_04, RM_14, RM_24, RM_34,               \
    RM_03, RM_13, RM_23, RM_33, RM_43, RM_53, \
    RM_02, RM_12, RM_22, RM_32, RM_42, RM_52, \
           RM_11, RM_21, RM_31, RM_41, RM_51, \
                  RM_20                       \
  ) \
  { \
    { LT_00, LT_10, LT_20, LT_31, LM_20, LM_31, LM_41, LM_51 }, \
    { LT_01, LT_11, LT_21, LM_11, LM_21, LM_32, LM_42, LM_52 }, \
    { LT_12, LT_22, LT_32, LM_12, LM_22, LM_33, LM_43, LM_53 }, \
    { LM_02, LM_03, LM_04, LM_13, LM_23, LM_14, LM_24, LM_34 }, \
    { RT_00, RT_10, RT_20, RT_31, RM_20, RM_31, RM_41, RM_51 }, \
    { RT_01, RT_11, RT_21, RM_11, RM_21, RM_32, RM_42, RM_52 }, \
    { RT_12, RT_22, RT_32, RM_12, RM_22, RM_33, RM_43, RM_53 }, \
    { RM_02, RM_03, RM_04, RM_13, RM_23, RM_14, RM_24, RM_34 }, \
  }
