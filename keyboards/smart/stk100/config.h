/* Copyright 2024 Jacky Jia <jacky@i-chip.cn>
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

#define SPI_DRIVER SPID1

#define AW20216S_CS_PIN_1 C11
#define AW20216S_CS_PIN_2 C10

#define AW20216S_EN_PIN_1 A15
#define AW20216S_EN_PIN_2 A15

#define DRIVER_1_LED_TOTAL 50
#define DRIVER_2_LED_TOTAL 51
#define RGB_MATRIX_LED_COUNT (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)

#define SPI_SCK_PIN A5
#define SPI_MOSI_PIN A6
#define SPI_MISO_PIN A7

/* Disable DIP switch in matrix data */
#define MATRIX_MASKED

/* DIP switch */
#define DIP_SWITCH_MATRIX_GRID  { {6,0},{6,1} }

#define TRANSIENT_EEPROM_SIZE 2048
