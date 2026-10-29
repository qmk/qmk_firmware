// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define HAL_USE_PWM TRUE
#define SERIAL_USB_BUFFERS_SIZE 256
#define HAL_USE_SERIAL TRUE

#include_next <halconf.h>
