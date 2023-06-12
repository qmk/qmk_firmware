 /* Copyright 2020 Álvaro "Gondolindrim" Volpato <gondolindrim@acheronproject.com>
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
  */

#pragma once

#include "m80v1.h"

#define LAYOUT_tkl_ansi( \
    K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  K415,  K114, K115,  K116, \
    K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  K213,         K214, K215,  K216, \
    K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313,  K514,  K314, K315,  K316, \
    K401,  K402,  K403,  K404,  K405,  K406,  K407,  K408,  K409,  K410,  K411,  K412,  K413,                            \
    K501,  K502,  K503,  K504,  K505,  K506,  K507,  K508,  K509,  K510,  K511,  K512,                      K515,        \
    K601,  K602,  K603,                       K607,                K610,  K611,  K612,  K613,         K614, K615,  K616  \
) { \
    { K101,   K102,   K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  K114 , K115,  K116 },  \
    { K201,   K202,   K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  K213,  K214 , K215,  K216 },  \
    { K301,   K302,   K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313,  K314 , K315,  K316 },  \
    { K401,   K402,   K403,  K404,  K405,  K406,  K407,  K408,  K409,  K410,  K411,  K412,  K413,  KC_NO, K415 , KC_NO }, \
    { K501,   K502,   K503,  K504,  K505,  K506,  K507,  K508,  K509,  K510,  K511,  K512,  KC_NO, K514 , K515,  KC_NO }, \
    { K601,   K602,   K603,  KC_NO, KC_NO, KC_NO, K607,  KC_NO, KC_NO, K610,  K611,  K612,  K613,  K614 , K615,  K616 }   \
}
