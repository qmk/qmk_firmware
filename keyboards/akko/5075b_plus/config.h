// Copyright 2026 rijojohn (@rijojohn85)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* The WS2812 chain hangs off SPIM2's MOSI. WS2812_SPI_DIVISOR is written verbatim
 * into the WB32 SPI BAUDR register, so SCK = PCLK2 / 24 = 4MHz. */
#define WS2812_SPI_DRIVER SPIDM2
#define WS2812_SPI_DIVISOR 24
