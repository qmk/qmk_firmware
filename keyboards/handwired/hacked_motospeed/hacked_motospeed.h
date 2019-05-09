/* Copyright 2019 Vladislav Opara <Deckweiss75@gmail.com>
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
    EWR, DWR, CWR, BWR, AWR, FXR,   FYL, AZL, BZL, CZL, DZL,        \
         DXR, CXR, BXR, AXR, FZR,   DVL, AYL, BYL, CYL, DYL, EZL,   \
    EZR, DYR, CYR, BYR, AYR, DVR,   FZL, AXL, BXL, CXL, DXL,        \
         DZR, CZR, BZR, AZR, FYR,   FXL, AWL, BWL, CWL, DWL, EWL    \
) \
{ \
    { EWR,   DWR,   CWR,   BWR,   AWR,   KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, DXR,   CXR,   BXR,   AXR,   FXR,     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, DYR,   CYR,   BYR,   AYR,   FYR,     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { EZR,   DZR,   CZR,   AZR,   BZR,   FZR,     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, DVR,   KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
                                                                                              \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   FZL,   BZL,   AZL,   CZL,   DZL,   EZL   }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   FYL,   AYL,   BYL,   CYL,   DYL,   KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   FXL,   AXL,   BXL,   CXL,   DXL,   KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO, AWL,   BWL,   CWL,   DWL,   EWL   }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, DVL,   KC_NO }  \
}
