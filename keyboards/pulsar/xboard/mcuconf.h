/* Copyright 2020 QMK
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

#include_next <mcuconf.h>

/* enable TIM1, used for backlight PWM */
//#undef STM32_PWM_USE_TIM1
//#define STM32_PWM_USE_TIM1                  TRUE

/* enable TIM2, used for underglow PWM driver */
//#undef STM32_PWM_USE_TIM2
//#define STM32_PWM_USE_TIM2                  TRUE

#undef STM32_GPT_USE_TIM3
#define STM32_GPT_USE_TIM3                  TRUE

/* enable SPI2, used for WS2812underglow(RGB BackLight)/WS2812 RGB-Matrix SPI driver, PIN B15 */
#undef STM32_SPI_USE_SPI2
#define STM32_SPI_USE_SPI2 TRUE

/* enable I2C1, used for OLED & 3731 LED Driver, PIN B6 B7 */
#undef STM32_I2C_USE_I2C1
#define STM32_I2C_USE_I2C1 TRUE
#undef STM32_I2C_USE_DMA
#define STM32_I2C_USE_DMA TRUE      //FALSE

// < for STM32F072 >
#undef STM32_I2C_I2C1_RX_DMA_STREAM
#undef STM32_I2C_I2C1_TX_DMA_STREAM
#define STM32_I2C_I2C1_RX_DMA_STREAM STM32_DMA_STREAM_ID(1, 3)  // 7
#define STM32_I2C_I2C1_TX_DMA_STREAM STM32_DMA_STREAM_ID(1, 2)  // 6


#undef STM32_ADC_USE_ADC1
#define STM32_ADC_USE_ADC1 TRUE
#define STM32_ADC_ADC1_CKMODE               STM32_ADC_CKMODE_ADCCLK
#define STM32_ADC_ADC1_DMA_STREAM           STM32_DMA_STREAM_ID(1, 1)
//#define STM32_ADC_ADC1_DMA_STREAM           STM32_DMA_STREAM_ID_ANY
