// Copyright 2022 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next "board.h"

#undef STM32_HSECLK
#define STM32_HSECLK 16000000
