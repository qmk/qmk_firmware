// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>

#if defined(RGB_MATRIX_AW20216S)
#    include "aw20216s.h"
#elif defined(RGB_MATRIX_IS31FL3218)
#    include "is31fl3218.h"
#elif defined(RGB_MATRIX_IS31FL3731)
#    include "is31fl3731.h"
#elif defined(RGB_MATRIX_IS31FL3733)
#    include "is31fl3733.h"
#elif defined(RGB_MATRIX_IS31FL3736)
#    include "is31fl3736.h"
#elif defined(RGB_MATRIX_IS31FL3737)
#    include "is31fl3737.h"
#elif defined(RGB_MATRIX_IS31FL3741)
#    include "is31fl3741.h"
#elif defined(RGB_MATRIX_IS31FL3742A)
#    include "is31fl3742a.h"
#elif defined(RGB_MATRIX_IS31FL3743A)
#    include "is31fl3743a.h"
#elif defined(IS31FLCOMMON)
#    include "is31flcommon.h"
#elif defined(RGB_MATRIX_SNLED27351)
#    include "snled27351.h"
#elif defined(RGB_MATRIX_WS2812)
#    include "ws2812.h"
#endif

typedef struct {
    /* Perform any initialisation required for the other driver functions to work. */
    void (*init)(void);
    /* Set the colour of a single LED in the buffer. */
    void (*set_color)(int index, uint8_t r, uint8_t g, uint8_t b);
    /* Set the colour of all LEDS on the keyboard in the buffer. */
    void (*set_color_all)(uint8_t r, uint8_t g, uint8_t b);
    /* Flush any buffered changes to the hardware. */
    void (*flush)(void);
} rgb_matrix_driver_t;

extern const rgb_matrix_driver_t rgb_matrix_driver;
