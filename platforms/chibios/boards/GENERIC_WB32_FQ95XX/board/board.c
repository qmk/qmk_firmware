/*
    Copyright (C) 2022 Westberry Technology (ChangZhou) Corp., Ltd

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

/*
 * This file has been automatically generated using ChibiStudio board
 * generator plugin. Do not edit manually.
 */

#include "hal.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

static void wb32_gpio_init(void) {

#if WB32_HAS_GPIOA
  rccEnableAPB1(RCC_APB1ENR_GPIOAEN);
#endif

#if WB32_HAS_GPIOB
  rccEnableAPB1(RCC_APB1ENR_GPIOBEN);
#endif

#if WB32_HAS_GPIOC
  rccEnableAPB1(RCC_APB1ENR_GPIOCEN);
#endif

#if WB32_HAS_GPIOD
  rccEnableAPB1(RCC_APB1ENR_GPIODEN);
#endif
}

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/
/*
 * Early initialization code.
 * This initialization must be performed just after stack setup and before
 * any other initialization.
 */
void __early_init(void) {

  wb32_clock_init();
  wb32_gpio_init();
}
/**
 * @brief   Board-specific initialization code.
 * @note    You can add your board-specific code here.
 */
void boardInit(void) {

}

void restart_usb_driver(USBDriver *usbp) {
  // Do nothing. Restarting the USB driver on these boards breaks it.
}
