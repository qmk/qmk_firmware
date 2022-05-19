#pragma once

#include "config_common.h"

/* USB DEVICE DESCRIPTOR */
#define PRODUCT The Bastard Keyboards Blackpill
#define MANUFACTURER Bastard Keyboards x KarlK90
#define VENDOR_ID 0xA8F8
#define PRODUCT_ID 0x1828
#define DEVICE_VER 0x0001

/* MATRIX CONFIG */
#define MATRIX_COLS 5
#define MATRIX_ROWS 8
#define MATRIX_ROW_PINS \
     { A2, B8, A8, B9 }
 #define MATRIX_COL_PINS \
     { B1, B10, B3, B4, B5 }

#define DIODE_DIRECTION ROW2COL
// #define DEBUG_MATRIX_SCAN_RATE
//


/* RGB CONFIG - WS2812 DRIVER */
#define RGB_DI_PIN A1
#define RGBLED_NUM 36
#define RGBLED_SPLIT \
     { 18, 18 }
#define WS2812_EXTERNAL_PULLUP
#define WS2812_PWM_DRIVER PWMD2
#define WS2812_PWM_CHANNEL 2
#define WS2812_PWM_PAL_MODE 1
#define WS2812_DMA_CHANNEL 3
#define WS2812_DMA_STREAM STM32_DMA1_STREAM1
// Without the following configurations the WS2812 would not light up
#define WS2812_PWM_TARGET_PERIOD 800000

/* RGB matrix support. */
#ifdef RGB_MATRIX_ENABLE
#    define SPLIT_TRANSPORT_MIRROR
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define RGB_MATRIX_SPLIT RGBLED_SPLIT
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 50
#    define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
#    define RGB_DISABLE_WHEN_USB_SUSPENDED
#    define RGB_MATRIX_KEYPRESSES
#endif

/* CRC DRIVER 
#define CRC8_USE_TABLE
#define CRC8_OPTIMIZE_SPEED
*/
/* SPLIT CONFIG */
#define SPLIT_HAND_PIN A3

/* SERIAL SPLIT DRIVER */
#define SOFT_SERIAL_PIN A9  // D0 or D1, D2, D3, E6
#define SELECT_SOFT_SERIAL_SPEED 1 // or 0, 2, 3, 4, 5
                                    //  0: about 189kbps (Experimental only)
                                    //  1: about 137kbps (default)
                                    //  2: about 75kbps
                                    //  3: about 39kbps
                                    //  4: about 26kbps
                                    //  5: about 20kbps
//#define SERIAL_USART_TX_PIN A9
// To use the highest possible baudrate (3.75Mbit/s) uncomment the following
// line, this can result in dropped communications so lower the speed if there
// are many timeouts. #define SERIAL_USART_SPEED (STM32_PCLK2 >> 4)

/* SPI DRIVER 
*/
//#define SPI_DRIVER SPID1
//#define SPI_SCK_PIN A5
//&#define SPI_MOSI_PIN B7
//#define SPI_MISO_PIN A6
/* EEPROM DRIVER */
//#define EXTERNAL_EEPROM_SPI_SLAVE_SELECT_PIN A4

/* PMW3360 DRIVER */
//#define PMW3360_CS_PIN B14
//
/* Top left key on left half */
 #define BOOTMAGIC_LITE_ROW    0
 #define BOOTMAGIC_LITE_COLUMN 0
 /* Top right key on right half */
 #define BOOTMAGIC_LITE_ROW_RIGHT    4
 #define BOOTMAGIC_LITE_COLUMN_RIGHT 4
