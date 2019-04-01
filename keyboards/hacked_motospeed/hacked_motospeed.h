/* Copyright 2019 %YOUR_NAME%
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

#include "quantum.h"

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
    EWR, DWR, CWR, BWR, AWR, FWR,   \
         DXR, CXR, BXR, AXR, FXR,   \
    EZR, DYR, CYR, BYR, AYR, DVR,   \
         DZR, CZR, BZR, AZR, FZR,   \
                                    \
    FZL, AZL, BZL, CZL, DZL,        \
    DVL, AYL, BYL, CYL, DYL, EZL,   \
    FXL, AXL, BXL, CXL, DXL,        \
    FWL, AWL, BWL, CWL, DWL, EWL    \
) \
{ \
    { EWR,   DWR,   CWR,   BWR,   AWR,   FWR,     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, DXR,   CXR,   BXR,   AXR,   FXR,     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, DYR,   CYR,   BYR,   AYR,   KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { EZR,   DZR,   CZR,   AZR,   BZR,   FZR,     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, DVR,   KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
                                                                                              \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   FZL,   BZL,   AZL,   CZL,   DZL,   KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO, AYL,   BYL,   CYL,   DYL,   EZL   }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   FXL,   AXL,   BXL,   CXL,   DXL,   KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   FWL,   AWL,   BWL,   CWL,   DWL,   EWL   }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, DVL,   KC_NO }  \
}
