// Copyright 2023-2025 HorrorTroll <https://github.com/HorrorTroll>
// Copyright 2023-2025 Zhaqian <https://github.com/zhaqian12>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#if !defined(USB_DRIVER)
#    define USB_DRIVER USBD2
#endif

#define BOARD_OTG_VBUSIG

#ifndef EARLY_INIT_PERFORM_BOOTLOADER_JUMP
#    define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE
#endif
