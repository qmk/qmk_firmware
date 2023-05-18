/*
Copyright 2023 @dlford
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 150U

// wiring of each half
#define MATRIX_COL_PINS \
    { B4, E6, D7, C6, D4 }
#define MATRIX_ROW_PINS \
    { B6, B2, B3, B1 }

#define DIODE_DIRECTION ROW2COL

#define RGB_DI_PIN F4
#define RGB_MATRIX_LED_COUNT 36
#define RGB_MATRIX_SPLIT \
    { 18, 18 }
#define RGB_MATRIX_CENTER \
    { 133, 54 }

#define OLED_DISPLAY_128X64

#define AUDIO_PIN B5
#define AUDIO_PWM_DRIVER PWMD4
#define AUDIO_PWM_CHANNEL RP2040_PWM_CHANNEL_B

#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_PIO_USE_PIO0
#define SOFT_SERIAL_PIN D3
#define SERIAL_USART_RX_PIN D2
