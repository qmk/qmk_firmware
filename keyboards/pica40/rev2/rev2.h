// Copyright 2022 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#include "gpio.h"

// RGB LED support for XIAO RP2040
#define PICA40_RGB_POWER_PIN GP11

// enable custom encoder functionality for Pica40
#ifdef ENCODER_ENABLE
#   include "encoder.h"
#   include "transactions.h"
#   ifndef ENCODER_MAP_KEY_DELAY
#       define ENCODER_MAP_KEY_DELAY 2
#   endif
#   ifndef ENCODER_RESOLUTION
#       define ENCODER_RESOLUTION 4
#   endif
#endif
