/*
    ChibiOS - Copyright (C) 2006..2015 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#pragma once

#include_next <mcuconf.h>

#undef STM32_I2C_USE_I2C1
#define STM32_I2C_USE_I2C1 TRUE

#if 1
#undef STM32_SPI_USE_SPI2
#define STM32_SPI_USE_SPI2 TRUE
#endif

#if 0
#undef STM32_SERIAL_USE_USART0
#define STM32_SERIAL_USE_USART0 TRUE
#define STM32_USART0_IRQ_PRIORITY 6

#undef STM32_SERIAL_USE_USART1
#define STM32_SERIAL_USE_USART1 TRUE
#define STM32_USART1_IRQ_PRIORITY 7
#endif
