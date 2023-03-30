/* Copyright 2019
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
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

#include "config_common.h"

#define MATRIX_COL_PINS \
    { A3, A2, A5, A4 }
#define MATRIX_ROW_PINS \
    { E8, E7, E10, E9, E12 }

#define ENCODERS_SWITCH B11
#define ENCODERS_PAD_A { E13 }
#define ENCODERS_PAD_B { E15 }

#define I2C_DRIVER I2CD1
#define I2C1_SCL_PIN B8
#define I2C1_SDA_PIN B9
#define I2C1_SCL_PAL_MODE 4
#define I2C1_SDA_PAL_MODE 4
#define I2C1_OPMODE OPMODE_I2C
#define I2C1_CLOCK_SPEED 100000
#define I2C1_DUTY_CYCLE STD_DUTY_CYCLE

#define OLED_INIT setPinInputHigh(B11);

#define RGB_DI_PIN C6

#define WS2812_TRST_US 300

/* From the WS2812B-Mini V3 Docs
T0H 0 220ns~380ns
T1H 1 580ns~1µs
T0L 0 580ns~1µs
T1L 1 580ns~1µs
TRES  > 280µs
*/

//#define WS2812_TIMING	1250
#define WS2812_T0H	380
#define WS2812_T0L	1000
#define WS2812_T1H	1000
#define WS2812_T1L	580

/*
#define WS2812_PWM_DRIVER PWMD3  // default: PWMD2
#define WS2812_PWM_CHANNEL 2  // default: 2
#define WS2812_PWM_PAL_MODE 2  // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 2
//#define WS2812_PWM_COMPLEMENTARY_OUTPUT // Define for a complementary timer output (TIMx_CHyN); omit for a normal timer output (TIMx_CHy).
#define WS2812_DMA_STREAM STM32_DMA1_STREAM2  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#define WS2812_DMA_CHANNEL 2  // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
//#define WS2812_DMAMUX_ID STM32_DMAMUX1_TIM3_UP // DMAMUX configuration for TIMx_UP -- only required if your MCU has a DMAMUX peripheral, see the respective reference manual for the appropriate values for your MCU.
*/


// SPI interface to write to the selected display

#define SPI_DRIVER SPID1 //SPID2
#define SPI_SS_PIN B12
#define SPI_DC_PIN C5
#define SPI_RST_PIN B1
#define SPI_SCK_PIN B3 //B13
#define SPI_SCK_PAL_MODE 3
#define SPI_MOSI_PIN B5 //B15
#define SPI_MOSI_PAL_MODE 5
#define SPI_MISO_PIN B4 //B14
#define SPI_MISO_PAL_MODE 5

// Shift register to select the display
#define SR_NMR_PIN D4
#define SR_CLK_PIN D5
#define SR_DATA_PIN D6
#define SR_LATCH_PIN D7

// KEY_DISPLAYS_VBAT_PIN
#define KEY_DISPLAYS_VBAT_PIN D1
#define KEY_DISPLAYS_VDD_PIN D3
