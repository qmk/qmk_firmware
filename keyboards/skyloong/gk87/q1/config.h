// Copyright 2023 JZ-Skyloong (@JZ-Skyloong)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define WIN_LOCK_PIN C13

#define ENCODER_MAP_KEY_DELAY 10

#define AW20216S_CS_PIN_1 B12
#define AW20216S_CS_PIN_2 B11
// Hardware enable lines may be connected to the same pin
#define AW20216S_EN_PIN B10

#define NUM_LOCK_INDEX 33
#define WIN_MOD_INDEX 22
#define MAC_MOD_INDEX 23
#define WIN_LOCK_INDEX 93
#define CAPS_LOCK_INDEX 58
#define SCR_LOCK_INDEX 14

#define MATRIX_ROWS 6
#define MATRIX_COLS 16
#define MATRIX_ROW_PINS {A0, A1, A2, A3, A4, B0}
