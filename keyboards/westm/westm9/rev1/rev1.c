/* Copyright 2021 WestM
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

#include "rev1.h"

void board_init(void) {
    // Need this to reset first LED upon plugging in PCB
    rgblight_toggle();
    rgblight_set();
    SYSCFG->CFGR1 |= SYSCFG_CFGR1_I2C1_DMA_RMP; // Some people didn't require this for their STM32F072, so your milage may vary.
}