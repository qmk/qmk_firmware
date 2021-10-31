/* Copyright 2021 hanachi-ap
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

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
          KA01, KA02, KA03, KA04, KA05, KA06,                   KA10, KA11, KA12, KA13, KA14, KA15, KD14, \
          KB01, KB02, KB03, KB04, KB05, KB06,                   KB10, KB11, KB12, KB13, KB14, KB15, KD15, \
          KC01, KC02, KC03, KC04, KC05, KC06, KC07,       KC09, KC10, KC11, KC12, KC13, KC14, KC15,       \
          KD01,             KD04, KD05, KD06, KD07, KB09, KD09, KD10, KD11, KD12,                         \
          KD02, KD03,                     KA07,KB07,        KA09,KD13                                    \
) { \
        { KA01, KA02, KA03, KA04, KA05, KA06, KA07,      KA09, KA10, KA11, KA12, KA13, KA14, KA15  }, \
        { KB01, KB02, KB03, KB04, KB05, KB06, KB07,      KB09, KB10, KB11, KB12, KB13, KB14, KB15  }, \
        { KC01, KC02, KC03, KC04, KC05, KC06, KC07,      KC09, KC10, KC11, KC12, KC13, KC14, KC15  }, \
        { KD01, KD02, KD03, KD04, KD05, KD06, KD07,      KD09, KD10, KD11, KD12, KD13, KD14, KD15  }  \
}

