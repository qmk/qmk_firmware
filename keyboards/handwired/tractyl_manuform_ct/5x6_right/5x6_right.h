/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "tractyl_manuform.h"
//#include "elite_c.h"
#include "quantum.h"

#define XXX KC_NO

// clang-format off
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

// clang-format on
