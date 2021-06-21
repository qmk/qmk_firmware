#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x6060
#define DEVICE_VER 0x0002
#define MANUFACTURER Neilzx - Design
#define PRODUCT Final80 % v2
#define DESCRIPTION STM32 based 80% keyboard with full rgb, oled and encoder.

/* key matrix set */
#define MATRIX_ROWS 6
#define MATRIX_COLS 15

#define MATRIX_ROW_PINS { A10, A9, A1, A0, B8, B9 }
#define MATRIX_COL_PINS { A8, B15, B14, B13, B12, B11, B10, B1, B0, A6, A5, A4, A3, A2, C13 }
#define DIODE_DIRECTION ROW2COL
#define DEBOUNCE 5

/* RGN Matrix */
#ifdef RGB_MATRIX_ENABLE
#    define RGB_DI_PIN A7
#    define RGBLED_NUM 100
#    define DRIVER_LED_TOTAL RGBLED_NUM

#    define WS2812_PWM_DRIVER PWMD3               // default: PWMD2
#    define WS2812_PWM_CHANNEL 2                  // default: 2
#    define WS2812_PWM_PAL_MODE 2                 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 2
#    define WS2812_DMA_STREAM STM32_DMA1_STREAM3  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#    define WS2812_DMA_CHANNEL 3                  // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.

#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255     // 最大亮度限制
#    define RGB_DISABLE_WHEN_USB_SUSPENDED true
#    define RGB_MATRIX_CENTER { 96, 32 }
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#endif

/* Encoder */
#ifdef ENCODER_ENABLE
#    define ENCODERS_PAD_A { B4 }
#    define ENCODERS_PAD_B { B5 }
#    define ENCODER_RESOLUTION 4
//#    define ENCODER_DIRECTION_FLIP  // 如果旋钮反向，启用此处
#endif

/* MOUSEKEY */
#ifdef MOUSEKEY_ENABLE
#    define MOUSEKEY_DELAY 0
#    define MOUSEKEY_INTERVAL 17
#    define MK_3_SPEED
#    define MK_MOMENTARY_ACCEL
#    define MK_C_OFFSET_UNMOD 64   // MOUSEKEY移动鼠标指针一次64像素
#    define MK_C_INTERVAL_UNMOD 17
#endif

/* OLED */
#ifdef OLED_DRIVER_ENABLE
#    define OLED_DISPLAY_128X64
#    define I2C_DRIVER I2CD1
//#    define OLED_IC OLED_IC_SH1106  // 选用1.3寸SH1106主控OLED时打开, 0.96寸SSD1306主控OLED注释掉本行。
//#    define OLED_COLUMN_OFFSET 2  // 调整OLED纵向偏移，0.96寸SSD1306主控OLED注释掉本行。
#    define I2C1_TIMINGR_PRESC 0U
#    define I2C1_TIMINGR_SCLDEL 7U
#    define I2C1_TIMINGR_SDADEL 0U
#    define I2C1_TIMINGR_SCLH 38U
#    define I2C1_TIMINGR_SCLL 129U
#    define OLED_TIMEOUT 60000  // 60秒无操作关闭OLED
#    define OLED_FONT_HEIGHT 8
#    define OLED_FONT_WIDTH 6
#    define OLED_FONT_H "neil_font.c"
#endif

/* Others */
#define TAP_HOLD_CAPS_DELAY 10

#ifdef CONSOLE_ENABLE
#    define DEBUG_MATRIX_SCAN_RATE
#endif
#endif
