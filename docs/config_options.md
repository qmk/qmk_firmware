# The `config.h` file

This is a c header file that is one of the first things included, and will persist over the whole project (if included). Lots of variables can be set here and accessed elsewhere (namely keymaps). This file can exist at a couple different levels:

## Keyboard

```c
#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

// config options

#endif
```

This file contains config options that should apply to the whole keyboard, and won't change in revisions, or most keymaps. The revision block here only applies to keyboards with revisions.

## Revisions

```c
#ifndef <revision>_CONFIG_H
#define <revision>_CONFIG_H

#include "config_common.h"

// config options

#endif
```

For keyboards that have revisions, this file contains config options that should apply to only that revisions, and won't change in most keymaps.

## Keymap

```c
#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "config_common.h"

// config options

#endif
```

This file contains all of the options for that particular keymap. If you wish to override a previous declaration, you can use `#undef <variable>` to undefine it, where you can then redefine it without an error.

# Config Options

```c
#define VENDOR_ID 0x1234 // defines your VID, and for most DIY projects, can be whatever you want
#define PRODUCT_ID 0x5678 // defines your PID, and for most DIY projects, can be whatever you want  
#define DEVICE_VER 0 // defines the device version (often used for revisions)

#define MANUFACTURER Me // generally who/whatever brand produced the board
#define PRODUCT Board // the name of the keyboard
#define DESCRIPTION a keyboard // a short description of what the keyboard is

#define MATRIX_ROWS 5 // the number of rows in your keyboard's matrix
#define MATRIX_COLS 15 // the number of columns in your keyboard's matrix

#define MATRIX_ROW_PINS { D0, D5, B5, B6 } // pins of the rows, from top to bottom
#define MATRIX_COL_PINS { F1, F0, B0, C7, F4, F5, F6, F7, D4, D6, B4, D7 } // pins of the columns, from left to right
#define UNUSED_PINS { D1, D2, D3, B1, B2, B3 } // pins unused by the keyboard for reference 
#define MATRIX_HAS_GHOST // define is matrix has ghost (unlikely)
#define DIODE_DIRECTION COL2ROW // COL2ROW or ROW2COL - how your matrix is configured
// COL2ROW means the black mark on your diode is facing to the rows, and between the switch and the rows

#define AUDIO_VOICES // turns on the alternate audio voices (to cycle through)
#define C6_AUDIO // enables audio on pin C6
#define B5_AUDIO // enables audio on pin B5 (duophony is enable if both are enabled)

#define BACKLIGHT_PIN B7 // pin of the backlight - B5, B6, B7 use PWM, others use softPWM
#define BACKLIGHT_LEVELS 3 // number of levels your backlight will have (not including off)

#define DEBOUNCING_DELAY 5 // the delay when reading the value of the pin (5 is default)

#define LOCKING_SUPPORT_ENABLE // mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap
#define LOCKING_RESYNC_ENABLE // tries to keep switch state consistent with keyboard LED state

#define IS_COMMAND() ( \ // key combination that allows the use of magic commands (useful for debugging)
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

// the following options can save on file size at the expense of that feature
#define NO_DEBUG // disable debuging (saves on file size)
#define NO_PRINT // disable printing (saves of file size)
#define NO_ACTION_LAYER // no layers
#define NO_ACTION_TAPPING // no tapping for layers/mods
#define NO_ACTION_ONESHOT // no oneshot for layers/mods
#define NO_ACTION_MACRO // no macros
#define NO_ACTION_FUNCTION // no functions

#define FORCE_NKRO // NKRO by default requires to be turned on, this forces it to be on always

#define PREVENT_STUCK_MODIFIERS // when switching layers, this will release all mods

#define TAPPING_TERM 200 // how long before a tap becomes a hold
#define TAPPING_TOGGLE 2 // how many taps before triggering the toggle

#define PERMISSIVE_HOLD // makes tap and hold keys work better for fast typers who don't want tapping term set above 500

#define LEADER_TIMEOUT 300 // how long before the leader key times out

#define ONESHOT_TIMEOUT 300 // how long before oneshot times out
#define ONESHOT_TAP_TOGGLE 2 // how many taps before oneshot toggle is triggered

#define IGNORE_MOD_TAP_INTERRUPT // makes it possible to do rolling combos (zx) with keys that convert to other keys on hold

// ws2812 options
#define RGB_DI_PIN D7 // pin the DI on the ws2812 is hooked-up to
#define RGBLIGHT_ANIMATIONS // run RGB animations
#define RGBLED_NUM 15 // number of LEDs
#define RGBLIGHT_HUE_STEP 12 // units to step when in/decreasing hue
#define RGBLIGHT_SAT_STEP 25 // units to step when in/decresing saturation
#define RGBLIGHT_VAL_STEP 12 // units to step when in/decreasing value (brightness)

#define RGBW_BB_TWI // bit-bangs twi to EZ RGBW LEDs (only required for Ergodox EZ)

// mousekey options (self-describing)
#define MOUSEKEY_INTERVAL 20
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_TIME_TO_MAX 60
#define MOUSEKEY_MAX_SPEED 7
#define MOUSEKEY_WHEEL_DELAY 0

```