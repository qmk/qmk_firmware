/*
Copyright 2020 Gondolindrim

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

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0xAC11
#define PRODUCT_ID 0x5369 // For Shark+1
#define DEVICE_VER 0x0002
#define MANUFACTURER AcheronProject
#define PRODUCT SharkPCB rev. Beta

#define MATRIX_ROWS 4
#define MATRIX_COLS 12

#define MATRIX_COL_PINS { A5 , A10, C13, B9 , B8 , B5 , B4 , B3 , A15, A0 , A1 , A2 }
#define MATRIX_ROW_PINS { A8 , B14, A4 , A3 }
#define DIODE_DIRECTION COL2ROW

#define DEBOUNCE 5

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE

#define BACKLIGHT_PIN           A6
#define BACKLIGHT_PWM_DRIVER    PWMD3
#define BACKLIGHT_PWM_CHANNEL   1
#define BACKLIGHT_PAL_MODE      2
#define BACKLIGHT_LEVELS 20
#define BACKLIGHT_BREATHING
#define BREATHING_PERIOD 5
#define BACKLIGHT_ON_STATE 1

#define RGB_DI_PIN B15
#define RGBLED_NUM 24
#define RGBLIGHT_ANIMATIONS

#define WS2812_PWM_COMPLEMENTARY_OUTPUT
#define WS2812_PWM_DRIVER PWMD1
#define WS2812_PWM_CHANNEL 3
#define WS2812_PWM_PAL_MODE 1
#define WS2812_DMA_STREAM STM32_DMA2_STREAM5
#define WS2812_DMA_CHANNEL 6

#define ENCODERS_PAD_A { C15 }
#define ENCODERS_PAD_B { C14 }

#define EEPROM_I2C_24LC256
