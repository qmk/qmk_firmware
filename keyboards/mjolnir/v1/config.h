// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#define SERIAL_USART_FULL_DUPLEX   // Enable full duplex operation mode.
#define SERIAL_USART_TX_PIN GP0    // USART TX pin
#define SERIAL_USART_RX_PIN GP1    // USART RX pin

// possibly fix KB  not working at boot time
#define SPLIT_USB_TIMEOUT 10000
#define SPLIT_USB_TIMEOUT_POLL 10
