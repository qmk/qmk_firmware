/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define DEF_SERIAL_NUMBER "purdea.ro:aristides_2862"

#ifndef SERIAL_NUMBER
#define SERIAL_NUMBER DEF_SERIAL_NUMBER
#endif

#define MATRIX_ROWS 8
#define MATRIX_COLS 16

#define WEAR_LEVELING_LOGICAL_SIZE 16384
#define WEAR_LEVELING_BACKING_SIZE (WEAR_LEVELING_LOGICAL_SIZE * 2)
