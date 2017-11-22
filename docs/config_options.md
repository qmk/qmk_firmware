# Configuring QMK

QMK is nearly infinitely configurable. Wherever possible we err on the side of allowing users to customize their keyboard, even at the expense of code size. That level of flexibility makes for a daunting configuration experience, however.

There are two main types of configuration files in QMK- `config.h` and `rules.mk`. These files exist at various levels in QMK and all files of the same type are combined to build the final configuration. The levels, from lowest priority to highest priority, are:

* QMK Default
* Keyboard
* Folders (Up to 5 levels deep)
* Keymap

## QMK Default

Every available setting in QMK has a default. If that setting is not set at the Keyboard, Folder, or Keymap level this is the setting that will be used.

## Keyboard

This level contains config options that should apply to the whole keyboard. Some settings won't change in revisions, or most keymaps. Other settings are merely defaults for this keyboard and can be overridden by folders and/or keymaps.

## Folders

Some keyboards have folders and sub-folders to allow for different hardware configurations. Most keyboards only go 1 folder deep, but QMK supports structures up to 5 folders deep. Each folder can have its own `config.h` and `rules.mk` files that are incorporated into the final configuration.

## Keymap

This level contains all of the options for that particular keymap. If you wish to override a previous declaration, you can use `#undef <variable>` to undefine it, where you can then redefine it without an error.

# The `config.h` file

This is a C header file that is one of the first things included, and will persist over the whole project (if included). Lots of variables can be set here and accessed elsewhere. The `config.h` file shouldn't be including other `config.h` files, or anything besides this:

    #include "config_common.h"

## `config.h` Options

### Hardware Options
* `#define VENDOR_ID 0x1234`
  * defines your VID, and for most DIY projects, can be whatever you want
* `#define PRODUCT_ID 0x5678`
  * defines your PID, and for most DIY projects, can be whatever you want
* `#define DEVICE_VER 0`
  * defines the device version (often used for revisions)
* `#define MANUFACTURER Me`
  * generally who/whatever brand produced the board
* `#define PRODUCT Board`
  * the name of the keyboard
* `#define DESCRIPTION a keyboard`
  * a short description of what the keyboard is
* `#define MATRIX_ROWS 5`
  * the number of rows in your keyboard's matrix
* `#define MATRIX_COLS 15`
  * the number of columns in your keyboard's matrix
* `#define MATRIX_ROW_PINS { D0, D5, B5, B6 }`
  * pins of the rows, from top to bottom
* `#define MATRIX_COL_PINS { F1, F0, B0, C7, F4, F5, F6, F7, D4, D6, B4, D7 }`
  * pins of the columns, from left to right
* `#define UNUSED_PINS { D1, D2, D3, B1, B2, B3 }`
  * pins unused by the keyboard for reference
* `#define MATRIX_HAS_GHOST`
  * define is matrix has ghost (unlikely)
* `#define DIODE_DIRECTION COL2ROW`
  * COL2ROW or ROW2COL - how your matrix is configured. COL2ROW means the black mark on your diode is facing to the rows, and between the switch and the rows.
* `#define AUDIO_VOICES`
  * turns on the alternate audio voices (to cycle through)
* `#define C6_AUDIO`
  * enables audio on pin C6
* `#define B5_AUDIO`
  * enables audio on pin B5 (duophony is enable if both are enabled)
* `#define BACKLIGHT_PIN B7`
  * pin of the backlight - B5, B6, B7 use PWM, others use softPWM
* `#define BACKLIGHT_LEVELS 3`
  * number of levels your backlight will have (not including off)
* `#define DEBOUNCING_DELAY 5`
  * the delay when reading the value of the pin (5 is default)
* `#define LOCKING_SUPPORT_ENABLE`
  * mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap
* `#define LOCKING_RESYNC_ENABLE`
  * tries to keep switch state consistent with keyboard LED state
* `#define IS_COMMAND() ( keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) )`
  * key combination that allows the use of magic commands (useful for debugging)

### Features That Can Be Disabled

If you define these options you will disable the associated feature, which can save on code size.

* `#define NO_DEBUG`
  * disable debuging
* `#define NO_PRINT`
  * disable printing/debugging using hid_listen
* `#define NO_ACTION_LAYER`
  * disable layers
* `#define NO_ACTION_TAPPING`
  * disable tap dance and other tapping features
* `#define NO_ACTION_ONESHOT`
  * disable one-shot modifiers
* `#define NO_ACTION_MACRO`
  * disable all macro handling
* `#define NO_ACTION_FUNCTION`
  * disable the action function (deprecated)

### Features That Can Be Enabled

If you define these options you will enable the associated feature, which may increase your code size.

* `#define FORCE_NKRO`
  * NKRO by default requires to be turned on, this forces it on during keyboard startup regardless of eeprom setting. NKRO can still be turned off but will be turned on again if the keyboard reboots.
* `#define PREVENT_STUCK_MODIFIERS`
  * when switching layers, this will release all mods

### Behaviors That Can Be Configured

* `#define TAPPING_TERM 200`
  * how long before a tap becomes a hold
* `#define RETRO_TAPPING`
  * tap anyway, even after TAPPING_TERM, if there was no other key interruption between press and release
* `#define TAPPING_TOGGLE 2`
  * how many taps before triggering the toggle
* `#define PERMISSIVE_HOLD`
  * makes tap and hold keys work better for fast typers who don't want tapping term set above 500
* `#define LEADER_TIMEOUT 300`
  * how long before the leader key times out
* `#define ONESHOT_TIMEOUT 300`
  * how long before oneshot times out
* `#define ONESHOT_TAP_TOGGLE 2`
  * how many taps before oneshot toggle is triggered
* `#define IGNORE_MOD_TAP_INTERRUPT`
  * makes it possible to do rolling combos (zx) with keys that convert to other keys on hold
* `#define QMK_KEYS_PER_SCAN 4`
  * Allows sending more than one key per scan. By default, only one key event gets
    sent via `process_record()` per scan. This has little impact on most typing, but
    if you're doing a lot of chords, or your scan rate is slow to begin with, you can
    have some delay in processing key events. Each press and release is a separate
    event. For a keyboard with 1ms or so scan times, even a very fast typist isn't
    going to produce the 500 keystrokes a second needed to actually get more than a
    few ms of delay from this. But if you're doing chording on something with 3-4ms
    scan times? You probably want this.

### RGB Light Configuration

* `#define RGB_DI_PIN D7`
  * pin the DI on the ws2812 is hooked-up to
* `#define RGBLIGHT_ANIMATIONS`
  * run RGB animations
* `#define RGBLED_NUM 15`
  * number of LEDs
* `#define RGBLIGHT_HUE_STEP 12`
  * units to step when in/decreasing hue
* `#define RGBLIGHT_SAT_STEP 25`
  * units to step when in/decresing saturation
* `#define RGBLIGHT_VAL_STEP 12`
  * units to step when in/decreasing value (brightness)
* `#define RGBW_BB_TWI`
  * bit-bangs twi to EZ RGBW LEDs (only required for Ergodox EZ)

### Mouse Key Options

* `#define MOUSEKEY_INTERVAL 20`
* `#define MOUSEKEY_DELAY 0`
* `#define MOUSEKEY_TIME_TO_MAX 60`
* `#define MOUSEKEY_MAX_SPEED 7`
* `#define MOUSEKEY_WHEEL_DELAY 0`

# The `rules.mk` File

This is a [make](https://www.gnu.org/software/make/manual/make.html) file that is included by the top-level `Makefile`. It is used to set some information about the MCU that we will be compiling for as well as enabling and disabling certain features.

## `rules.mk` options

### Build Options

* `DEFAULT_FOLDER`
  * Used to specify a default folder when a keyboard has more than one sub-folder.
* `SRC`
  * Used to add files to the compilation/linking list.
* `LAYOUTS`
  * A list of [layouts](feature_layouts.md) this keyboard supports.

### AVR MCU Options
* `MCU = atmega32u4`
* `F_CPU = 16000000`
* `ARCH = AVR8`
* `F_USB = $(F_CPU)`
* `OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT`
* `BOOTLOADER = atmel-dfu` with the following options:
  * `atmel-dfu`
  * `lufa-dfu`
  * `qmk-dfu`
  * `halfkay`
  * `caterina`
  * `bootloadHID`

### Feature Options

Use these to enable or disable building certain features. The more you have enabled the bigger your firmware will be, and you run the risk of building a firmware too large for your MCU.

* `BOOTMAGIC_ENABLE`
  * Virtual DIP switch configuration(+1000)
* `MOUSEKEY_ENABLE`
  * Mouse keys(+4700)
* `EXTRAKEY_ENABLE`
  * Audio control and System control(+450)
* `CONSOLE_ENABLE`
  * Console for debug(+400)
* `COMMAND_ENABLE`
  * Commands for debug and configuration
* `NKRO_ENABLE`
  * USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
* `AUDIO_ENABLE`
  * Enable the audio subsystem.
* `RGBLIGHT_ENABLE`
  * Enable keyboard underlight functionality
* `MIDI_ENABLE`
  * MIDI controls
* `UNICODE_ENABLE`
  * Unicode
* `BLUETOOTH_ENABLE`
  * Enable Bluetooth with the Adafruit EZ-Key HID
