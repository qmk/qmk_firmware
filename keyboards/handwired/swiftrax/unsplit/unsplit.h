/*
Copyright 2020 Swiftrax <swiftrax@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "quantum.h"

// readability
#define XXX KC_NO

#define LAYOUT( \
    K000, K001, K002, K003, K004, K005,                               K011, K012, K013, K014, K015, K016, \
    K100, K101, K102, K103, K104, K105,                               K111, K112, K113, K114, K115, K116, \
    K200, K201, K202, K203, K204, K205,                               K211, K212, K213, K214, K215, K216, \
                K402, K403, K404, K405,                               K411, K412, K413, K414  \
) { \
    { K000,  K001,  K002,  K003,  K004,  K005,  K011,  K012,  K013,  K014,  K015,  K016 }, \
    { K100,  K101,  K102,  K103,  K104,  K105,  K111,  K112,  K113,  K114,  K115,  K116 }, \
    { K200,  K201,  K202,  K203,  K204,  K205,  K211,  K212,  K213,  K214,  K215,  K216 }, \
    { XXX,    XXX,  K402,  K403,  K404,  K405,  K411,  K412,  K413,  K414,   XXX,   XXX }  \
}
