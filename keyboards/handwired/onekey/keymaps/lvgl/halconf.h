// Copyright 2022 Jose Pablo Ramirez (@jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <halconf.h>

#undef HAL_USE_SPI
#define HAL_USE_SPI TRUE

#undef SPI_USE_WAIT
#define SPI_USE_WAIT TRUE
