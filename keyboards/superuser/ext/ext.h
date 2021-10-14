/* Copyright 2021 superuser
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

#define LAYOUT_tkl(\
    KF10, KF11, K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K312,    K114, K115, K116,  \
    KF20, KF21, K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213,          K214, K215, K216,  \
    KF30, KF31, K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311,       K313,                             \
    KF40, KF41, K400, K401, K402, K403, K404, K405, K406, K407, K408, K409, K410, K411, K412, K413,                K415,        \
    KF50, KF51, K500, K501, K502,                   K506,                         K511, K512, K513,          K514, K515, K516   \
) { \
    { KF10,  KF11,  K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  K114,  K115,  K116  }, \
    { KF20,  KF21,  K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  K213,  K214,  K215,  K216  }, \
    { KF30,  KF31,  K300,  K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313,  KC_NO, KC_NO, KC_NO }, \
    { KF40,  KF41,  K400,  K401,  K402,  K403,  K404,  K405,  K406,  K407,  K408,  K409,  K410,  K411,  K412,  K413,  KC_NO, K415,  KC_NO }, \
    { KF50,  KF51,  K500,  K501,  K502,  KC_NO, KC_NO, KC_NO, K506,  KC_NO, KC_NO, KC_NO, KC_NO, K511,  K512,  K513,  K514,  K515,  K516  }  \
}
