/* Copyright 2021 Paul Cotter (@gr1mr3aver)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#include <qp_st77xx.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter ST7789 configurables
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// The number of ST7789 devices we're going to be talking to
#ifndef ST7789_NUM_DEVICES
#    define ST7789_NUM_DEVICES 1
#endif

#ifdef LCD_SPI_MODE
#   undef LCD_SPI_MODE
#endif

#define LCD_SPI_MODE 3

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter ST7789 device factory
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Factory method for an ST7789 device
painter_device_t qp_st7789_make_device(pin_t chip_select_pin, pin_t data_pin, pin_t reset_pin, uint16_t spi_divisor, bool uses_backlight, uint16_t lcd_width, uint16_t lcd_height);
