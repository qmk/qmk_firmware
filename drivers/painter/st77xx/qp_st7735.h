// Copyright 2021 Paul Cotter (@gr1mr3aver)
// Copyright 2021 Nick Brassel (@tzarc)
// Copyright 2022 David Hoelscher (@customMK)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include "gpio.h"
#include "qp_internal.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter ST7735 configurables (add to your keyboard's config.h)

#ifndef ST7735_NUM_DEVICES
/**
 * @def This controls the maximum number of ST7735 devices that Quantum Painter can communicate with at any one time.
 *      Increasing this number allows for multiple displays to be used.
 */
#    define ST7735_NUM_DEVICES 1
#endif

// Additional configuration options to be copied to your keyboard's config.h (don't change here):

// If you know exactly which offsets should be used on your panel with respect to selected rotation, then this config
// option allows you to save some flash space -- you'll need to invoke qp_set_viewport_offsets() instead from your keyboard.
//       #define ST7735_NO_AUTOMATIC_VIEWPORT_OFFSETS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter ST7735 device factories

#ifdef QUANTUM_PAINTER_ST7735_SPI_ENABLE
/**
 * Factory method for an ST7735 SPI LCD device.
 *
 * @param panel_width[in] the width of the display panel
 * @param panel_height[in] the height of the display panel
 * @param chip_select_pin[in] the GPIO pin used for SPI chip select
 * @param dc_pin[in] the GPIO pin used for D/C control
 * @param reset_pin[in] the GPIO pin used for RST
 * @param spi_divisor[in] the SPI divisor to use when communicating with the display
 * @param spi_mode[in] the SPI mode to use when communicating with the display
 * @return the device handle used with all drawing routines in Quantum Painter
 */
painter_device_t qp_st7735_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode);
#endif // QUANTUM_PAINTER_ST7735_SPI_ENABLE
