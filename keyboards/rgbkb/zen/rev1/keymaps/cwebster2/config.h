/*
Copyright 2020 Casey Webster <casey@e1337.dev>

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

#include "config_common.h"

/* Use I2C or Serial, not both */

#define USE_SERIAL

#define EE_HANDS

#ifdef COMBO_ENABLE
  #define COMBO_COUNT 2
#endif

#define QMK_KEYS_PER_SCAN 4

#define EE_HANDS
