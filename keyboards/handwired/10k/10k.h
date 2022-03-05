/*
Copyright 2022 Nabos <nabos at glargh dot fr>

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

#define LAYOUT_1x5(\
    L00, L01, L02, L03, L04,     R04, R03, R02, R01, R00 \
    )\
    {\
        { L00, L01 , L02, L03, L04 },     \
\
        { R00, R01 , R02, R03, R04 }    \
}
