// Copyright 2022 Pablo Martinez (@elpekenin)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "gpio.h"
#include "qp_internal.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter IL91874_NUM_DEVICES configurables (add to your keyboard's config.h)

#ifndef IL91874_NUM_DEVICES
/**
 * @def This controls the maximum number of IL91874_NUM_DEVICES devices that Quantum Painter can communicate with at any one time.
 *      Increasing this number allows for multiple displays to be used.
 */
#    define IL91874_NUM_DEVICES 1
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter IL91874_NUM_DEVICES device factories

#ifdef QUANTUM_PAINTER_IL91874_SPI_ENABLE
/**
 * Factory method for an IL91874 SPI LCD device.
 *
 * @param panel_width[in] the width of the display panel
 * @param panel_height[in] the height of the display panel
 * @param chip_select_pin[in] the GPIO pin used for SPI chip select
 * @param dc_pin[in] the GPIO pin used for D/C control
 * @param reset_pin[in] the GPIO pin used for RST
 * @param spi_divisor[in] the SPI divisor to use when communicating with the display
 * @param spi_mode[in] the SPI mode to use when communicating with the display
 * @param ptr[in] the array in which pixel data is stored
 * @return the device handle used with all drawing routines in Quantum Painter
 */
painter_device_t qp_il91874_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode, void *ptr);

#endif // QUANTUM_PAINTER_IL91874_SPI_ENABLE
