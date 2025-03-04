/*
    ChibiOS - Copyright (C) 2006..2021 Giovanni Di Sirio

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

/*
 * RP2040_MCUCONF drivers configuration.
 *
 * IRQ priorities:
 * 3...0        Lowest...Highest.
 *
 * DMA priorities:
 * 0...1        Lowest...Highest.
 */

#define RP2040_MCUCONF

/*
 * HAL driver system settings.
 */
#define RP_NO_INIT                          FALSE
#define RP_CORE1_START                      FALSE
#define RP_CORE1_VECTORS_TABLE              _vectors
#define RP_CORE1_ENTRY_POINT                _crt0_c1_entry
#define RP_CORE1_STACK_END                  __c1_main_stack_end__

/*
 * IRQ system settings.
 */
#define RP_IRQ_SYSTICK_PRIORITY             2
#define RP_IRQ_TIMER_ALARM0_PRIORITY        2
#define RP_IRQ_TIMER_ALARM1_PRIORITY        2
#define RP_IRQ_TIMER_ALARM2_PRIORITY        2
#define RP_IRQ_TIMER_ALARM3_PRIORITY        2
#define RP_IRQ_ADC1_PRIORITY                3
#define RP_IRQ_UART0_PRIORITY               3
#define RP_IRQ_UART1_PRIORITY               3
#define RP_IRQ_SPI0_PRIORITY                2
#define RP_IRQ_SPI1_PRIORITY                2
#define RP_IRQ_USB0_PRIORITY                3
#define RP_IRQ_I2C0_PRIORITY                2
#define RP_IRQ_I2C1_PRIORITY                2
#define RP_IRQ_RTC_PRIORITY                 3

/*
 * USB driver system settings.
 */
#define RP_USB_USE_USBD0                    TRUE
#define RP_USB_FORCE_VBUS_DETECT            TRUE
#define RP_USE_EXTERNAL_VBUS_DETECT         FALSE
#define RP_USB_USE_ERROR_DATA_SEQ_INTR      FALSE

#endif /* MCUCONF_H */
