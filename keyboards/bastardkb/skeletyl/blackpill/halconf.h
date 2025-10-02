// Copyright 2020 Nick Brassel (tzarc)
// Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define HAL_USE_PWM TRUE
#define HAL_USE_SERIAL TRUE
//#define HAL_USE_I2C     TRUE
//#define HAL_USE_SPI TRUE
//#define SPI_USE_WAIT TRUE
//#define SPI_SELECT_MODE SPI_SELECT_MODE_PAD
//#define HAL_USE_GPT TRUE

#include_next <halconf.h>
