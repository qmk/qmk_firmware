// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <board.h>

#undef BOARD_RP_PICO_RP2040
#define BOARD_PM2040

#undef BOARD_NAME
#define BOARD_NAME "Blok"
