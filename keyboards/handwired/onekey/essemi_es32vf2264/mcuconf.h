/*
    Copyright (C) 2021 essemi

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

#ifndef MCUCONF_H
#define MCUCONF_H

#define ES32_ES32VF2264_MCUCONF

/*
 * HAL driver system settings.
 */
#define ES32_NO_INIT   FALSE

/*
 * GPIO driver system settings.
 */
#define ES32_USB_USE_GPIO                   TRUE

/*
 * ADC driver system settings.
 */
#define ES32_ADC_USE_ADC1 TRUE

/*
 * GPT driver system settings.
 */
#define ES32_GPT_USE_GP16C4T1 TRUE
#define ES32_GPT_USE_GP16C4T2 FALSE

/*
 * ICU driver system settings.
 */
#define ES32_ICU_USE_GP16C4T1 FALSE
#define ES32_ICU_USE_GP16C4T2 FALSE

/*
 * I2C driver system settings.
 */
#define ES32_I2C_USE_I2C1                  TRUE
#define ES32_I2C_USE_I2C2                  FALSE
#define ES32_I2C_BUSY_TIMEOUT              50

/*
 * SERIAL driver system settings.
 */
#define ES32_SERIAL_USE_UART1              FALSE
#define ES32_SERIAL_USE_UART2              FALSE
#define ES32_SERIAL_USE_UART3              FALSE
#define ES32_SERIAL_USE_UART4              FALSE

/*
 * SPI driver system settings.
 */
#define ES32_SPI_USE_SPI1                  TRUE
#define ES32_SPI_USE_SPI2                  FALSE

/*
 * ST driver system settings.
 */
#define ES32_ST_USE_TIMER                   2

/*
 * UART driver system settings.
 */
#define ES32_UART_USE_UART1                 FALSE
#define ES32_UART_USE_UART2                 FALSE
#define ES32_UART_USE_UART3                 FALSE
#define ES32_UART_USE_UART4                 FALSE

/*
 * PWM driver system settings.
 */
#define ES32_PWM_USE_GP16C4T1 TRUE
#define ES32_PWM_USE_GP16C4T2 FALSE

/*
 * USB driver system settings.
 */
#define ES32_USB_USE_USB1                   TRUE
#define ES32_USE_USB_SOF_TRIM_HRC48         TRUE

#endif /* MCUCONF_H */
