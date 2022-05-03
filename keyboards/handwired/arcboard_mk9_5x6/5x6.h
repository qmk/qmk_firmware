// only process this file once
#pragma once
// inclue dependencies, including PROGMEM
#include "quantum.h"

// An alias for 'we won't use this key'
#define XXX KC_NO

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
/*
 * From the Concertina code comments...
 * The matrix is constructed for ease of soldering and for density.
 * The nomenclature is <side><cluster>_<row><column>.
 *
 * L: Left hand.
 * R: Right hand.
 * T: Thumb cluster.
 * M: Main cluster.
 *
 * Numbers increase going to the right and away from the user on the
 * right-hand side of the keyboard, looking directly at each of the two
 * key clusters (main and thumb), one by one.
 * This coordinate system is mirrored for the left-hand side.
 */

    /* 
     * ,-----------------------------------------,                                           ,-----------------------------------------,
     * |  1,1 |  1,2 |  1,3 |  1,4 |  1,5 |  1,6 |                                           |  1,1 |  1,2 |  1,3 |  1,4 |  1,5 |  1,6 |
     * |------+------+------+------+------+------|                                           |-------------+------+------+------+------|
     * |  2,1 |  2,2 |  2,3 |  2,4 |  2,5 |  2,6 |                               (TRACKBALL) |  2,1 |  2,2 |  2,3 |  2,4 |  2,5 |  2,6 |
     * |------+------+------+------+------|------|------|------|------,        |------|------|------|------+------+------+------+------|
     * |  3,1 |  3,2 |  3,3 |  3,4 |  3,5 |  3,6 |  4,3 |  4,4 |  4,5 |        |  4,1 |  4,2 |  3,1 |  3,2 |  3,3 |  3,4 |  3,5 |  3,6 |
     * |------+------+------+------,------,------,------,------,------,      ,------,------,------,------,-----------------------------,
     *                             |      |      |      |      |             |      |      |      |      |        ,------,
     *                             |  4,1 |  4,2 |  5,3 |  5,4 |             |  4,3 |  4,4 |  4,5 |  4,6 |        |  5,4 |
     *                             |      |      |      |      |             |      |      |      |      | ,------+------+-----,
     *                             '------+------+------+------'             '------'------+------+------' |  5,3 |------| 5,6 |
     *                                    '------+------'                                  '------+------' '------+------+-----'
     *                                    |  5,1 |  5,2 |                                  |  5,1 |  5,2 |        |  5,5 |
     *                                    '------+------'                                  '------+------'        '------'
     */

#define LAYOUT( \
    LM_11, LM_12, LM_13, LM_14, LM_15, LM_16,                    RM_11, RM_12, RM_13, RM_14, RM_15, RM_16, \
    LM_21, LM_22, LM_23, LM_24, LM_25, LM_26,                    RM_21, RM_22, RM_23, RM_24, RM_25, RM_26, \
    LM_31, LM_32, LM_33, LM_34, LM_35, LM_36,                    RM_31, RM_32, RM_33, RM_34, RM_35, RM_36, \
                LT_41, LT_42, LT_43, LT_44, LT_45, RT_41, RT_42, RT_43, RT_44, RT_45, RT_46, \
                       LT_51, LT_52, LT_53, LT_54, RT_51, RT_52, RT_53, RT_54, RT_55, RT_56 \
) \
{ \
    { LM_11, LM_12, LM_13, LM_14, LM_15, LM_16 }, \
    { LM_21, LM_22, LM_23, LM_24, LM_25, LM_26 }, \
    { LM_31, LM_32, LM_33, LM_34, LM_35, LM_36 }, \
    { LT_41, LT_42, LT_43, LT_44, LT_45,   XXX }, \
    { LT_51, LT_52, LT_53, LT_54,   XXX,   XXX }, \
    { RM_11, RM_12, RM_13, RM_14, RM_15, RM_16 }, \
    { RM_21, RM_22, RM_23, RM_24, RM_25, RM_26 }, \
    { RM_31, RM_32, RM_33, RM_34, RM_35, RM_36 }, \
    { RT_41, RT_42, RT_43, RT_44, RT_45, RT_46 }, \
    { RT_51, RT_52, RT_53, RT_54, RT_55, RT_56 } \
}
