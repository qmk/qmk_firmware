// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define HAL_USE_SERIAL TRUE

#define HAL_USE_I2C TRUE

// This enables interrupt-driven mode
#define PAL_USE_WAIT TRUE
#define USB_USE_WAIT TRUE

#include_next <halconf.h>
