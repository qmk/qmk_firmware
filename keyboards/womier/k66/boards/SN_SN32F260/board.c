/*
 *  ChibiOS - Copyright (C) 2006..2016 Giovanni Di Sirio
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

/*
 * This file has been automatically generated using ChibiStudio board
 * generator plugin. Do not edit manually.
 */

#include "hal.h"

#if HAL_USE_PAL || defined(__DOXYGEN__)

/**
 * @brief   PAL setup.
 * @details Digital I/O ports static configuration as defined in @p board.h.
 *          This variable is used by the HAL when initializing the PAL driver.
 */
const PALConfig pal_default_config = {
#    if STM32_HAS_GPIOA
    {VAL_GPIOA_MODER},
#    endif
#    if STM32_HAS_GPIOB
    {VAL_GPIOB_MODER},
#    endif
#    if STM32_HAS_GPIOC
    {VAL_GPIOC_MODER},
#    endif
#    if STM32_HAS_GPIOD
    {VAL_GPIOD_MODER},
#    endif
};
#endif

static int flag __attribute__((section(".flag"))) __attribute__((__used__)) = 0xAAAA5555;

/**
 * @brief   Early initialization code.
 * @details This initialization must be performed just after stack setup
 *          and before any other initialization.
 */
void __early_init(void) { sn32_clock_init(); }

/**
 * @brief   Board-specific initialization code.
 * @todo    Add your board-specific code, if any.
 */
void boardInit(void) {
    // setP0.0~P0.1, P0.6~P0.7, P0.10~P0.15 to input pull-up
    SN_GPIO0->CFG = 0x000A0AA0;

    // set P1.2~1.9, P1.12~P1.15 to input pull-up
    SN_GPIO1->CFG = 0x00A0000A;

    // set P2.4~P2.15 to input pull-up
    SN_GPIO2->CFG = 0x000000AA;

    // set P3.0~P3.1, P3.4~P3.8 to input pull-up
    SN_GPIO3->CFG = 0xAAA800A0;

    SN_GPIO0->MODE = 0xffff;
    SN_GPIO2->CFG  = 0x00;  // Enable P2 internal pull-up resistor
    SN_GPIO2->MODE = 0xFFFF;
    SN_GPIO2->DATA = 0x0000;

    SN_SYS0->SWDCTRL_b.SWDDIS = 1;
}
