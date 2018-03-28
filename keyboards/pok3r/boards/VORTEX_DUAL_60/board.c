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

#include "ch.h"
#include "hal.h"

#if HAL_USE_PAL || defined(__DOXYGEN__)
/**
 * @brief   PAL setup.
 * @details Digital I/O ports static configuration as defined in @p board.h.
 *          This variable is used by the HAL when initializing the PAL driver.
 */
const PALConfig pal_default_config = {
	.setup[0] = {
		.DIR = 0x0000,
		.INE = 0x0000,
		.PU = 0x0000,
		.PD = 0x0000,
		.OD = 0x0000,
		.DRV = 0x0000,
		.LOCK = 0x0000,
		.OUT = 0x0000,
		.CFG[0] = 0x00000000,
		.CFG[1] = 0x00000000,
	},
	.setup[1] = {
		.DIR = 0x0000,
		.INE = 0x0000,
		.PU = 0x0000,
		.PD = 0x0000,
		.OD = 0x0000,
		.DRV = 0x0000,
		.LOCK = 0x0000,
		.OUT = 0x0000,
		.CFG[0] = 0x00000000,
		.CFG[1] = 0x00000000,
	},
	.setup[2] = {
		.DIR = 0x0000,
		.INE = 0x0000,
		.PU = 0x0000,
		.PD = 0x0000,
		.OD = 0x0000,
		.DRV = 0x0000,
		.LOCK = 0x0000,
		.OUT = 0x0000,
		.CFG[0] = 0x00000000,
		.CFG[1] = 0x00000000,
	},
	.setup[3] = {
		.DIR = 0x0000,
		.INE = 0x0000,
		.PU = 0x0000,
		.PD = 0x0000,
		.OD = 0x0000,
		.DRV = 0x0000,
		.LOCK = 0x0000,
		.OUT = 0x0000,
		.CFG[0] = 0x00000000,
		.CFG[1] = 0x00000000,
	},
	.setup[4] = {
		.DIR = 0x0000,
		.INE = 0x0000,
		.PU = 0x0000,
		.PD = 0x0000,
		.OD = 0x0000,
		.DRV = 0x0000,
		.LOCK = 0x0000,
		.OUT = 0x0000,
		.CFG[0] = 0x00000000,
		.CFG[1] = 0x00000000,
	},
	.ESSR[0] = 0x00000000,
	.ESSR[1] = 0x00000000,
};

#endif

/**
 * @brief   Board-specific initialization code.
 * @todo    Add your board-specific code, if any.
 */
void boardInit(void) {
}

void __early_init(void)
{
  ht32_clock_init();
}

const uint32_t bootloader_magic[2] __attribute__ ((section (".magic.bootloader"))) = {
  0x03046000, 0x34000001,
};
