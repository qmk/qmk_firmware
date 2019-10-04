#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x4443 // "DC" = Don Chiou
#define PRODUCT_ID      0x5350 // "SP" = Snagpad
#define DEVICE_VER      0x0001
#define MANUFACTURER    Flehrad
#define PRODUCT         Snagpad
#define DESCRIPTION     A Pro Micro-Powered 5x4 macropad/numpad

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 4

/* key matrix pins */
#define MATRIX_ROW_PINS { D1, D0, D4, C6, D7 }
#define MATRIX_COL_PINS { F4, F5, F6, F7 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* number of backlight levels */

#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 3
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* prevent stuck modifiers */
//#define STRICT_LAYER_RELEASE

#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 0
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif

// Does not use WT_MONO_BACKLIGHT
// #define WT_MONO_BACKLIGHT

#define DYNAMIC_KEYMAP_LAYER_COUNT 4

// EEPROM usage

// TODO: refactor with new user EEPROM code (coming soon)
#define EEPROM_MAGIC 0x451F
#define EEPROM_MAGIC_ADDR 34
// Bump this every time we change what we store
// This will automatically reset the EEPROM with defaults
// and avoid loading invalid data from the EEPROM
#define EEPROM_VERSION 0x08
#define EEPROM_VERSION_ADDR 36

// Dynamic keymap starts after EEPROM version
#define DYNAMIC_KEYMAP_EEPROM_ADDR 37
// Dynamic macro starts after dynamic keymaps (37+(4*5*4*2)) = (37+160)
#define DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR 197
#define DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE 827
#define DYNAMIC_KEYMAP_MACRO_COUNT 16