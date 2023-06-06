// Copyright 2023 Vinh Le (@vinhcatba)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

/* WS2812 driver config specifically for STM32F401 */

// DI pin = PB1, which is AF02, TIM3_CH4 (table 9 in datasheet)
#ifdef RGBLIGHT_ENABLE
    #define RGBLIGHT_LED_MAP { 2,	3,	4,	5,	6,	0,	1,	7,	8,	9,	10,	11,	12,	13}    // index 5 = CAPS; index 6 = NUM

    #define WS2812_PWM_DRIVER PWMD3     // TIM3
    #define WS2812_PWM_CHANNEL 4        // CH4
    #define WS2812_PWM_PAL_MODE 2       // AF2

    #define WS2812_DMA_STREAM STM32_DMA1_STREAM2        // DMA1 Stream 2 for TIM3_UP (table 28 in reference manual)
    #define WS2812_DMA_CHANNEL 5                        // DMA Channel 5 for TIM3_UP  (table 28 in reference manual)
#endif

/* i2c peripheral config */
#define I2C_DRIVER I2CD1
#define I2C1_SCL_PIN B6
#define I2C1_SDA_PIN B7
#define I2C_SCL_PAL_MODE 4
#define I2C_SDA_PAL_MODE 4

#define I2C1_CLOCK_SPEED 400000
#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2

/* eeprom i2c driver config */
#define EXTERNAL_EEPROM_I2C_BASE_ADDRESS 0b10100000
#define EXTERNAL_EEPROM_BYTE_COUNT 4096
#define EXTERNAL_EEPROM_PAGE_SIZE 32
#define EXTERNAL_EEPROM_WRITE_TIME 10
//#define EEPROM_I2C_24LC32

/* OLED config */
#ifdef OLED_ENABLE
#define OLED_UPDATE_INTERVAL 100
#define OLED_BRIGHTNESS 200
#endif
