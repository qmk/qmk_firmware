// Copyright 2022 Kyle McCreery
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x6D77 // mw = "MechWild"
#define PRODUCT_ID      0x1710
#define DEVICE_VER      0x0001
#define MANUFACTURER    MechWild
#define PRODUCT         SugarGlider

/* Matrix COL and ROW definitions */
#define MATRIX_ROWS 9
#define MATRIX_COLS 6

/* Status light pins */
//#define LED_NUM_LOCK_PIN B12
//#define LED_CAPS_LOCK_PIN B13
//#define LED_SCROLL_LOCK_PIN B14
//#define LED_PIN_ON_STATE 0

#define USB_POLLING_INTERVAL_MS 1

/* Memory definitions for UF2 builds */
#ifdef UF2_BUILD
#define EXTERNAL_EEPROM_BYTE_COUNT 2048
#define EXTERNAL_EEPROM_PAGE_SIZE 128
#define EXTERNAL_EEPROM_ADDRESS_SIZE 1
#define EXTERNAL_EEPROM_WRITE_TIME 0
#define FEE_PAGE_BASE_ADDRESS 0x08008000
#endif

/* Define custom font */
#define OLED_FONT_H "keyboards/mechwild/sugarglider/glcdfont.c"

/* allows the "key" button on the blackpill to toggle caps lock for user testing before soldering */
#define DIP_SWITCH_PINS { A0 }

/* set the tapping term for glidepoint pad to register a tap click */
//#define CIRQUE_PINNACLE_TAPPING_TERM 0 // This is set to 0 to disable it

/* TAPPING_TERM value is used for the CIRQUE_PINNACLE_TAPPING_TERM as well by default
 * defining it this way allows us to easily modify it with DYNAMIC_TAPPING_TERM_ENABLE
 */
#define TAPPING_TERM 0

/* spi config */
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN A5
#define SPI_SCK_PAL_MODE 5
#define SPI_MOSI_PIN A7
#define SPI_MOSI_PAL_MODE 5
#define SPI_MISO_PIN A6
#define SPI_MISO_PAL_MODE 5
#define CIRQUE_PINNACLE_SPI_DIVISOR 8
#define CIRQUE_PINNACLE_SPI_CS_PIN A3

/* encoder pins */
#define ENCODERS_PAD_B { B0, B3, B9, C15 }
#define ENCODERS_PAD_A { A2, A15, B8, C14 }

/* encoder resolution */
#define ENCODER_RESOLUTION 4
#define TAP_CODE_DELAY 0

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* RGB settings, uncomment this define to enable RGB */
//#define RGB_DI_PIN B5
#ifdef RGB_DI_PIN
#    define RGBLED_NUM 6
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 8
#    define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
#    define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_SNAKE
#    define RGBLIGHT_EFFECT_KNIGHT
#    define RGBLIGHT_EFFECT_CHRISTMAS
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLIGHT_EFFECT_RGB_TEST
#    define RGBLIGHT_EFFECT_ALTERNATING
/*== customize breathing effect ==*/
/*==== (DEFAULT) use fixed table instead of exp() and sin() ====*/
//#    define RGBLIGHT_BREATHE_TABLE_SIZE 256      // 256(default) or 128 or 64
/*==== use exp() and sin() ====*/
//#    define RGBLIGHT_EFFECT_BREATHE_CENTER 1.85  // 1 to 2.7
//#    define RGBLIGHT_EFFECT_BREATHE_MAX    255   // 0 to 255
#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
// Debounce not used in this custom matrix implementation
//#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* If defined, GRAVE_ESC will always act as ESC when CTRL is held.
 * This is useful for the Windows task manager shortcut (ctrl+shift+esc).
 */
//#define GRAVE_ESC_CTRL_OVERRIDE

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
#define FORCE_NKRO

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

/* Bootmagic Lite key configuration */
//#define BOOTMAGIC_LITE_ROW 0
//#define BOOTMAGIC_LITE_COLUMN 0
