// Copyright 2023 Gustaw.xyz (@Gustaw.xyz)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP9
#define SERIAL_USART_RX_PIN GP8
#define SPLIT_HAND_PIN GP22

// Fix not working after reboot in USB HUB https://github.com/qmk/qmk_firmware/issues/22477
#define SPLIT_WATCHDOG_ENABLE
