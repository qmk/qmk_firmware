// Copyright 2018-2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define HAL_USE_GPT TRUE
#define HAL_USE_PWM TRUE
#define HAL_USE_SPI TRUE
#define HAL_USE_SERIAL TRUE
#define SERIAL_BUFFERS_SIZE 256

// This enables interrupt-driven mode
#define PAL_USE_WAIT TRUE

#include_next <halconf.h>
