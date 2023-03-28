// Copyright 2022 Stefan Kerkmann
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <board.h>

#undef BOARD_RP_PICO_RP2040
#define BOARD_GENERIC_RP2040

#undef BOARD_NAME
#define BOARD_NAME "Generic Raspberry Pi RP2040"
