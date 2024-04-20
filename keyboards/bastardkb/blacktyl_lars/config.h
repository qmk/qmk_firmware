#pragma once

/* USB DEVICE DESCRIPTOR */

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
#define WS2812_DI_PIN A1
#define RGB_MATRIX_LED_COUNT 36
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

#define ENABLE_RGB_MATRIX_ALPHAS_MODS   Enables RGB_MATRIX_ALPHAS_MODS
  #define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
  #define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
  #define ENABLE_RGB_MATRIX_BREATHING
  #define ENABLE_RGB_MATRIX_BAND_SAT
  #define ENABLE_RGB_MATRIX_BAND_VAL
  #define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
  #define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
  #define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
  #define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
  #define ENABLE_RGB_MATRIX_CYCLE_ALL
  #define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
  #define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
  #define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
  #define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
  #define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
  #define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
  #define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
  #define ENABLE_RGB_MATRIX_DUAL_BEACON
  #define ENABLE_RGB_MATRIX_RAINBOW_BEACON
  #define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
  #define ENABLE_RGB_MATRIX_RAINDROPS
  #define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
  #define ENABLE_RGB_MATRIX_HUE_BREATHING
  #define ENABLE_RGB_MATRIX_HUE_PENDULUM
  #define ENABLE_RGB_MATRIX_HUE_WAVE
  #define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
  #define ENABLE_RGB_MATRIX_PIXEL_FLOW
  #define ENABLE_RGB_MATRIX_PIXEL_RAIN
