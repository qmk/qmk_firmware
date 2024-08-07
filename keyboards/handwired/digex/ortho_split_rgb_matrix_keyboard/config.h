/* Copyright 2020 petrvden */

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
//#define VENDOR_ID       0x7654
//#define PRODUCT_ID      0x0060
//#define DEVICE_VER      0x0003

//#define FEE_MCU_FLASH_SIZE 64
//#define GD32VF103C8

//#define MANUFACTURER    digex
//#define PRODUCT         handwired rgb split keyboard

/* key matrix size */
//#define MATRIX_ROWS 10 // Rows are doubled-up
//#define MATRIX_COLS 8

#define PERMISSIVE_HOLD

//#define MATRIX_COL_PINS           { A1, A6, A7, B0, B1, B10, B11, NO_PIN }
//#define MATRIX_COL_PINS_RIGHT     { A8, A1, A6, A7, B0, B1,  B10, B11 }
//
//
//#define MATRIX_ROW_PINS_RIGHT { B15, B14, B13, B12, A15 }
//#define MATRIX_ROW_PINS       { B15, B14, B13, B12, A15 }
/* COL2ROW, ROW2COL*/
//#define DIODE_DIRECTION ROW2COL

#define MATRIX_IO_DELAY 5


#define BOOTMAGIC_ROW 0
#define BOOTMAGIC_COLUMN 0


// mouse settings

#define MK_KINETIC_SPEED
#define MOUSEKEY_DELAY              5
#define MOUSEKEY_INTERVAL           10
#define MOUSEKEY_MOVE_DELTA         16
#define MOUSEKEY_INITIAL_SPEED      10
#define MOUSEKEY_DECELERATED_SPEED  10
#define MOUSEKEY_BASE_SPEED         5000
#define MOUSEKEY_ACCELERATED_SPEED  4800
#define MOUSEKEY_WHEEL_INITIAL_MOVEMENTS 		16
#define MOUSEKEY_WHEEL_BASE_MOVEMENTS 			128
#define MOUSEKEY_WHEEL_ACCELERATED_MOVEMENTS 	48
#define MOUSEKEY_WHEEL_DECELERATED_MOVEMENTS 	8



#define   	SPLIT_HAND_PIN_LOW_IS_LEFT
//#define 	SPLIT_HAND_PIN  B3
//#define MASTER_RIGHT
//#define MASTER_LEFT
//#define SPLIT_USB_DETECT






#define SERIAL_USART_FULL_DUPLEX   // Enable full duplex operation mode.
//#define SERIAL_USART_TX_PIN B6     // USART TX pin
#define SERIAL_USART_RX_PIN B7     // USART RX pin
#define USART1_REMAP             // Remap USART TX and RX pins on STM32F103 MCUs, see table below.
//#define SERIAL_USART_PIN_SWAP    // Swap TX and RX pins if keyboard is master halve.
                                   // Check if this feature is necessary with your keyboard design and available on the mcu.
#define SELECT_SOFT_SERIAL_SPEED 1 // or 0, 2, 3, 4, 5

#define SOFT_SERIAL_PIN B6


#define WS2812_PWM_DRIVER PWMD3
#define WS2812_PWM_CHANNEL 1
#define WS2812_DMA_STREAM STM32_DMA1_STREAM3
#define WS2812_DMA_CHANNEL 3

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

///* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE
///* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE

#define SPLIT_CONNECTION_CHECK_TIMEOUT 1000
#define SPLIT_TRANSPORT_MIRROR
//#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE

#ifdef RGB_MATRIX_ENABLE
//#define RGB_MATRIX_LED_COUNT 72 // Number of LEDs
//#define RGBLED_NUM       72 // Number of LEDs
//#define DRIVER_LED_TOTAL RGBLED_NUM
//#define RGB_MATRIX_SPLIT     { 35, 37 }

//#define  WS2812_DI_PIN B4
// RGB Matrix Animation modes. Explicitly enabled
// For full list of effects, see:
// https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects
//#define ENABLE_RGB_MATRIX_ALPHAS_MODS
//#define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
//#define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
//#define ENABLE_RGB_MATRIX_BREATHING
//#define ENABLE_RGB_MATRIX_BAND_SAT
//#define ENABLE_RGB_MATRIX_BAND_VAL
//#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
//#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
//#define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
//#define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
//#define ENABLE_RGB_MATRIX_CYCLE_ALL
//#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
//#define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
//#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
//#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
//#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
//#define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
//#define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
//#define ENABLE_RGB_MATRIX_DUAL_BEACON
//#define ENABLE_RGB_MATRIX_RAINBOW_BEACON
//#define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
//#define ENABLE_RGB_MATRIX_RAINDROPS
//#define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
//#define ENABLE_RGB_MATRIX_HUE_BREATHING
//#define ENABLE_RGB_MATRIX_HUE_PENDULUM
//#define ENABLE_RGB_MATRIX_HUE_WAVE
//#define ENABLE_RGB_MATRIX_PIXEL_RAIN
//#define ENABLE_RGB_MATRIX_PIXEL_FLOW
//#define ENABLE_RGB_MATRIX_PIXEL_FRACTAL 
//// enabled only if RGB_MATRIX_FRAMEBUFFER_EFFECTS is defined
//#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
//#define ENABLE_RGB_MATRIX_DIGITAL_RAIN
//// enabled only of RGB_MATRIX_KEYPRESSES or RGB_MATRIX_KEYRELEASES is defined
//#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
//#define ENABLE_RGB_MATRIX_SOLID_REACTIVE
//#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
//#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
//#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
//#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
//#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
//#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
//#define ENABLE_RGB_MATRIX_SPLASH
//#define ENABLE_RGB_MATRIX_MULTISPLASH
//#define ENABLE_RGB_MATRIX_SOLID_SPLASH
//#define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
        
//#define RGB_MATRIX_SOLID_REACTIVE_GRADIENT_MODE

//#define RGBLIGHT_LAYERS_RETAIN_VAL

#define  RGB_MATRIX_KEYPRESSES  // реагирует на нажатия клавиш 
#define  RGB_MATRIX_FRAMEBUFFER_EFFECTS  // включение эффектов кадрового буфера 
#define  RGB_MATRIX_TIMEOUT  0  // количество миллисекунд ожидания до автоматического отключения rgb 
//#define  RGB_DISABLE_AFTER_TIMEOUT  0  / / УСТАРЕЛО: количество тиков ожидания до отключения эффектов 
//#define  RGB_MATRIX_SLEEP   //отключать эффекты при приостановке 
/* If defined, GRAVE_ESC will always act as ESC when CTRL is held.
 * This is userful for the Windows task manager shortcut (ctrl+shift+esc).
 */
// #define GRAVE_ESC_CTRL_OVERRIDE
#endif
/*
 * Force NKRO
 *
 * Force NKRO (nKey Rollover) to be enabled by default, regardless of the saved
 * state in the bootmagic EEPROM settings. (Note that NKRO must be enabled in the
 * makefile for this to work.)
 *
 * If forced on, NKRO can be disabled via magic key (default = LShift+RShift+N)
 * until the next keyboard reset.
 *
 * NKRO may prevent your keystrokes from being detected in the BIOS, but it is
 * fully operational during normal computer usage.
 *
 * For a less heavy-handed approach, enable NKRO via magic key (LShift+RShift+N)
 * or via bootmagic (hold SPACE+N while plugging in the keyboard). Once set by
 * bootmagic, NKRO mode will always be enabled until it is toggled again during a
 * power-up.
 *
 */
//#define FORCE_NKRO

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

/* disable these deprecated features by default */
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION
    
    

//#define TAPPING_TERM_PER_KEY