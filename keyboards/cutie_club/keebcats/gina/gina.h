/*
Copyright 2023 Cutie Club

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

typedef union {
  uint32_t raw;
  struct {
    uint8_t indicator_key: 8;
  };
} keyboard_config_t;

#define LAYOUT_right_all( \
    k00_00, k00_01, k00_02, k00_03, k00_04, \
    k01_00, k01_01, k01_02, k01_03, k01_04, \
    k02_00, k02_01, k02_02, k02_03, k02_04, \
    k03_00, k03_01, k03_02, k03_03, k03_04, \
    k04_00, k04_01, k04_02, k04_03, k04_04  \
) \
{ \
    { k00_00, k00_01, k00_02, k00_03, k00_04 }, \
    { k01_00, k01_01, k01_02, k01_03, k01_04 }, \
    { k02_00, k02_01, k02_02, k02_03, k02_04 }, \
    { k03_00, k03_01, k03_02, k03_03, k03_04 }, \
    { k04_00, k04_01, k04_02, k04_03, k04_04 }  \
}

#define LAYOUT_left_all( \
    k00_00, k00_01, k00_02, k00_03, k00_04, \
    k01_00, k01_01, k01_02, k01_03, k01_04, \
    k02_00, k02_01, k02_02, k02_03, k02_04, \
    k03_00, k03_01, k03_02, k03_03, k03_04, \
    k04_00, k04_01, k04_02, k04_03, k04_04  \
) \
{ \
    { k00_04, k00_03, k00_02, k00_01, k00_00 }, \
    { k01_04, k01_03, k01_02, k01_01, k01_00 }, \
    { k02_00, k02_01, k02_02, k02_03, k02_04 }, \
    { k02_04, k02_03, k02_02, k02_01, k02_00 }, \
    { k04_04, k04_03, k04_02, k04_01, k04_00 }  \
}

#define LAYOUT_left_all( \
    k00_00, k00_01, k00_02, k00_03, k00_04, \
    k01_00, k01_01, k01_02, k01_03, k01_04, \
    k02_00, k02_01, k02_02, k02_03, k02_04, \
    k03_00, k03_01, k03_02, k03_03, k03_04, \
    k04_00, k04_01, k04_02, k04_03, k04_04  \
) \
{ \
    { k00_04, k00_03, k00_02, k00_01, k00_00 }, \
    { k01_04, k01_03, k01_02, k01_01, k01_00 }, \
    { k02_00, k02_01, k02_02, k02_03, k02_04 }, \
    { k02_04, k02_03, k02_02, k02_01, k02_00 }, \
    { k04_04, k04_03, k04_02, k04_01, k04_00 }  \
}
