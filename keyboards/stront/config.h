// Copyright 2023 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* stront specific options */
#define STRONT_DISPLAY_LEFT // display is on left by default
#define STRONT_DISPLAY_ROTATION QP_ROTATION_180
#ifdef QUANTUM_PAINTER_ST7789_SPI_ENABLE // default settings for ST7789 1.69" display
#    define STRONT_DISPLAY_WIDTH 240
#    define STRONT_DISPLAY_HEIGHT 280
#    define STRONT_DISPLAY_OFFSET_X 0
#    define STRONT_DISPLAY_OFFSET_Y 20
#endif

/* interconnect config */
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_PIN_SWAP
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1

/* reset config */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

/* any side can be master by default, enable split sync to support it */
#define EE_HANDS
#define SPLIT_POINTING_ENABLE

/* common SPI/I2C config */
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN GP10
#define SPI_MOSI_PIN GP11
#define SPI_MISO_PIN GP12
#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP10
#define I2C1_SCL_PIN GP11

/* common touchpad config */
#define POINTING_DEVICE_RIGHT // touchpad is right by default
#define POINTING_DEVICE_CS_PIN GP9
#ifdef POINTING_DEVICE_DRIVER_azoteq_iqs5xx
#    define AZOTEQ_IQS5XX_TPS43
#    define AZOTEQ_IQS5XX_ROTATION_270
#else
#    define CIRQUE_PINNACLE_DIAMETER_MM 40
// #    define CIRQUE_PINNACLE_ATTENUATION EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_2X // enable for curved overlay
#    ifdef POINTING_DEVICE_RIGHT
#        define POINTING_DEVICE_ROTATION_180
#    endif
#endif

/* common LCD config */
#define LCD_DC_PIN GP12
#define LCD_CS_PIN GP9
#define LCD_RST_PIN GP13
#define BACKLIGHT_PWM_DRIVER PWMD7
#define BACKLIGHT_PWM_CHANNEL RP2040_PWM_CHANNEL_A
#define QUANTUM_PAINTER_DISPLAY_TIMEOUT 0

/* RGB config */
#ifdef RGB_MATRIX_ENABLE
#    define SPLIT_TRANSPORT_MIRROR
#endif
