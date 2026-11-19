// Copyright 2026 rijojohn
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef WB32_SPI_USE_SPIM2
#define WB32_SPI_USE_SPIM2 TRUE

/* The WS2812 stream is clocked out at 4MHz from an interrupt-refilled TX FIFO.
 * If the refill is ever late by more than ~50us the LEDs see a reset and restart
 * the frame at pixel 1, so this ISR has to outrank the other peripherals. */
#undef WB32_SPI_SPIM2_IRQ_PRIORITY
#define WB32_SPI_SPIM2_IRQ_PRIORITY 3
