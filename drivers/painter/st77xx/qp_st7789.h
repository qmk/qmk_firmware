// Copyright 2021 Paul Cotter (@gr1mr3aver)
// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <gpio.h>
#include <qp_internal.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter ST7789 configurables (add to your keyboard's config.h)

// The number of ST7789 devices we're going to be talking to. If you have more than one display you need to increase it.
#ifndef ST7789_NUM_DEVICES
#    define ST7789_NUM_DEVICES 1
#endif

// Additional configuration options to be copied to your keyboard's config.h (don't change here):

// If you know exactly which offsets should be used on your panel with respect to selected rotation, then this config
// option allows you to save some flash space -- you'll need to invoke qp_set_viewport_offsets() instead from your keyboard.
//       #define ST7789_NO_AUTOMATIC_VIEWPORT_OFFSETS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter ST7789 device factories

#ifdef QUANTUM_PAINTER_ST7789_SPI_ENABLE
// Factory method for an ST7789 SPI device
painter_device_t qp_st7789_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode);
#endif  // QUANTUM_PAINTER_ST7789_SPI_ENABLE
