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

#define RP2040

#define MATRIX_COL_PINS \
    { GP10, GP11, GP12, GP13, GP14, GP15, GP16, GP3 }
#define MATRIX_ROW_PINS \
    { GP18, GP19, GP20, GP21, GP22 }

#define I2C_DRIVER I2CD1
#define I2C1_SCL_PIN GP0
#define I2C1_SDA_PIN GP1
//#define I2C1_SCL_PAL_MODE 4
//#define I2C1_SDA_PAL_MODE 4
#define I2C1_OPMODE OPMODE_I2C
#define I2C1_CLOCK_SPEED 100000
#define I2C1_DUTY_CYCLE STD_DUTY_CYCLE

#define OLED_INIT

#define RGB_DI_PIN GP2

/* From the WS2812B-Mini V3 Docs: https://datasheet.lcsc.com/szlcsc/2005251033_Worldsemi-WS2812B-Mini_C527089.pdf
T0H 0 220ns~380ns
T1H 1 580ns~1µs
T0L 0 580ns~1µs
T1L 1 580ns~1µs
TRES  > 280µs
*/

//#define WS2812_TIMING	1250
//#define WS2812_T0H	320
//#define WS2812_T0L	700
//#define WS2812_T1H	700
//#define WS2812_T1L	700
//#define WS2812_TRST_US 300
//WS2812_T0L < (50 + WS2812_T1L)?

#define NOP_FUDGE 0.4
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

#define SPI_DRIVER SPID0
#define SPI_SS_PIN GP17
#define SPI_DC_PIN GP8
#define HW_RST_PIN GP9
#define SPI_SCK_PIN GP6
//#define SPI_SCK_PAL_MODE 5
#define SPI_MOSI_PIN GP7
//#define SPI_MOSI_PAL_MODE 5
#define SPI_MISO_PIN GP4 //can be used as uart tx as well?

//This number can be calculated by dividing the MCU’s clock speed
//by the desired SPI clock speed. For example, an MCU running at 8 MHz
//wanting to talk to an SPI device at 4 MHz would set the divisor to 2
//#define SPI_DIVISOR (CPU_CLOCK / 1000000) //rp1040 runs at 133Mhz, SPI at 16Mhz (for new Board)
#define SPI_DIVISOR (CPU_CLOCK / 16000000) //rp1040 runs at 133Mhz, SPI at 16Mhz
//#define SPI_MISO_PAL_MODE 5

// Shift register to select the display
//#define SR_NMR_PIN //NO_PIN if possible
#define SR_CLK_PIN GP27
#define SR_DATA_PIN GP26
#define SR_LATCH_PIN GP28

// KEY_DISPLAYS_VBAT_PIN
//#define KEY_DISPLAYS_VBAT_PIN NO_PIN
//#define KEY_DISPLAYS_VDD_PIN NO_PIN

/* Reset. */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
//#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U

//#define ENCODERS_PAD_A { }
//#define ENCODERS_PAD_B { }
//#define ENCODER_RESOLUTIONS { }
//#define ENCODERS_PAD_A_LEFT { GP25 }
//#define ENCODERS_PAD_B_LEFT { GP29 }
//#define ENCODER_RESOLUTIONS_LEFT { 2 }
#define ENCODERS_PAD_A { GP25 }
#define ENCODERS_PAD_B { GP29 }
#define ENCODER_RESOLUTION 4

/*
#define ENCODERS_PAD_A { 0 }
#define ENCODERS_PAD_B { 1 }
#define ENCODER_RESOLUTION 1
*/
//#define CUSTOM_PROCESS_RECORD_USER
