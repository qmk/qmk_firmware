// Copyright 2023 VertorWang (@itarze)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define HAL_USE_SPI TRUE
#define SPI_USE_WAIT TRUE
#define SPI_SELECT_MODE SPI_SELECT_MODE_PAD

#include_next <halconf.h>
