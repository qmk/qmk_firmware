// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "gpio.h"
#include "qp_internal.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter ILI9163 configurables (add to your keyboard's config.h)

// The number of ILI9163 devices we're going to be talking to. If you have more than one display you need to increase it.
#ifndef ILI9163_NUM_DEVICES
#    define ILI9163_NUM_DEVICES 1
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter ILI9163 device factories

#ifdef QUANTUM_PAINTER_ILI9163_SPI_ENABLE
// Factory method for an ILI9163 SPI device
painter_device_t qp_ili9163_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode);
#endif  // QUANTUM_PAINTER_ILI9163_SPI_ENABLE
