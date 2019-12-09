/*
    ChibiOS - Copyright (C) 2006..2016 Giovanni Di Sirio

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

#include "hal.h"

/**
 * @brief   PAL setup.
 * @details Digital I/O ports static configuration as defined in @p board.h.
 *          This variable is used by the HAL when initializing the PAL driver.
 */
#if HAL_USE_PAL || defined(__DOXYGEN__)
const PALConfig pal_default_config =
{
  {VAL_GPIOA_ODR, VAL_GPIOA_CRL, VAL_GPIOA_CRH},
  {VAL_GPIOB_ODR, VAL_GPIOB_CRL, VAL_GPIOB_CRH},
  {VAL_GPIOC_ODR, VAL_GPIOC_CRL, VAL_GPIOC_CRH},
  {VAL_GPIOD_ODR, VAL_GPIOD_CRL, VAL_GPIOD_CRH},
  {VAL_GPIOE_ODR, VAL_GPIOE_CRL, VAL_GPIOE_CRH},
};
#endif

/*
 * Early initialization code.
 * This initialization must be performed just after stack setup and before
 * any other initialization.
 */
void __early_init(void) {

  stm32_clock_init();
}

/*
 * Board-specific initialization code.
 */
void boardInit(void) {
}
