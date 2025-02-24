/* Copyright 2024 temp4gh
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "quantum.h"
#include "config.h"
#include "btspi.h"

void init_set_IS31FL3733_poweron(void)
{
    palSetLineMode(IS31FL3733_POWERON_PIN, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLine(IS31FL3733_POWERON_PIN);
}

void bootloader_jump(void)
{
    NVIC_SystemReset();
}

void mcu_reset(void)
{
    NVIC_SystemReset();
}

void board_init(void)
{
    AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_DISABLE;

    palSetLineMode(CAPS_LOCK_DRV_PIN, PAL_MODE_OUTPUT_PUSHPULL);
    set_caps_lock_off();

    palSetPadMode(GPIOC, 11, PAL_MODE_INPUT);
    palSetPadMode(GPIOA, 13, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA, 14, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA, 15, PAL_MODE_OUTPUT_PUSHPULL);

    init_set_IS31FL3733_poweron();
}
