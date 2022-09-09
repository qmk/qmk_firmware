// Copyright 2022 Takeshi Noda (nodatk@gmail.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 14

#define MATRIX_ROW_PINS { B7, B6, B5, B4 }
#define MATRIX_COL_PINS { A2, A1, A0, B8 , B13, B14, B15, B9, B10, B11, B3, B2, B1, B0}

#define DIODE_DIRECTION COL2ROW

#define DEBOUNCE 8
#define TAPPING_TERM 150

#define FORCE_NKRO

#ifdef AUDIO_ENABLE
  #define AUDIO_PIN A5
  #define AUDIO_PIN_ALT A4
  #define AUDIO_PIN_ALT_AS_NEGATIVE
  #define STARTUP_SONG SONG(STARTUP_SOUND)
  #define AUDIO_INIT_DELAY
#endif
