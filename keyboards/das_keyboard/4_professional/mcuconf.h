/*
  ChibiOS - Copyright (C) 2020 Alex Lewontin

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

#ifndef _MCUCONF_H_
#define _MCUCONF_H_

/*
 * Board setting
 * The following settings override the default settings present in
 * the various device driver implementation headers.
 * Note that the settings for each driver only have effect if the whole
 * driver is enabled in halconf.h.
 *
 * IRQ priorities:
 * 3...0       Lowest...Highest.
 *
 * DMA priorities:
 * 5...0        Lowest...Highest.
 */

/*
 * HAL driver system settings.
 */
#define NUC123_HSE_ENABLED TRUE
#define NUC123_PLL_ENABLED TRUE
#define NUC123_PLLSRC NUC123_PLLSRC_HSE
#define NUC123_HCLKSRC NUC123_HCLKSRC_PLL
#define NUC123_HCLKDIV 2
#define NUC123_PLL_NF 144
#define NUC123_USB_USE_USB0 TRUE
#define NUC123_USB_USE_USB1 TRUE

#define NUC123_SERIAL_USE_UART0 TRUE
#define NUC123_SERIAL_CLKSRC NUC123_SERIAL_CLKSRC_HSI

#define NUC123_MCUCONF

#endif /* _MCUCONF_H_ */
