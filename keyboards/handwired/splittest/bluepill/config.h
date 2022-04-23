// Copyright 2022 dvermd (@dvermd)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

#define BLUEPILL

// wiring of each half
#define MATRIX_ROW_PINS { B10 }
#define MATRIX_COL_PINS { B1 }

#define SPLIT_HAND_PIN A7
#define FORCED_SYNC_THROTTLE_MS 100

#define SELECT_SOFT_SERIAL_SPEED 1 // or 0, 2, 3, 4, 5
                                   //  0: about 189kbps (Experimental only)
                                   //  1: about 137kbps (default)
                                   //  2: about 75kbps
                                   //  3: about 39kbps
                                   //  4: about 26kbps
                                   //  5: about 20kbps


#if !(defined(USE_SDI1_ON_STANDARD_ROLE_PINS) || defined(USE_SDI1_ON_ALTERNATE_ROLE_PINS) || defined(USE_SDI2))
    #define USE_SDI1_ON_STANDARD_ROLE_PINS
#endif