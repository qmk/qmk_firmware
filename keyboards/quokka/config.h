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
    { GP8, GP7, GP6, GP5, GP4 }
#define MATRIX_ROW_PINS \
    { GP10, GP19, GP20, GP18 }

#define DIODE_DIRECTION ROW2COL

#define WS2812_PIO_USE_PIO1
#define RGB_DI_PIN GP29
#define RGB_MATRIX_LED_COUNT 36
#define RGB_MATRIX_SPLIT \
    { 18, 18 }
#define RGB_MATRIX_CENTER \
    { 133, 54 }

#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP2
#define I2C1_SCL_PIN GP3
#define OLED_DISPLAY_128X64

#define AUDIO_PIN GP9
#define AUDIO_PWM_DRIVER PWMD4
#define AUDIO_PWM_CHANNEL RP2040_PWM_CHANNEL_B

#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_PIO_USE_PIO0
#define SOFT_SERIAL_PIN GP0
#define SERIAL_USART_RX_PIN GP1
