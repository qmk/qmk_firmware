/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <https://github.com/Legonut> wrote this file.  As long as you retain this
 * notice you can do whatever you want with this stuff. If we meet some day, and
 * you think this stuff is worth it, you can buy me a beer in return. David Rauseo
 * ----------------------------------------------------------------------------
 */

#pragma once

#include "config_common.h"

/* Matrix Configuration - Rows are doubled up */
#define MATRIX_ROWS 12
// Last pins reserved for encoder / touch encoder support
#define MATRIX_ROW_PINS       { B15,  A8, A15, B12, A3, NO_PIN }
#define MATRIX_ROW_PINS_RIGHT { B15, B14,  A8, A13, A7, NO_PIN }
#define MATRIX_COLS 8
// Empty matrix entries used for encoder / touch encoder support
#define MATRIX_COL_PINS       { A6, A7, B0, B2, B1,  B9,  B3,  B4 }
#define MATRIX_COL_PINS_RIGHT { B9, B8, B4, A6, A3, B10, B12, B11 }
#define MATRIX_IO_DELAY 5

#define BUSY_WAIT
#define BUSY_WAIT_INSTRUCTIONS 35 // Increase if two rows are pressed at the same time.
#define GPIO_INPUT_PIN_DELAY 10

/* Touchbar adjustments */
#define TOUCH_DEADZONE 50 // width of a "button", wider inputs will be interpreted as a swipe
#define TOUCH_TERM 350 // time of a "button" touch, longer inputs will be a swipe
#define TOUCH_RESOLUTION 25 // sensitivity of swipes, lower=faster
#define TOUCH_SEGMENTS 3

/* Encoder Configuration */
//      Matrix Entries  k36/k35(E1SW>B13), k33/k32, k7/k28
#define ENCODERS_PAD_A { A1, B10, A13 }
#define ENCODERS_PAD_B { A2, B11, B14 }
//      Matrix Entries  k72/k71(E5SW>B0), k69/k68, k43/k64
#define ENCODERS_PAD_A_RIGHT { A1, C15,  B3 }
#define ENCODERS_PAD_B_RIGHT { A2, C14, B13 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* CRC Configuration */
#define CRC8_OPTIMIZE_SPEED
#define CRC8_USE_TABLE

/* Split Keyboard Configuration */
#define SPLIT_HAND_PIN C13
#define SPLIT_USB_DETECT
// also handles the SERIAL_USART_TX_PIN define
#define SOFT_SERIAL_PIN A9
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
#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_TRANSACTION_IDS_KB TOUCH_ENCODER_SYNC, RGB_MENU_SYNC

/* LED Turbo DIP Switch */
#define DIP_SWITCH_PINS { A14, B13 }
#define DIP_SWITCH_PINS_RIGHT { A14, B0 }

/* RGB LED Configuration */
#define RGB_DI_PIN B5
#define RGBLED_NUM 156
#define RGBLED_SPLIT { 78, 78 }
#define RGBLIGHT_LIMIT_VAL 255

// RGB Lighting Animation modes. Explicitly enabled
// For full list of effects, see:
// https://docs.qmk.fm/#/feature_rgblight?id=effect-and-animation-toggles
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_TWINKLE

#define DRIVER_LED_TOTAL RGBLED_NUM
#define RGB_MATRIX_SPLIT RGBLED_SPLIT
#define RGB_MATRIX_CENTER { 81, 28 }
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS RGBLIGHT_LIMIT_VAL
#define RGB_MATRIX_LED_FLUSH_LIMIT 33
#define RGB_MATRIX_LED_PROCESS_LIMIT 10
#define RGB_DISABLE_WHEN_USB_SUSPENDED

// RGB Matrix Animation modes. Explicitly enabled
// For full list of effects, see:
// https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects
#define ENABLE_RGB_MATRIX_ALPHAS_MODS
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
#define ENABLE_RGB_MATRIX_PIXEL_RAIN
#define ENABLE_RGB_MATRIX_PIXEL_FLOW
#define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
// enabled only if RGB_MATRIX_FRAMEBUFFER_EFFECTS is defined
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#define ENABLE_RGB_MATRIX_DIGITAL_RAIN
// enabled only of RGB_MATRIX_KEYPRESSES or RGB_MATRIX_KEYRELEASES is defined
#define RGB_MATRIX_KEYPRESSES
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#define ENABLE_RGB_MATRIX_SPLASH
#define ENABLE_RGB_MATRIX_MULTISPLASH
#define ENABLE_RGB_MATRIX_SOLID_SPLASH
#define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH

#define WS2812_PWM_DRIVER PWMD3
#define WS2812_PWM_CHANNEL 2
#define WS2812_PWM_PAL_MODE 2
#define WS2812_DMA_STREAM STM32_DMA1_STREAM3
#define WS2812_DMA_CHANNEL 3

#define TOUCH_UPDATE_INTERVAL 33
#define OLED_UPDATE_INTERVAL 33
#define TAP_CODE_DELAY 5

/* Audio Configuration */
#define AUDIO_PIN A4
#define AUDIO_PIN_ALT A5
#define AUDIO_PIN_ALT_AS_NEGATIVE
#define AUDIO_CLICKY
#define AUDIO_DAC_SAMPLE_WAVEFORM_SQUARE
#define AUDIO_DAC_OFF_VALUE 0
