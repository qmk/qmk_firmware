/* Copyright
 *   2021 solartempest
 *   2021 QMK
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

#define DEBUG_TO_SCREEN 1

#define EE_HANDS

//#define SPLIT_USB_DETECT
//#define SPLIT_MASTER_TIMER 2000

#define MASTER_RIGHT

// OLED settings
#undef OLED_ENABLE
#define OLED_ENABLE
#define OLED_TIMEOUT    80000
#define OLED_BRIGHTNESS 90

//#define OLED_IC	        OLED_IC_SSD1306
#define OLED_DC_PIN B6
#define OLED_CS_PIN B7

#define I2C1_SCL_PIN B6
#define I2C1_SDA_PIN B7
#define I2C_DRIVER I2CD1

#define SERIAL_USART_HALF_DUPLEX  // Enable full duplex operation mode.
#define SERIAL_USART_DRIVER      SD2
#define SERIAL_USART_TX_PAL_MODE 7    // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#define SERIAL_USART_RX_PAL_MODE 7    // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#define SERIAL_USART_TIMEOUT     100  // USART driver timeout. default 100
#define SERIAL_USART_SPEED       921600


#define BACKLIGHT_PWM_DRIVER    PWMD3
#define BACKLIGHT_PWM_CHANNEL   1
#define BACKLIGHT_PAL_MODE      1

#define WS2812_SPI_DRIVER SPID2
#define WS2812_SPI_MOSI_PAL_MODE 0
#define WS2812_SPI_SCK_PAL_MODE 0
#define WS2812_SPI_SCK_PIN B13