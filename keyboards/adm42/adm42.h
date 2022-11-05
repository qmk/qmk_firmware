/* Copyright 2020-2022 Lorenzo Leonini
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
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

#define LAYOUT_adm42_3x12_6( \
    K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, \
    K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, \
    K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, \
                      K404, K405, K406, K407, K408, K409  \
) { \
    { K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112  }, \
    { K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212  }, \
    { K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312  }, \
    { KC_NO, KC_NO, KC_NO, K404,  K405,  K407,  K406,  K408,  K409,  KC_NO, KC_NO, KC_NO }  \
}
