/* Copyright 2022 Jacky
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

//#define DEBUG_MATRIX_SCAN_RATE

#define DRIVER_1_LED_TOTAL 66
#define DRIVER_2_LED_TOTAL 21
#define RGB_MATRIX_LED_COUNT (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)
#define SPI_DRIVER SPID1
#define AW_SPI_MODE 3


/* SPI Config for LED Driver */

#define SPI_SCK_PIN A5
#define SPI_MOSI_PIN A6
#define SPI_MISO_PIN A7

#define DRIVER_1_CS B13
#define DRIVER_2_CS B14
#define DRIVER_1_EN C13
#define DRIVER_2_EN C13

#define DRIVER_COUNT 2


/* UART Config  */

#define SERIAL_DRIVER SD1
#define SD1_TX_PAL_MODE PAL_MODE_ALTERNATE_OPENDRAIN



#define RGB_MATRIX_KEYPRESSES // reacts to keypresses
//#define RGB_MATRIX_KEYRELEASES         // reacts to keyreleases (instead of keypresses)
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS // enable framebuffer effects
#define RGB_DISABLE_WHEN_USB_SUSPENDED // USB待机时候停止灯效
#define RGB_MATRIX_SOLID_REACTIVE_GRADIENT_MODE
//#define RGB_MATRIX_TYPING_HEATMAP_SLIM














