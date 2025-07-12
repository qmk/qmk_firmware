// Copyright 2025 esplo
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "quantum.h"
#include "kb_config.h"

#ifdef OLED_ENABLE
typedef enum _DisplayMode { DisplayMode_Layer, DisplayMode_CONF_0, DisplayMode_CONF_1, DisplayMode_CONF_2, DisplayMode_CONF_3, DisplayMode_CONF_4, DisplayMode_VERSION, DisplayMode_MAX } DisplayMode;
#endif

#ifdef POINTING_DEVICE_ENABLE
#    include "drivers/modular_adns5050.h"
#    define NUM_MODULAR_ADNS5050 ARRAY_SIZE(((pin_t[])MODULAR_ADNS5050_SCLK_PINS))
#    define SCROLL_DIVISOR_H 32.0
#    define SCROLL_DIVISOR_V 32.0
#endif
