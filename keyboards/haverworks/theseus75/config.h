/* Copyright 2023 Moritz Plattner (@ebastler), Alex Havermale (@haversnail)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

/* Defines for the split keyboard setup */
#define SERIAL_USART_DRIVER SD3         // USART 3
#define SOFT_SERIAL_PIN B10             // The GPIO pin that is used split communication.
#define USART3_REMAP                    // Remap USART TX and RX pins for half duplex
#define SERIAL_USART_TX_PAL_MODE 7      // Pin alternate function 7 = USART3_TX for PB10

#if defined(SOFT_SERIAL_PIN)
#    define SERIAL_USART_TX_PIN SOFT_SERIAL_PIN
#endif

#define SELECT_SOFT_SERIAL_SPEED 0    // Experimental, will make connection faster but may need testing.

#define ID_PIN A13
#define USBSW_PIN A14     // Switches the hub input/output with the MUXes
#define PSW_PIN A15       // Turns the power routing to the usb-c port on/off
#define SPLIT_HAND_PIN B9 // The MCUs probe a pin to determine if they are left or right side. high = left, low = right
#define BUS_B_PIN C13     // Tells the hub to be bus powered or self powered (which in turn tells the clients connected to it to be 100 mA or 500 mA)
#define USB_VBUS_PIN C15  // Only the master side will have VBUS present at power-up (used to determine master/slave)
#define USBPD_1_PIN F0
#define USBPD_2_PIN F1

#define SPLIT_TRANSACTION_IDS_KB RPC_ID_KB_STATE

#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE          // Required to sync LED indicator state info to the slave half (see https://docs.qmk.fm/#/feature_led_indicators)

/* Defines for the RGB matrix */
#ifdef RGB_MATRIX_ENABLE
#   define RGB_MATRIX_MAXIMUM_BRIGHTNESS 128
#   define INDICATOR_MAX_BRIGHTNESS 255
#   define CAPS_LOCK_LED_INDEX 0        // LED1 on PCB
#   define RGB_MATRIX_LED_COUNT 53
#   define RGB_MATRIX_SPLIT { 27, 26 }
#   define RGBLIGHT_SLEEP
#   define NOP_FUDGE 0.4                // Chip/pin specific configs from this lone onward
#   define WS2812_EXTERNAL_PULLUP
#   define WS2812_PWM_DRIVER PWMD3
#   define WS2812_PWM_CHANNEL 4
#   define WS2812_PWM_PAL_MODE 10
#   define WS2812_DMA_STREAM STM32_DMA1_STREAM2
#   define WS2812_DMA_CHANNEL 2
#   define WS2812_DMAMUX_ID STM32_DMAMUX1_TIM3_UP
#endif

#define USBPD_ALLOWANCE_CHECK_INTERVAL 100
