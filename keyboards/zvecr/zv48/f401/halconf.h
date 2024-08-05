// Copyright 2024 zvecr <git@zvecr.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define HAL_USE_PWM TRUE

#define HAL_USE_SERIAL TRUE

#define SERIAL_USB_BUFFERS_SIZE 256

#include_next <halconf.h>
