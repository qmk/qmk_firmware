/*
 Copyright 2022 Gondolindrim <gondolindrim@acheronproject.com>

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
#include "common_config.h"

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 18

                       // C0 , C1 , C2 , C3 , C4 , C5 , C6 , C7 , C8 , C9 , C10, C11, C12, C13, C14, C15, C16, C17
#define MATRIX_COL_PINS { C6 , C7 , C8 , C9 , A8 , B3 , B4 , A10, B5 , B8 , B9 , C13, C14, C15, A0 , A1 , A2 , A3 }
                      //  R0 , R1 , R2 , R3 , R4 , R5
#define MATRIX_ROW_PINS { C3 , C2 , C1 , C0 , B14, A7 } 
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define ENCODERS_PAD_A { B10 }
#define ENCODERS_PAD_B { B12 }
#define ENCODER_RESOLUTION 2

#define TAPPING_TERM 200

#define I2C_DRIVER I2CD1
#define I2C_SCL_PIN B6
#define I2C_SDA_PIN B7
#define I2C_SCL_PAL_MODE 4
#define I2C_SDA_PAL_MODE 4
#define EEPROM_I2C_24LC256
#define I2C1_CLOCK_SPEED 400000
#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2

#define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE

#define RGB_DI_PIN B15
#define RGBLED_NUM 4
#define RGBLIGHT_DEFAULT_VAL 0

#define WS2812_PWM_COMPLEMENTARY_OUTPUT
#define WS2812_PWM_DRIVER PWMD1
#define WS2812_PWM_CHANNEL 3
#define WS2812_PWM_PAL_MODE 1
#define WS2812_DMA_STREAM STM32_DMA2_STREAM5
#define WS2812_DMA_CHANNEL 6
