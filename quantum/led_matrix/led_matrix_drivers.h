// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>

#if defined(LED_MATRIX_IS31FL3218)
#    include "is31fl3218-mono.h"
#elif defined(LED_MATRIX_IS31FL3731)
#    include "is31fl3731-mono.h"
#elif defined(LED_MATRIX_IS31FL3733)
#    include "is31fl3733-mono.h"
#elif defined(LED_MATRIX_IS31FL3736)
#    include "is31fl3736-mono.h"
#elif defined(LED_MATRIX_IS31FL3737)
#    include "is31fl3737-mono.h"
#elif defined(LED_MATRIX_IS31FL3741)
#    include "is31fl3741-mono.h"
#elif defined(LED_MATRIX_IS31FL3742A)
#    include "is31fl3742a-mono.h"
#elif defined(LED_MATRIX_IS31FL3743A)
#    include "is31fl3743a-mono.h"
#elif defined(LED_MATRIX_IS31FL3745)
#    include "is31fl3745-mono.h"
#elif defined(LED_MATRIX_IS31FL3746A)
#    include "is31fl3746a-mono.h"
#elif defined(LED_MATRIX_SNLED27351)
#    include "snled27351-mono.h"
#endif

typedef struct {
    /* Perform any initialisation required for the other driver functions to work. */
    void (*init)(void);

    /* Set the brightness of a single LED in the buffer. */
    void (*set_value)(int index, uint8_t value);
    /* Set the brightness of all LEDS on the keyboard in the buffer. */
    void (*set_value_all)(uint8_t value);
    /* Flush any buffered changes to the hardware. */
    void (*flush)(void);
} led_matrix_driver_t;

extern const led_matrix_driver_t led_matrix_driver;
