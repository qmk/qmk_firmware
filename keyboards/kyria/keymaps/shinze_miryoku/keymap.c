/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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

#include "keymap_shinze.h"

enum layers { BASE, MBO, MEDR, NAVR, MOUR, NSSL, NSL, FUNL };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
      S00, S01, S02, S03, S04, S05,                         S06, S07, S08, S09, S10, S11,
      S12, S13, S14, S15, S16, S17,                         S18, S19, S20, S21, S22, S23,
      S24, S25, S26, S27, S28, S29, S30, S31,     S32, S33, S34, S35, S36, S37, S38, S39,
                     B01, B02, B03, B04, B05,     B06, B07, B08, B09, B10
    ),

    [MBO] = LAYOUT(
      S00, S01, S02, S03, S04, S05,                         S06, S07, S08, S09, S10, S11,
      S12, S13, S14, S15, S16, S17,                         S18, S19, S20, S21, S22, S23,
      S24, S25, S26, S27, S28, S29, S30, S31,     S32, S33, S34, S35, S36, S37, S38, S39,
                     B01, B02, B03, B04, B05,     B06, B07, B08, B09, B10
    ),

    [MEDR] = LAYOUT(
      S00, S01, S02, S03, S04, S05,                         S06, S07, S08, S09, S10, S11,
      S12, S13, S14, S15, S16, S17,                         S18, S19, S20, S21, S22, S23,
      S24, S25, S26, S27, S28, S29, S30, S31,     S32, S33, S34, S35, S36, S37, S38, S39,
                     B01, B02, B03, B04, B05,     B06, B07, B08, B09, B10
    ),

    [NAVR] = LAYOUT(
      S00, S01, S02, S03, S04, S05,                         S06, S07, S08, S09, S10, S11,
      S12, S13, S14, S15, S16, S17,                         S18, S19, S20, S21, S22, S23,
      S24, S25, S26, S27, S28, S29, S30, S31,     S32, S33, S34, S35, S36, S37, S38, S39,
                     B01, B02, B03, B04, B05,     B06, B07, B08, B09, B10
    ),

    [MOUR] = LAYOUT(
      S00, S01, S02, S03, S04, S05,                         S06, S07, S08, S09, S10, S11,
      S12, S13, S14, S15, S16, S17,                         S18, S19, S20, S21, S22, S23,
      S24, S25, S26, S27, S28, S29, S30, S31,     S32, S33, S34, S35, S36, S37, S38, S39,
                     B01, B02, B03, B04, B05,     B06, B07, B08, B09, B10
    ),

    [NSSL] = LAYOUT(
      S00, S01, S02, S03, S04, S05,                         S06, S07, S08, S09, S10, S11,
      S12, S13, S14, S15, S16, S17,                         S18, S19, S20, S21, S22, S23,
      S24, S25, S26, S27, S28, S29, S30, S31,     S32, S33, S34, S35, S36, S37, S38, S39,
                     B01, B02, B03, B04, B05,     B06, B07, B08, B09, B10
    ),

    [NSL] = LAYOUT(
      S00, S01, S02, S03, S04, S05,                         S06, S07, S08, S09, S10, S11,
      S12, S13, S14, S15, S16, S17,                         S18, S19, S20, S21, S22, S23,
      S24, S25, S26, S27, S28, S29, S30, S31,     S32, S33, S34, S35, S36, S37, S38, S39,
                     B01, B02, B03, B04, B05,     B06, B07, B08, B09, B10
    ),

    [FUNL] = LAYOUT(
      S00, S01, S02, S03, S04, S05,                         S06, S07, S08, S09, S10, S11,
      S12, S13, S14, S15, S16, S17,                         S18, S19, S20, S21, S22, S23,
      S24, S25, S26, S27, S28, S29, S30, S31,     S32, S33, S34, S35, S36, S37, S38, S39,
                     B01, B02, B03, B04, B05,     B06, B07, B08, B09, B10
    ),
};

