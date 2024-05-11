/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <https://github.com/Legonut> wrote this file.  As long as you retain this
 * notice you can do whatever you want with this stuff. If we meet some day, and
 * you think this stuff is worth it, you can buy me a beer in return. David Rauseo
 * ----------------------------------------------------------------------------
 */

#pragma once

#define BUSY_WAIT
#define BUSY_WAIT_INSTRUCTIONS 35 // Increase if two rows are pressed at the same time.
#define GPIO_INPUT_PIN_DELAY 10

/* Touchbar adjustments */
#define TOUCH_DEADZONE 50 // width of a "button", wider inputs will be interpreted as a swipe
#define TOUCH_TERM 350 // time of a "button" touch, longer inputs will be a swipe
#define TOUCH_RESOLUTION 25 // sensitivity of swipes, lower=faster
#define TOUCH_SEGMENTS 3

/* CRC Configuration */
#define CRC8_OPTIMIZE_SPEED
#define CRC8_USE_TABLE

/* Split Keyboard Configuration */
#define EE_HANDS
#define SPLIT_USB_DETECT
#define SERIAL_USART_TX_PAL_MODE 7
#define SERIAL_USART_TIMEOUT 5
#define SERIAL_USART_DRIVER SD1
//#define SERIAL_USART_FULL_DUPLEX - Waiting on reunification pr
#if SERIAL_USART_FULL_DUPLEX
    #define SERIAL_USART_RX_PIN A10
    #define SERIAL_USART_RX_PAL_MODE 7
    // Mun connects TX to TX and RX to RX as we were planning on i2c split, so we need pin swap for full duplex
    #define SERIAL_USART_PIN_SWAP
    #define SERIAL_USART_SPEED (2 * 1024 * 1024)
#else
    #define SERIAL_USART_SPEED (1 * 1024 * 1024)
#endif

/* Split Transport Features */
#define SPLIT_TRANSACTION_IDS_KB TOUCH_ENCODER_SYNC, RGB_MENU_SYNC

#if RGB_UNLIMITED_POWER
  #define RGBLIGHT_LIMIT_VAL 255
  #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255
#else
  #define RGBLIGHT_LIMIT_VAL 127
  #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 127
#endif

#define WS2812_PWM_DRIVER PWMD3
#define WS2812_PWM_CHANNEL 2
#define WS2812_PWM_PAL_MODE 2
#define WS2812_PWM_DMA_STREAM STM32_DMA1_STREAM3
#define WS2812_PWM_DMA_CHANNEL 3

#define TOUCH_UPDATE_INTERVAL 33
#define OLED_UPDATE_INTERVAL 33
#define OLED_FONT_H "keyboards/rgbkb/common/glcdfont.c"
