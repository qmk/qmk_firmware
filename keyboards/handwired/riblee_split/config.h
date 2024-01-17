// Copyright 2023 Daniel Reibl (@riblee)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// If the pin is high, then the controller assumes it is the left hand, and if it’s low, it’s assumed to be the right side.
#define SPLIT_HAND_PIN C15

#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN B6
#define SERIAL_USART_RX_PIN B7
