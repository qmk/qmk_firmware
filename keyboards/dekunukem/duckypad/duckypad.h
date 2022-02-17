/*

QMK Firmware for dekuNukem/duckyPad

Copyright (C) 2020 Anthony Som

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
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

#define LAYOUT( \
    k00, k01, k02, \
    k03, k04, k05, \
    k06, k07, k08, \
    k09, k010, k011, \
    k012, k013, k014, \
    k015, k016 \
) {{k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k010, k011, k012, k013, k014, k015, k016}}
