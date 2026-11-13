// Copyright 2023 Thomas Haukland (@tompi)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Force the usage of PIO1 peripheral, by default the WS2812 implementation uses the PIO0 peripheral.
#define WS2812_PIO_USE_PIO1

// The LED is the one on the RP2040-Zero, and its byte order depends on who
// made the board: Waveshare's is GRB, some clones are RGB. If red and green
// are swapped, use this byte order: WS2812_BYTE_ORDER_GRB
#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_BRG

// The encoder is read from the matrix by a custom driver in cheapino.c.
#define NUM_ENCODERS 1
