// Copyright 2024 SDK (@sdk66)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define USB_POWER_EN_PIN                    B1 // USB ENABLE pin
#define LED_POWER_EN_PIN                    A5 // LED ENABLE pin
#define HS_BAT_CABLE_PIN                    A7 // USB insertion detection pin
// #define HS_LED_BOOSTING_PIN                 D2 // LED BOOSTING,Power boost pin

#define BAT_FULL_PIN                        A15
#define BAT_FULL_STATE                      1

#define HS_RGB_INDICATOR_COUNT              87
#define HS_RGB_BAT_COUNT                    1

/* Device Name Definition */
#define MD_BT1_NAME "EPOMAKER TIDE75"
#define MD_BT2_NAME "EPOMAKER TIDE75"
#define MD_BT3_NAME "EPOMAKER TIDE75"
#define MD_DONGLE_MANUFACTURER "EPOMAKER TIDE 75"

/* Device Connection RGB Indicator Light Index And Color */
#define HS_RGB_BLINK_INDEX_BT1 52
#define HS_RGB_BLINK_INDEX_BT2 51
#define HS_RGB_BLINK_INDEX_BT3 50
#define HS_RGB_BLINK_INDEX_2G4 43
#define HS_RGB_BLINK_INDEX_USB 48

#define HS_LBACK_COLOR_BT1 RGB_BLUE
#define HS_LBACK_COLOR_BT2 RGB_BLUE
#define HS_LBACK_COLOR_BT3 RGB_BLUE
#define HS_LBACK_COLOR_2G4 RGB_GREEN
#define HS_LBACK_COLOR_USB RGB_WHITE

#define HS_PAIR_COLOR_BT1 RGB_BLUE
#define HS_PAIR_COLOR_BT2 RGB_BLUE
#define HS_PAIR_COLOR_BT3 RGB_BLUE
#define HS_PAIR_COLOR_2G4 RGB_GREEN

#define WIITE_B 0X6e

/* Battery */
#define BATTERY_CAPACITY_LOW 15
#define BATTERY_CAPACITY_STOP 0
#define RGB_MATRIX_BAT_INDEX_MAP {26, 27, 28, 29, 30, 31, 32, 33, 34, 35}

/* Status Indicator Lamp */
#define HS_MATRIX_BLINK_INDEX_BAT           2
#define HS_RGB_INDEX_CAPS                   54
#define HS_RGB_INDEX_WIN_LOCK               85
#define HS_RGB_BLINK_INDEX_VAI              68
#define HS_RGB_BLINK_INDEX_VAD              5
#define HS_RGB_BLINK_INDEX_SPI              6
#define HS_RGB_BLINK_INDEX_SPD              4

#define HS_RGB_BLINK_INDEX_WIN              55
#define HS_RGB_BLINK_INDEX_MAC              56

/* UART */
#define SERIAL_DRIVER SD1
#define SD1_TX_PIN C10
#define SD1_RX_PIN C11

/* UART for wireless module */
#define UART_RX_PIN C11
#define UART_RX_PAL_MODE 7
#define UART_TX_PIN C10
#define UART_TX_PAL_MODE 7

/* Encoder */
#define ENCODER_MAP_KEY_DELAY               1
#define ENCODER_RESOLUTION                  2

/* SPI */
#define SPI_DRIVER                          SPIDQ
#define SPI_SCK_PIN                         B3
#define SPI_MOSI_PIN                        B5
#define SPI_MISO_PIN                        B4

/* Flash */
#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN C12
#define WEAR_LEVELING_LOGICAL_SIZE          (WEAR_LEVELING_BACKING_SIZE / 2)

/* RGB Matrix */
#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_RGB
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES

/* RGB Light */
#define RGBLED_NUM 8
#define RGBLIGHT_CUSTOM_DRIVER
#define RGBLIGHT_DISABLE_KEYCODES
#define BREATHING_VAL           40
#define RAINBOW_MOOD            40
#define LED_TYPE                RGB
#define RGBLIGHT_LED_MAP {0, 1, 2, 3, 4, 5, 6, 7}

/* WS2812 */
#define WS2812_SPI_DRIVER       SPIDM2
#define WS2812_SPI_DIVISOR      32

/* rgb_record */
#define ENABLE_RGB_MATRIX_RGBR_PLAY
#define RGBREC_CHANNEL_NUM         4
#define EECONFIG_CONFINFO_USE_SIZE (4 + 16)
#define EECONFIG_RGBREC_USE_SIZE   (RGBREC_CHANNEL_NUM * MATRIX_ROWS * MATRIX_COLS * 2)
#define EECONFIG_USER_DATA_SIZE    (EECONFIG_RGBREC_USE_SIZE + EECONFIG_CONFINFO_USE_SIZE)
#define RGBREC_EECONFIG_ADDR       (uint8_t *)(EECONFIG_USER_DATABLOCK)
#define CONFINFO_EECONFIG_ADDR     (uint32_t *)((uint32_t)RGBREC_EECONFIG_ADDR + (uint32_t)EECONFIG_RGBREC_USE_SIZE)

/* Matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 15

/* Matrix pin configuration */
#define MATRIX_ROW_PINS { A0, A1, A2, A3, A4, C13 }
#define MATRIX_COL_PINS { C0, C1, C2, C3, A6, B10, B11, B12, B13, B14, A10, C6, C7, C8, C9 }
