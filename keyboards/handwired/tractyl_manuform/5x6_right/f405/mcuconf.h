/* Copyright 2020 Nick Brassel (tzarc)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include_next <mcuconf.h>

#undef STM32_LSE_ENABLED
#define STM32_LSE_ENABLED TRUE

#undef STM32_PLLM_VALUE
#define STM32_PLLM_VALUE 8

#undef STM32_RTCSEL
#define STM32_RTCSEL STM32_RTCSEL_LSE

#undef STM32_SERIAL_USE_USART1
#define STM32_SERIAL_USE_USART1 TRUE

#if HAL_USE_WDG == TRUE
#    undef STM32_WDG_USE_IWDG
#    define STM32_WDG_USE_IWDG TRUE
#endif

#if HAL_USE_I2C == TRUE
#    undef STM32_I2C_USE_I2C1
#    define STM32_I2C_USE_I2C1 TRUE

#    undef STM32_I2C_BUSY_TIMEOUT
#    define STM32_I2C_BUSY_TIMEOUT 10

#    undef STM32_I2C_I2C1_RX_DMA_STREAM
#    define STM32_I2C_I2C1_RX_DMA_STREAM STM32_DMA_STREAM_ID(1, 0)
#    undef STM32_I2C_I2C1_TX_DMA_STREAM
#    define STM32_I2C_I2C1_TX_DMA_STREAM STM32_DMA_STREAM_ID(1, 7)
#endif // HAL_USE_I2C

#ifdef WS2812_PWM
#    undef STM32_PWM_USE_TIM3
#    define STM32_PWM_USE_TIM3 TRUE
#endif // WS2812_PWM

#ifdef BACKLIGHT_PWM
#    undef STM32_PWM_USE_TIM8
#    define STM32_PWM_USE_TIM8 TRUE
#endif

#if HAL_USE_SPI == TRUE
#    undef STM32_SPI_USE_SPI1
#    define STM32_SPI_USE_SPI1 TRUE
#endif

#ifdef AUDIO_DRIVER_DAC
#    undef STM32_DAC_USE_DAC1_CH1
#    define STM32_DAC_USE_DAC1_CH1 TRUE
#    undef STM32_DAC_USE_DAC1_CH2
#    define STM32_DAC_USE_DAC1_CH2 TRUE

#    undef STM32_GPT_USE_TIM6
#    define STM32_GPT_USE_TIM6 TRUE
#endif // AUDIO_DRIVER_DAC


#ifdef USE_USB_OTG_HS_PORT
#    undef STM32_USB_USE_OTG1
#    define STM32_USB_USE_OTG1 FALSE
#    undef STM32_USB_USE_OTG2
#    define STM32_USB_USE_OTG2 TRUE
#endif
