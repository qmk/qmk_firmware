// Copyright 2023 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define DEBUG_MATRIX_SCAN_RATE // only want api

#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP18
#define SPI_MOSI_PIN GP19
#define SPI_MISO_PIN GP16

#define DISPLAY_RST GP15
#define DISPLAY_CS GP21
#define DISPLAY_DC GP20

#define QUANTUM_PAINTER_SUPPORTS_256_PALETTE true
