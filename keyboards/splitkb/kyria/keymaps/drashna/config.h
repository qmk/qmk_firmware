/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

#define EE_HANDS

#ifdef OLED_ENABLE
#    undef OLED_DISPLAY_128X64
#    define OLED_DISPLAY_128X128
#    define OLED_PRE_CHARGE_PERIOD 0x22
#    define OLED_VCOM_DETECT 0x35
#endif

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_SLEEP
#    undef RGBLIGHT_LIMIT_VAL
#    define RGBLIGHT_LIMIT_VAL 120
#    define RGBLIGHT_HUE_STEP  8
#    define RGBLIGHT_SAT_STEP  8
#    define RGBLIGHT_VAL_STEP  8
#    define RGBLIGHT_SPLIT
#    define RGBLIGHT_LAYERS
#endif


#define QMK_ESC_INPUT               D4
#define QMK_ESC_OUTPUT              B2

#ifdef KEYBOARD_splitkb_kyria_rev3
#    define SERIAL_USART_FULL_DUPLEX      // Enable full duplex operation mode.
#    define SERIAL_USART_PIN_SWAP         // Swap TX and RX pins if keyboard is master halve.
#    define SERIAL_USART_DRIVER      SD1  // USART driver of TX pin. default: SD1
#    define SERIAL_USART_TX_PAL_MODE 7    // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#    undef SOFT_SERIAL_PIN
#    define SERIAL_USART_TX_PIN      D3
#    define SERIAL_USART_RX_PIN      D2

#    undef WS2812_DI_PIN
#    define WS2812_DI_PIN            PAL_LINE(GPIOA, 3)
#    define WS2812_PWM_DRIVER        PWMD2                  // default: PWMD2
#    define WS2812_PWM_CHANNEL       4                      // default: 2
#    define WS2812_PWM_PAL_MODE      1                      // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 2
#    define WS2812_DMA_STREAM        STM32_DMA1_STREAM2     // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#    define WS2812_DMA_CHANNEL       2                      // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#    define WS2812_DMAMUX_ID         STM32_DMAMUX1_TIM2_UP  // DMAMUX configuration for TIMx_UP -- only required if your MCU has a DMAMUX peripheral, see the respective reference manual for the appropriate values for your MCU.

#    define BOOTMAGIC_LITE_ROW 0
#    define BOOTMAGIC_LITE_COLUMN 6
#    define BOOTMAGIC_LITE_ROW_RIGHT 4
#    define BOOTMAGIC_LITE_COLUMN_RIGHT 6

#    define BOOTMAGIC_LITE_EEPROM_ROW 1
#    define BOOTMAGIC_LITE_EEPROM_COLUMN 6
#    define BOOTMAGIC_LITE_EEPROM_ROW_RIGHT 5
#    define BOOTMAGIC_LITE_EEPROM_COLUMN_RIGHT 6
#    define SECURE_UNLOCK_SEQUENCE    { {1, 5}, {1, 4}, {1, 3}, {1, 2} }

#    define ENCODER_RESOLUTION 2
#else
#    define BOOTMAGIC_LITE_ROW 0
#    define BOOTMAGIC_LITE_COLUMN 7
#    define BOOTMAGIC_LITE_ROW_RIGHT 4
#    define BOOTMAGIC_LITE_COLUMN_RIGHT 7

#    define BOOTMAGIC_LITE_EEPROM_ROW 1
#    define BOOTMAGIC_LITE_EEPROM_COLUMN 7
#    define BOOTMAGIC_LITE_EEPROM_ROW_RIGHT 5
#    define BOOTMAGIC_LITE_EEPROM_COLUMN_RIGHT 7
#endif

#define SERIAL_USART_SPEED       921600

#if defined(KEYBOARD_splitkb_kyria_rev1_proton_c) || defined(KEYBOARD_splitkb_kyria_rev3)
#    define WEAR_LEVELING_BACKING_SIZE 16384
#    define WEAR_LEVELING_LOGICAL_SIZE 8192
#endif
