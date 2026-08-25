// Copyright 2024 SDK (@sdk66)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define USB_POWER_EN_PIN                    B1 // USB ENABLE pin
#define LED_POWER_EN_PIN                    A5 // LED ENABLE pin
#define HS_BAT_CABLE_PIN                    A7 // USB insertion detection pin
#define HS_LED_BOOSTING_PIN                 D2 // LED BOOSTING,Power boost pin
#define LED_ENABLE_ON 1

#define BAT_FULL_PIN                        A15
#define BAT_FULL_STATE                      1

#define MM_BT_DEF_PIN                       C15
#define MM_2G4_DEF_PIN                      C14
#define HS_SUCCEED_TIME                     2000 // 2s

/* Device Name Definition */
#define MD_BT1_NAME "R87Pro"
#define MD_BT2_NAME "R87Pro"
#define MD_BT3_NAME "R87Pro"
#define MD_DONGLE_MANUFACTURER "RK 2.4 GDongle"

/* Device Connection RGB Indicator Light Index And Color */
#define HS_RGB_BLINK_INDEX_BT1 49
#define HS_RGB_BLINK_INDEX_BT2 48
#define HS_RGB_BLINK_INDEX_BT3 47
#define HS_RGB_BLINK_INDEX_2G4 40
// #define HS_RGB_BLINK_INDEX_USB 45

#define HS_LBACK_COLOR_BT1 RGB_RED
#define HS_LBACK_COLOR_BT2 RGB_GREEN
#define HS_LBACK_COLOR_BT3 RGB_BLUE
#define HS_LBACK_COLOR_2G4 RGB_WHITE
#define HS_LBACK_COLOR_USB RGB_WHITE

#define HS_PAIR_COLOR_BT1  RGB_RED
#define HS_PAIR_COLOR_BT2  RGB_GREEN
#define HS_PAIR_COLOR_BT3  RGB_BLUE
#define HS_PAIR_COLOR_2G4  RGB_WHITE
#define HS_PAIR_COLOR_USB  RGB_WHITE

#define WIITE_B 0X3e
#define HS_DEBOUNCE

/* Battery */
#define RGB_MATRIX_BAT_INDEX_MAP {52,53, 54, 55, 56, 57, 58, 59, 60, 61}

/* LED */
#define LED_PIN_ON_STATE 1
#define LED_CAPS_PIN A9
#define LED_WIN_PIN B8

/* UART */
#define SERIAL_DRIVER SD3
#define SD1_TX_PIN C10
#define SD1_RX_PIN C11

// UART for wireless communication
#define UART_DRIVER SD3
#define UART_TX_PIN A9
#define UART_RX_PIN A10
#define UART_TX_PAL_MODE 7
#define UART_RX_PAL_MODE 7


/* Encoder */
#define ENCODER_MAP_KEY_DELAY               1
#define ENCODER_RESOLUTION                  4

/* SPI */
#define SPI_DRIVER                          SPIDQ
#define SPI_SCK_PIN                         B3
#define SPI_MOSI_PIN                        B5
#define SPI_MISO_PIN                        B4

/* Flash */
#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN C12
#define WEAR_LEVELING_LOGICAL_SIZE          (WEAR_LEVELING_BACKING_SIZE / 2)

/* RGB Matrix */
#define HS_RGB
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES

/* RGB Light */
#define RGBLED_NUM 33
#define RGBLIGHT_CUSTOM_DRIVER
//#define RGBLIGHT_DISABLE_KEYCODES
#define BREATHING_VAL           40
#define RAINBOW_MOOD            40
#define LED_TYPE                RGB
#define RGBLIGHT_LED_MAP {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}

/* Status Indicator Lamp */
#define RGB_MATRIX_BLINK_INDEX_ALL          0xFF
#define RGB_MATRIX_BLINK_INDEX_IND          251
#define RGB_MATRIX_BLINK_COUNT              4

#define HS_RGB_BLINK_INDEX_WIN              22
#define HS_RGB_BLINK_INDEX_MAC              23
#define HS_RGB_BLINK_INDEX_BAT              2
#define HS_RGB_INDEX_INDEX_CAP              1
#define HS_RGB_INDEX_INDEX_NUM              0
// #define HS_RGB_INDEX_SCR                    1
#define HS_RGB_INDEX_WIN_LOCK               102
#define HS_RGB_BLINK_INDEX_REC              32
#define HS_RGB_BLINK_INDEX_VAI              8
#define HS_RGB_BLINK_INDEX_VAD              6
#define HS_RGB_BLINK_INDEX_SPI              7
#define HS_RGB_BLINK_INDEX_SPD              5

/* WS2812 */
#define WS2812_SPI_DRIVER       SPIDM2
#define WS2812_SPI_DIVISOR      32

/* rgb_record */
#define ENABLE_RGB_MATRIX_RGBR_PLAY
#define RGBREC_CHANNEL_NUM         4
#define EECONFIG_CONFINFO_USE_SIZE (4 + 16)
#define EECONFIG_RGBREC_USE_SIZE   (RGBREC_CHANNEL_NUM * MATRIX_ROWS * MATRIX_COLS * 2)
#define EECONFIG_USER_DATA_SIZE    (EECONFIG_RGBREC_USE_SIZE + EECONFIG_CONFINFO_USE_SIZE)
//#define RGBREC_EECONFIG_ADDR       (uint8_t *)(EECONFIG_USER_DATABLOCK)
#define RGBREC_EECONFIG_ADDR       (uint8_t *)(EECONFIG_USER_DATA_SIZE)
#define CONFINFO_EECONFIG_ADDR     (uint32_t *)((uint32_t)RGBREC_EECONFIG_ADDR + (uint32_t)EECONFIG_RGBREC_USE_SIZE)
