// Copyright 2022 KnoblesseOblige (@KnoblesseOblige)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID    0xAE7E
#define PRODUCT_ID   0x5057 /* "PW" */
#define DEVICE_VER   0x0001
#define MANUFACTURER Aeternus
#define PRODUCT      Paw

#define MATRIX_ROWS 1
#define MATRIX_COLS 4

#define DIRECT_PINS { { D6, D5, D4, D3 } }
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN B2
#ifdef RGB_DI_PIN
#    define RGBLED_NUM 4
#    define RGBLIGHT_ANIMATIONS
#endif

#define DEBOUNCE 5

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
