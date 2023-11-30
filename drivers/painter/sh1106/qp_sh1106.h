// Copyright 2023 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include "gpio.h"
#include "qp_internal.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter SH1106 configurables (add to your keyboard's config.h)

#if defined(QUANTUM_PAINTER_SH1106_SPI_ENABLE) && !defined(SH1106_NUM_SPI_DEVICES)
/**
 * @def This controls the maximum number of SPI SH1106 devices that Quantum Painter can communicate with at any one time.
 *      Increasing this number allows for multiple displays to be used.
 */
#    define SH1106_NUM_SPI_DEVICES 1
#else
#    define SH1106_NUM_SPI_DEVICES 0
#endif

#if defined(QUANTUM_PAINTER_SH1106_I2C_ENABLE) && !defined(SH1106_NUM_I2C_DEVICES)
/**
 * @def This controls the maximum number of I2C SH1106 devices that Quantum Painter can communicate with at any one time.
 *      Increasing this number allows for multiple displays to be used.
 */
#    define SH1106_NUM_I2C_DEVICES 1
#else
#    define SH1106_NUM_I2C_DEVICES 0
#endif

#define SH1106_NUM_DEVICES ((SH1106_NUM_SPI_DEVICES) + (SH1106_NUM_I2C_DEVICES))

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter SH1106 device factories

#ifdef QUANTUM_PAINTER_SH1106_SPI_ENABLE

/**
 * Factory method for an SH1106 SPI LCD device.
 *
 * @param panel_width[in] the width of the display in pixels (usually 128)
 * @param panel_height[in] the height of the display in pixels (usually 64)
 * @param chip_select_pin[in] the GPIO pin used for SPI chip select
 * @param dc_pin[in] the GPIO pin used for D/C control
 * @param reset_pin[in] the GPIO pin used for RST
 * @param spi_divisor[in] the SPI divisor to use when communicating with the display
 * @param spi_mode[in] the SPI mode to use when communicating with the display
 * @return the device handle used with all drawing routines in Quantum Painter
 */
painter_device_t qp_sh1106_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode);

#endif // QUANTUM_PAINTER_SH1106_SPI_ENABLE

#ifdef QUANTUM_PAINTER_SH1106_I2C_ENABLE

/**
 * Factory method for an SH1106 I2C LCD device.
 *
 * @param panel_width[in] the width of the display in pixels (usually 128)
 * @param panel_height[in] the height of the display in pixels (usually 64)
 * @param i2c_address[in] the I2C address to use
 * @return the device handle used with all drawing routines in Quantum Painter
 */
painter_device_t qp_sh1106_make_i2c_device(uint16_t panel_width, uint16_t panel_height, uint8_t i2c_address);

#endif // QUANTUM_PAINTER_SH1106_I2C_ENABLE
