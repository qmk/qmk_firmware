/*
    ChibiOS Driver element - Copyright (C) 2019 /u/KeepItUnder

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

#if HAL_USE_PAL || defined(__DOXYGEN__)
/**
 * @brief   PAL setup.
 * @details Digital I/O ports static configuration as defined in @p board.h.
 *          This variable is used by the HAL when initializing the PAL driver.
 */
const PALConfig pal_default_config = {
#    if NUC123_HAS_GPIOA
    {VAL_GPIOA_PMD, VAL_GPIOA_OFFD, VAL_GPIOA_DMASK, VAL_GPIOA_DBEN, VAL_GPIOA_IMD, VAL_GPIOA_IEN, VAL_GPIOA_ISRC, VAL_GPIOA_DOUT},
#    endif
#    if NUC123_HAS_GPIOB
    {VAL_GPIOB_PMD, VAL_GPIOB_OFFD, VAL_GPIOB_DMASK, VAL_GPIOB_DBEN, VAL_GPIOB_IMD, VAL_GPIOB_IEN, VAL_GPIOB_ISRC, VAL_GPIOB_DOUT},
#    endif
#    if NUC123_HAS_GPIOC
    {VAL_GPIOC_PMD, VAL_GPIOC_OFFD, VAL_GPIOC_DMASK, VAL_GPIOC_DBEN, VAL_GPIOC_IMD, VAL_GPIOC_IEN, VAL_GPIOC_ISRC, VAL_GPIOC_DOUT},
#    endif
#    if NUC123_HAS_GPIOD
    {VAL_GPIOD_PMD, VAL_GPIOD_OFFD, VAL_GPIOD_DMASK, VAL_GPIOD_DBEN, VAL_GPIOD_IMD, VAL_GPIOD_IEN, VAL_GPIOD_ISRC, VAL_GPIOD_DOUT},
#    endif
#    if NUC123_HAS_GPIOF
    {VAL_GPIOF_PMD, VAL_GPIOF_OFFD, VAL_GPIOF_DMASK, VAL_GPIOF_DBEN, VAL_GPIOF_IMD, VAL_GPIOF_IEN, VAL_GPIOF_ISRC, VAL_GPIOF_DOUT},
#    endif
};
#endif

/**
 * @brief   Early initialization code.
 * @details This initialization must be performed just after stack setup
 *          and before any other initialization.
 */
void __early_init(void) {
    NUC123_clock_init();
}

/**
 * @brief   Board-specific initialization code.
 * @todo    Add your board-specific code, if any.
 */
void boardInit(void) {}
