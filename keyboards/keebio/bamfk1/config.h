// Copyright 2021 Danny Nguyen (@nooges)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define AUDIO_PIN C6
#ifdef AUDIO_ENABLE
#    define STARTUP_SONG SONG(STARTUP_SOUND)
#endif

#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CYCLE_PINWHEEL
#define RGB_MATRIX_DEFAULT_SPD 48
