
#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    blockboy
#define PRODUCT         FK680ProV2
#define RAW_USAGE_PAGE  0xFF60
#define RAW_USAGE_ID    0x61

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/* key matrix pins */
#define MATRIX_ROW_PINS { B3, B4, B5, B6, B7 }
#define MATRIX_COL_PINS { A4, A5, A6, A7, B0, B1, B10, B11, B12, B13, B14, B15, A8, A9, A10 }

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5


/* RGN Matrix */
#ifdef RGB_MATRIX_ENABLE
#    define RGB_DI_PIN A15
#    define RGBLED_NUM 110
#    define DRIVER_LED_TOTAL RGBLED_NUM

#    define RGBLIGHT_ANIMATIONS

#    define WS2812_PWM_DRIVER PWMD1               // default: PWMD2
#    define WS2812_PWM_CHANNEL 2                  // default: 2
#    define WS2812_PWM_COMPLEMENTARY_OUTPUT       // Define for a complementary timer output (TIMx_CHyN); omit for a normal timer output (TIMx_CHy).
#    define WS2812_PWM_PAL_MODE 2                 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 2
#    define WS2812_DMA_STREAM STM32_DMA1_STREAM1  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#    define WS2812_DMA_CHANNEL 2                  // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
//#    define WS2812_DMAMUX_ID STM32_DMAMUX1_TIM1_UP// DMAMUX configuration for TIMx_UP -- only required if your MCU has a DMAMUX peripheral, see the respective reference manual for the appropriate values for your MCU.

#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255     // 最大亮度限制

#    define RGB_MATRIX_KEYPRESSES

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
#define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#define ENABLE_RGB_MATRIX_PIXEL_FLOW
#define ENABLE_RGB_MATRIX_PIXEL_RAIN

#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#define ENABLE_RGB_MATRIX_DIGITAL_RAIN

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
#endif

#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8

/* 将USB 轮询速率更改为 1000hz 并为精英游戏每次扫描使用更大的密钥*/
#define USB_POLLING_INTERVAL_MS  2
#define QMK_KEYS_PER_SCAN  12


/* OLED */
// #    define I2C_DRIVER I2CD1
// #    define I2C1_SCL_PIN B6
// #    define I2C1_SCL_PAL_MODE 4
// #    define I2C1_SDA_PIN B7
// #    define I2C1_SDA_PAL_MODE 4

// #    define I2C1_OPMODE OPMODE_I2C
// #    define I2C1_CLOCK_SPEED 100000
// #    define I2C1_DUTY_CYCLE STD_DUTY_CYCLE

// #    define OLED_DISPLAY_128X32
// #    define OLED_TIMEOUT 60000  // 60秒无操作关闭OLED
// #    define OLED_FONT_HEIGHT 8
// #    define OLED_FONT_WIDTH 6
// #    define OLED_FONT_H "neil_font.c"

// #define WS2812_PWM_DRIVER PWMD3
// #define WS2812_PWM_CHANNEL 4
// #define WS2812_PWM_PAL_MODE 2
// #define WS2812_DMA_STREAM STM32_DMA1_STREAM2
// #define WS2812_DMA_CHANNEL 5
// #define WS2812_DMAMUX_ID STM32_DMAMUX1_TIM2_UP
