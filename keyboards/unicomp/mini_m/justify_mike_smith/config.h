/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define DEF_SERIAL_NUMBER "purdea.ro:justify_mike_smith"

#ifndef SERIAL_NUMBER
#define SERIAL_NUMBER DEF_SERIAL_NUMBER
#endif

#define MATRIX_ROWS 12
#define MATRIX_COLS 16

#define WEAR_LEVELING_LOGICAL_SIZE 16384
#define WEAR_LEVELING_BACKING_SIZE (WEAR_LEVELING_LOGICAL_SIZE * 2)

// with eager debouncing the default is not good enough:
#define DEBOUNCE 10
