// Copyright 2025 lucky(@lucky-zang)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define USB_POWER_EN_PIN                    B1 // USB ENABLE pin
#define LED_POWER_EN_PIN                    A8 // LED ENABLE pin
#define WIITE_B 0x50
#define USB_POWER_DOWN_DELAY 7000

/* Status Indicator Lamp */
#define RGB_MATRIX_BLINK_INDEX_ALL          0xFF 
#define RGB_MATRIX_BLINK_INDEX_BAT          250
#define RGB_MATRIX_BLINK_INDEX_IND          251
#define RGB_MATRIX_BLINK_COUNT              6

#define  KJ_RGB_INDEX_CAPS                  1
#define  KJ_RGB_INDEX_NUM                   0
// #define  KJ_RGB_INDEX_SCR                   1
#define KJ_RGB_INDEX_WIN_LOCK               2
#define KJ_RGB_BLINK_INDEX_REC              13
#define KJ_RGB_BLINK_INDEX_VAI              84
#define KJ_RGB_BLINK_INDEX_VAD              7
#define KJ_RGB_BLINK_INDEX_SPI              8
#define KJ_RGB_BLINK_INDEX_SPD              6

/*  ENCODER */
#define ENCODER_RESOLUTION  2

/*  IIC INIT */
#define I2C_DRIVER        I2CD1
#define I2C1_OPMODE       OPMODE_I2C
#define I2C1_CLOCK_SPEED  100000

/* SPI */
#define SPI_DRIVER                          SPIDQ
#define SPI_SCK_PIN                         B3
#define SPI_MOSI_PIN                        B5
#define SPI_MISO_PIN                        B4

/* Flash */
#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN C12
#define WEAR_LEVELING_LOGICAL_SIZE          (WEAR_LEVELING_BACKING_SIZE / 2)
#define VIA_EEPROM_ALLOW_RESET 

/* RGB Matrix */
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES
#define RGB_TRIGGER_ON_KEYDOWN

/* RGB Light */
#define RGBLED_NUM 14
#define RGBLIGHT_CUSTOM_DRIVER
#define RGBLIGHT_DISABLE_KEYCODES
#define RGBLIGHT_LIMIT_VAL      150
#define BREATHING_VAL           150
#define RAINBOW_MOOD            150
#define LED_TYPE                RGB
#define RGBLIGHT_LED_MAP {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}

/* WS2812 */
#define WS2812_SPI_DRIVER       SPIDM2
#define WS2812_SPI_DIVISOR      32

#define RGB_MATRIX_LED_COUNT (101)

/* rgb_record */
#define ENABLE_RGB_MATRIX_RGBR_PLAY
#define RGBREC_CHANNEL_NUM         4
#define EECONFIG_CONFINFO_USE_SIZE (4 + 17)
#define EECONFIG_RGBREC_USE_SIZE   (RGBREC_CHANNEL_NUM * MATRIX_ROWS * MATRIX_COLS * 2)
#define EECONFIG_USER_DATA_SIZE    (EECONFIG_RGBREC_USE_SIZE + EECONFIG_CONFINFO_USE_SIZE)
#define RGBREC_EECONFIG_OFFSET     0U
#define RGBREC_CHANNEL_SIZE        (MATRIX_ROWS * MATRIX_COLS * 2U)
#define RGBREC_EECONFIG_CHANNEL_OFFSET(ch) ((uint32_t)(RGBREC_EECONFIG_OFFSET) + ((uint32_t)(ch) * (uint32_t)(RGBREC_CHANNEL_SIZE)))
#define CONFINFO_EECONFIG_OFFSET   (RGBREC_EECONFIG_OFFSET + (uint32_t)(EECONFIG_RGBREC_USE_SIZE))
#define CONFINFO_INDEX_OFFSET      (CONFINFO_EECONFIG_OFFSET + 4U)