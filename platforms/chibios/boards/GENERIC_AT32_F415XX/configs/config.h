// Copyright 2023-2024 HorrorTroll <https://github.com/HorrorTroll>
// Copyright 2023-2024 Zhaqian <https://github.com/zhaqian12>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define BOARD_OTG_VBUSIG

#define USB_ENDPOINTS_ARE_REORDERABLE

#ifndef EARLY_INIT_PERFORM_BOOTLOADER_JUMP
#    define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE
#endif
