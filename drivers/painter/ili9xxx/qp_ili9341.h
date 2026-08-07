// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include "gpio.h"
#include "qp_internal.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter ILI9341 configurables (add to your keyboard's config.h)

#ifndef ILI9341_NUM_DEVICES
/**
 * @def This controls the maximum number of ILI9341 devices that Quantum Painter can communicate with at any one time.
 *      Increasing this number allows for multiple displays to be used.
 */
#    define ILI9341_NUM_DEVICES 1
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter ILI9341 device factories

#ifdef QUANTUM_PAINTER_ILI9341_SPI_ENABLE
/**
 * Factory method for an ILI9341 SPI LCD device.
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
painter_device_t qp_ili9341_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode);
#endif // QUANTUM_PAINTER_ILI9341_SPI_ENABLE
