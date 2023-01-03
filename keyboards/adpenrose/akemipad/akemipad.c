// Copyright 2022 Arturo Avila (@ADPenrose)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "akemipad.h"

#ifdef RGB_MATRIX_ENABLE

/* Setting up the LED matrix */
led_config_t g_led_config = { {
  // Key Matrix to LED Index
  { 0, 1, 2, 3, NO_LED },
  { 4, 5, 6, 7, NO_LED },
  { 8, 9, 10, 11, 12 },
  { 13, 14, 15, 16, NO_LED },
  { 17, 18, 19, 20, 21 },
  { 22, 23, 24, 25, 26 },
}, {
  // LED Index to Physical Position
  {  0,0  }, { 37,0  }, { 74,0  }, {111,0  }, {  0,34 }, { 37,34 }, { 74,34 }, {111,34 }, {  0,62 }, { 37,62 }, 
  { 74,62 }, {111,62 }, {120,75 }, {  0,89 }, { 37,89 }, { 74,89 }, {111,89 }, {  0,117}, { 37,117}, { 74,117}, 
  {111,117}, {120,130}, {  0,137}, { 18,144}, { 37,137}, { 74,144}, {111,144}
}, {
  // LED Index to Flag
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
} };

#endif
