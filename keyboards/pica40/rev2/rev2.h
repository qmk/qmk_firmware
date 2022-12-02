// Copyright 2022 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// RGB LED support for XIAO RP2040
#define PICA40_RGB_POWER_PIN GP11

// enable custom encoder functionality for Pica40
#ifdef PICA40_ENCODER_SYNC_ENABLE
#   include "transactions.h"
#   define PICA40_ENCODER_PIN GP7
#   ifndef ENCODER_RESOLUTION
#       define ENCODER_RESOLUTION 4
#   endif
#endif
