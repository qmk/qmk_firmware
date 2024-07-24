// Copyright 2024 customMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define HAL_USE_SPI TRUE

#define SPI_SELECT_MODE SPI_SELECT_MODE_PAD

#define SERIAL_BUFFERS_SIZE 256

#define SPI_USE_WAIT TRUE

#include_next <halconf.h>
