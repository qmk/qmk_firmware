// Copyright 2023 JZ-Skyloong (@JZ-Skyloong)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define WIN_LOCK_PIN C13

#ifdef ENCODER_ENABLE
#    define ENCODER_MAP_KEY_DELAY 10
#endif

#define MATRIX_ROWS 6
#define MATRIX_COLS 16
#define MATRIX_ROW_PINS {A0, A1, A2, A3, A4, B0}
