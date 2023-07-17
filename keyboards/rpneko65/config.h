// Copyright 2023 lendunistus (@lendunistus)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define WS2812_DI_PIN GP18
#define RGB_MATRIX_LED_COUNT 1
#define WS2812_PIO_USE_PIO1 // Force the usage of PIO1 peripheral, by default the WS2812 implementation uses the PIO0 peripheral
