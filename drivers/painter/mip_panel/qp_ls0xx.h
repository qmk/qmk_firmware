// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "gpio.h"
#include "qp_internal.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter ILI9163 configurables (add to your keyboard's config.h)

#ifndef LS0XX_NUM_DEVICES
/**
 * @def This controls the maximum number of LS0XX devices that Quantum Painter can communicate with at any one time.
 *      Increasing this number allows for multiple displays to be used.
 */
#    define LS0XX_NUM_DEVICES 1
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter ILI9163 device factories

#ifdef QUANTUM_PAINTER_LS0XX_SPI_ENABLE
/**
 * Factory method for an LS0XX MIP SPI device.
 *
 * @param panel_width[in] the width of the display panel
 * @param panel_height[in] the height of the display panel
 * @param chip_select_pin[in] the GPIO pin used for SPI chip select
 * @param spi_divisor[in] the SPI divisor to use when communicating with the display
 * @param spi_mode[in] the SPI mode to use when communicating with the display
 * @param buf[in] the address of the buffer where data will be stored
 * @return the device handle used with all drawing routines in Quantum Painter
 */
painter_device_t qp_ls0xx_device_t_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, uint16_t spi_divisor, int spi_mode, void *buf);
#endif // QUANTUM_PAINTER_LS0XX_SPI_ENABLE
