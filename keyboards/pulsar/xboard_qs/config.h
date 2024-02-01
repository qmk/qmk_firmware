/* Copyright 2024 Aplusx Inc.
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

#pragma once

#define WAIT_US_TIMER           GPTD3       //  Encoder 및 RGB ANI가 부드러워짐

// Dynamic EEPROM
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR  4095

/* USB Hub Control pins  */
#define GPIO_KM_PWEN        C1      // Hub Device Power on/off
#define GPIO_KM_OE          C2      // Hub Host Connection on/off
#define GPIO_KM_SEL         C0      // Hub Host Selection
#define GPIO_TEST_DEBUG     C9      // C3-LED / C9-GPIO PAD

/* RGB Underglow or WS2812 RGB Matirx  <spi driver > */
#define WS2812_SPI_DRIVER           SPID2    
#define WS2812_SPI_MOSI_PAL_MODE    0      
#define WS2812_SPI_SCK_PIN          B13
#define WS2812_SPI_SCK_PAL_MODE     5   
#define WS2812_SPI_DIVISOR          16  
#define WS2812_SPI_USE_CIRCULAR_BUFFER

