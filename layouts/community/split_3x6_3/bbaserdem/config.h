/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
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
// Split definition; use the following to flash;
//  pro-micro:      avrdude-split-left/right
//  elite-c:        dfu-split-left/right

// Code pertaining to Corne ARM; from Waffle's keymap
#ifdef KEYBOARD_crkbd_rev1
    // Use EE_HANDS to determine handedness
#   define EE_HANDS

    // Rebrand the PCB
#   undef PRODUCT
#   define PRODUCT Protorne Keyboard
#   undef MANUFACTURER
#   define MANUFACTURER Waffles

    // Remove OLED definitions? 
#   undef USE_I2C
#   undef SSD1306OLED

    // Audio output on pin A5 (actualy will be output on B1 using keymap init)
#   ifdef AUDIO_ENABLE
#       define AUDIO_PIN A5
#       define MUSIC_MAP
#   endif

    // Set serial pin as D3 for sure
#   undef SOFT_SERIAL_PIN
#   define SOFT_SERIAL_PIN D3
#   define SERIAL_USART_SPEED 921600
#   define SERIAL_USART_DRIVER SD1
#   define SERIAL_USART_TX_PAL_MODE 7

    // Things to make RGB matrix work on the waffle board
#   undef RGBLED_NUM
#   define RGBLED_NUM 54
#   undef RGB_DI_PIN
#   define RGB_DI_PIN B5
#   ifdef RGB_MATRIX_ENABLE
#       define RGB_MATRIX_MAXIMUM_BRIGHTNESS 100
#       define RGB_MATRIX_SPLIT { 27, 27 }
#   endif
#   define WS2812_PWM_DRIVER PWMD3
#   define WS2812_PWM_CHANNEL 3
#   define WS2812_PWM_PAL_MODE 2
#   define WS2812_DMA_STREAM STM32_DMA1_STREAM3
#   define WS2812_DMA_CHANNEL 3

    // OLED related code
#   ifdef OLED_ENABLE
#       define OLED_UPDATE_INTERVAL 100
#   endif
    
    // Encoder definitons
#   define ENCODERS_PAD_A { B2 }
#   define ENCODERS_PAD_B { B6 }
#   define ENCODER_RESOLUTIONS { 4 }
#   define ENCODERS_PAD_A_RIGHT { B2 }
#   define ENCODERS_PAD_B_RIGHT { B6 }
#   define ENCODER_RESOLUTIONS_RIGHT { 2 }
#endif
