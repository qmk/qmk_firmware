/*
 * Copyright 2020 Nick Brassel (tzarc)
 * Copyright 2021 Stefan Kerkmann (@KarlK90)
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#undef STM32_I2C_USE_I2C1
#define STM32_I2C_USE_I2C1 FALSE

//#undef STM32_I2C_I2C1_RX_DMA_STREAM
//#define STM32_I2C_I2C1_RX_DMA_STREAM STM32_DMA_STREAM_ID(1, 0)
//#undef STM32_I2C_I2C1_TX_DMA_STREAM
//#define STM32_I2C_I2C1_TX_DMA_STREAM STM32_DMA_STREAM_ID(1, 1)

#undef STM32_PWM_USE_TIM2
#define STM32_PWM_USE_TIM2 TRUE

//#undef STM32_PWM_USE_TIM3
//#define STM32_PWM_USE_TIM3 TRUE

#undef STM32_SPI_USE_SPI1
#define STM32_SPI_USE_SPI1 TRUE

//#undef STM32_SPI_SPI1_RX_DMA_STREAM
//#define STM32_SPI_SPI1_RX_DMA_STREAM STM32_DMA_STREAM_ID(2, 0)
//#undef STM32_SPI_SPI1_TX_DMA_STREAM
//#define STM32_SPI_SPI1_TX_DMA_STREAM STM32_DMA_STREAM_ID(2, 3)

#undef STM32_SERIAL_USE_USART1
#define STM32_SERIAL_USE_USART1 TRUE

//#undef STM32_SERIAL_USE_USART2
//#define STM32_SERIAL_USE_USART2 TRUE

//#undef STM32_UART_USART2_RX_DMA_STREAM
//#define STM32_UART_USART2_RX_DMA_STREAM STM32_DMA_STREAM_ID(1, 5)
//#undef STM32_UART_USART2_TX_DMA_STREAM
//#define STM32_UART_USART2_TX_DMA_STREAM STM32_DMA_STREAM_ID(1, 6)

#undef STM32_GPT_USE_TIM3
#define STM32_GPT_USE_TIM3 TRUE

#undef STM32_ST_USE_TIMER
#define STM32_ST_USE_TIMER 5
