/* Copyright 2020 Yiancar
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
#ifndef RGB_BACKLIGHT_NEBULA12
#    error RGB_BACKLIGHT_NEBULA12 not defined, recheck config.h
#else
#    include "drivers/led/issi/is31fl3731.h"
#endif

#include "nebula12.h"

void board_init(void) {
  SYSCFG->CFGR1 |= SYSCFG_CFGR1_I2C1_DMA_RMP;
  SYSCFG->CFGR1 &= ~(SYSCFG_CFGR1_SPI2_DMA_RMP);
}

#if defined(RGB_MATRIX_ENABLE) || defined(RGB_BACKLIGHT_NEBULA12)
const is31fl3731_led_t PROGMEM g_is31fl3731_leds[IS31FL3731_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, C1_1,  C3_2,  C4_2}, //A1
    {0, C1_2,  C2_2,  C4_3}, //A2
    {0, C1_3,  C2_3,  C3_3}, //A3
    {0, C1_4,  C2_4,  C3_4}, //A4
    {0, C1_5,  C2_5,  C3_5}, //A5
    {0, C1_6,  C2_6,  C3_6}, //A6
    {0, C1_7,  C2_7,  C3_7}, //A7
    {0, C1_8,  C2_8,  C3_8}, //A8
    {0, C9_1,  C8_1,  C7_1}, //A9
    {0, C9_2,  C8_2,  C7_2}, //A10
    {0, C9_3,  C8_3,  C7_3}, //A11
    {0, C9_4,  C8_4,  C7_4}, //A12
    {0, C9_5,  C8_5,  C7_5}, //A13
    {0, C9_6,  C8_6,  C7_6}, //A14
    {0, C9_7,  C8_7,  C6_6}, //A15
    {0, C9_8,  C7_7,  C6_7}, //A16
};
#endif
