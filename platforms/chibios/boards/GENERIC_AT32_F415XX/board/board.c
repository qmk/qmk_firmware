/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio
    ChibiOS - Copyright (C) 2023..2024 HorrorTroll
    ChibiOS - Copyright (C) 2023..2024 Zhaqian

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
  {VAL_GPIOAODT, VAL_GPIOACFGLR, VAL_GPIOACFGHR},
  {VAL_GPIOBODT, VAL_GPIOBCFGLR, VAL_GPIOBCFGHR},
#if AT32_HAS_GPIOC
  {VAL_GPIOCODT, VAL_GPIOCCFGLR, VAL_GPIOCCFGHR},
#endif
  {VAL_GPIODODT, VAL_GPIODCFGLR, VAL_GPIODCFGHR},
#if AT32_HAS_GPIOF
  {VAL_GPIOFODT, VAL_GPIOFCFGLR, VAL_GPIOFCFGHR},
#endif
};
#endif

/*
 * Early initialization code.
 * This initialization must be performed just after stack setup and before
 * any other initialization.
 */
void __early_init(void) {
  at32_clock_init();
}

/*
 * Board-specific initialization code.
 */
void boardInit(void) {
  IOMUX->REMAP |= IOMUX_REMAP_SWJTAG_MUX_JTAGDIS;
}
