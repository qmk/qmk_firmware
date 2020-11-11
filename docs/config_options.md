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

# The `config.h` File

This is a C header file that is one of the first things included, and will persist over the whole project (if included). Lots of variables can be set here and accessed elsewhere. The `config.h` file shouldn't be including other `config.h` files, or anything besides this:

    #include "config_common.h"


## Hardware Options
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
* `#define MATRIX_ROWS 5`
  * the number of rows in your keyboard's matrix
* `#define MATRIX_COLS 15`
  * the number of columns in your keyboard's matrix
* `#define MATRIX_ROW_PINS { D0, D5, B5, B6 }`
  * pins of the rows, from top to bottom
* `#define MATRIX_COL_PINS { F1, F0, B0, C7, F4, F5, F6, F7, D4, D6, B4, D7 }`
  * pins of the columns, from left to right
* `#define MATRIX_IO_DELAY 30`
  * the delay in microseconds when between changing matrix pin state and reading values
* `#define UNUSED_PINS { D1, D2, D3, B1, B2, B3 }`
  * pins unused by the keyboard for reference
* `#define MATRIX_HAS_GHOST`
  * define is matrix has ghost (unlikely)
* `#define DIODE_DIRECTION COL2ROW`
  * COL2ROW or ROW2COL - how your matrix is configured. COL2ROW means the black mark on your diode is facing to the rows, and between the switch and the rows.
* `#define DIRECT_PINS { { F1, F0, B0, C7 }, { F4, F5, F6, F7 } }`
  * pins mapped to rows and columns, from left to right. Defines a matrix where each switch is connected to a separate pin and ground.
* `#define AUDIO_VOICES`
  * turns on the alternate audio voices (to cycle through)
* `#define C4_AUDIO`
  * enables audio on pin C4
* `#define C5_AUDIO`
  * enables audio on pin C5
* `#define C6_AUDIO`
  * enables audio on pin C6
* `#define B5_AUDIO`
  * enables audio on pin B5 (duophony is enables if one of B[5-7]\_AUDIO is enabled along with one of C[4-6]\_AUDIO)
* `#define B6_AUDIO`
  * enables audio on pin B6 (duophony is enables if one of B[5-7]\_AUDIO is enabled along with one of C[4-6]\_AUDIO)
* `#define B7_AUDIO`
  * enables audio on pin B7 (duophony is enables if one of B[5-7]\_AUDIO is enabled along with one of C[4-6]\_AUDIO)
* `#define BACKLIGHT_PIN B7`
  * pin of the backlight
* `#define BACKLIGHT_LEVELS 3`
  * number of levels your backlight will have (maximum 31 excluding off)
* `#define BACKLIGHT_BREATHING`
  * enables backlight breathing
* `#define BREATHING_PERIOD 6`
  * the length of one backlight "breath" in seconds
* `#define DEBOUNCE 5`
  * the delay when reading the value of the pin (5 is default)
* `#define LOCKING_SUPPORT_ENABLE`
  * mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap
* `#define LOCKING_RESYNC_ENABLE`
  * tries to keep switch state consistent with keyboard LED state
* `#define IS_COMMAND() (get_mods() == MOD_MASK_SHIFT)`
  * key combination that allows the use of magic commands (useful for debugging)
* `#define USB_MAX_POWER_CONSUMPTION 500`
  * sets the maximum power (in mA) over USB for the device (default: 500)
* `#define USB_POLLING_INTERVAL_MS 10`
  * sets the USB polling rate in milliseconds for the keyboard, mouse, and shared (NKRO/media keys) interfaces
* `#define F_SCL 100000L`
  * sets the I2C clock rate speed for keyboards using I2C. The default is `400000L`, except for keyboards using `split_common`, where the default is `100000L`.

## Features That Can Be Disabled

If you define these options you will disable the associated feature, which can save on code size.

* `#define NO_DEBUG`
  * disable debugging
* `#define NO_PRINT`
  * disable printing/debugging using hid_listen
* `#define NO_ACTION_LAYER`
  * disable layers
* `#define NO_ACTION_TAPPING`
  * disable tap dance and other tapping features
* `#define NO_ACTION_ONESHOT`
  * disable one-shot modifiers
* `#define NO_ACTION_MACRO`
  * disable old-style macro handling using `MACRO()`, `action_get_macro()` _(deprecated)_
* `#define NO_ACTION_FUNCTION`
  * disable old-style function handling using `fn_actions`, `action_function()` _(deprecated)_

## Features That Can Be Enabled

If you define these options you will enable the associated feature, which may increase your code size.

* `#define FORCE_NKRO`
  * NKRO by default requires to be turned on, this forces it on during keyboard startup regardless of EEPROM setting. NKRO can still be turned off but will be turned on again if the keyboard reboots.
* `#define STRICT_LAYER_RELEASE`
  * force a key release to be evaluated using the current layer stack instead of remembering which layer it came from (used for advanced cases)

## Behaviors That Can Be Configured

* `#define TAPPING_TERM 200`
  * how long before a tap becomes a hold, if set above 500, a key tapped during the tapping term will turn it into a hold too
* `#define TAPPING_TERM_PER_KEY`
  * enables handling for per key `TAPPING_TERM` settings
* `#define RETRO_TAPPING`
  * tap anyway, even after TAPPING_TERM, if there was no other key interruption between press and release
  * See [Retro Tapping](tap_hold.md#retro-tapping) for details
* `#define TAPPING_TOGGLE 2`
  * how many taps before triggering the toggle
* `#define PERMISSIVE_HOLD`
  * makes tap and hold keys trigger the hold if another key is pressed before releasing, even if it hasn't hit the `TAPPING_TERM`
  * See [Permissive Hold](tap_hold.md#permissive-hold) for details
* `#define PERMISSIVE_HOLD_PER_KEY`
  * enabled handling for per key `PERMISSIVE_HOLD` settings
* `#define IGNORE_MOD_TAP_INTERRUPT`
  * makes it possible to do rolling combos (zx) with keys that convert to other keys on hold, by enforcing the `TAPPING_TERM` for both keys.
  * See [Ignore Mod Tap Interrupt](tap_hold.md#ignore-mod-tap-interrupt) for details
* `#define IGNORE_MOD_TAP_INTERRUPT_PER_KEY`
  * enables handling for per key `IGNORE_MOD_TAP_INTERRUPT` settings
* `#define TAPPING_FORCE_HOLD`
  * makes it possible to use a dual role key as modifier shortly after having been tapped
  * See [Tapping Force Hold](tap_hold.md#tapping-force-hold)
  * Breaks any Tap Toggle functionality (`TT` or the One Shot Tap Toggle)
* `#define TAPPING_FORCE_HOLD_PER_KEY`
  * enables handling for per key `TAPPING_FORCE_HOLD` settings
* `#define LEADER_TIMEOUT 300`
  * how long before the leader key times out
    * If you're having issues finishing the sequence before it times out, you may need to increase the timeout setting. Or you may want to enable the `LEADER_PER_KEY_TIMING` option, which resets the timeout after each key is tapped.
* `#define LEADER_PER_KEY_TIMING`
  * sets the timer for leader key chords to run on each key press rather than overall
* `#define LEADER_KEY_STRICT_KEY_PROCESSING`
  * Disables keycode filtering for Mod-Tap and Layer-Tap keycodes. Eg, if you enable this, you would need to specify `MT(MOD_CTL, KC_A)` if you want to use `KC_A`.
* `#define ONESHOT_TIMEOUT 300`
  * how long before oneshot times out
* `#define ONESHOT_TAP_TOGGLE 2`
  * how many taps before oneshot toggle is triggered
* `#define QMK_KEYS_PER_SCAN 4`
  * Allows sending more than one key per scan. By default, only one key event gets
    sent via `process_record()` per scan. This has little impact on most typing, but
    if you're doing a lot of chords, or your scan rate is slow to begin with, you can
    have some delay in processing key events. Each press and release is a separate
    event. For a keyboard with 1ms or so scan times, even a very fast typist isn't
    going to produce the 500 keystrokes a second needed to actually get more than a
    few ms of delay from this. But if you're doing chording on something with 3-4ms
    scan times? You probably want this.
* `#define COMBO_COUNT 2`
  * Set this to the number of combos that you're using in the [Combo](feature_combo.md) feature.
* `#define COMBO_TERM 200`
  * how long for the Combo keys to be detected. Defaults to `TAPPING_TERM` if not defined.
* `#define TAP_CODE_DELAY 100`
  * Sets the delay between `register_code` and `unregister_code`, if you're having issues with it registering properly (common on VUSB boards). The value is in milliseconds.
* `#define TAP_HOLD_CAPS_DELAY 80`
  * Sets the delay for Tap Hold keys (`LT`, `MT`) when using `KC_CAPSLOCK` keycode, as this has some special handling on MacOS.  The value is in milliseconds, and defaults to 80 ms if not defined. For macOS, you may want to set this to 200 or higher.

## RGB Light Configuration

* `#define RGB_DI_PIN D7`
  * pin the DI on the WS2812 is hooked-up to
* `#define RGBLIGHT_ANIMATIONS`
  * run RGB animations
* `#define RGBLIGHT_LAYERS`
  * Lets you define [lighting layers](feature_rgblight.md?id=lighting-layers) that can be toggled on or off. Great for showing the current keyboard layer or caps lock state.
* `#define RGBLIGHT_MAX_LAYERS`
  * Defaults to 8. Can be expanded up to 32 if more [lighting layers](feature_rgblight.md?id=lighting-layers) are needed.
  * Note: Increasing the maximum will increase the firmware size and slow sync on split keyboards.
* `#define RGBLIGHT_LAYER_BLINK` 
  * Adds ability to [blink](feature_rgblight.md?id=lighting-layer-blink) a lighting layer for a specified number of milliseconds (e.g. to acknowledge an action).
* `#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF`
  * If defined, then [lighting layers](feature_rgblight?id=overriding-rgb-lighting-onoff-status) will be shown even if RGB Light is off.
* `#define RGBLED_NUM 12`
  * number of LEDs
* `#define RGBLIGHT_SPLIT`
  * Needed if both halves of the board have RGB LEDs wired directly to the RGB output pin on the controllers instead of passing the output of the left half to the input of the right half
* `#define RGBLED_SPLIT { 6, 6 }`
  * number of LEDs connected that are directly wired to `RGB_DI_PIN` on each half of a split keyboard
  * First value indicates number of LEDs for left half, second value is for the right half
  * When RGBLED_SPLIT is defined, RGBLIGHT_SPLIT is implicitly defined.
* `#define RGBLIGHT_HUE_STEP 12`
  * units to step when in/decreasing hue
* `#define RGBLIGHT_SAT_STEP 25`
  * units to step when in/decreasing saturation
* `#define RGBLIGHT_VAL_STEP 12`
  * units to step when in/decreasing value (brightness)
* `#define RGBW`
  * Enables RGBW LED support

## Mouse Key Options

* `#define MOUSEKEY_INTERVAL 20`
* `#define MOUSEKEY_DELAY 0`
* `#define MOUSEKEY_TIME_TO_MAX 60`
* `#define MOUSEKEY_MAX_SPEED 7`
* `#define MOUSEKEY_WHEEL_DELAY 0`

## Split Keyboard Options

Split Keyboard specific options, make sure you have 'SPLIT_KEYBOARD = yes' in your rules.mk

* `SPLIT_TRANSPORT = custom`
  * Allows replacing the standard split communication routines with a custom one. ARM based split keyboards must use this at present.

### Setting Handedness

One thing to remember, the side that the USB port is plugged into is always the master half. The side not plugged into USB is the slave.

There are a few different ways to set handedness for split keyboards (listed in order of precedence):

1. Set `SPLIT_HAND_PIN`: Reads a pin to determine handedness. If pin is high, it's the left side, if low, the half is determined to be the right side
2. Set `EE_HANDS` and flash `eeprom-lefthand.eep`/`eeprom-righthand.eep` to each half
   * For boards with DFU bootloader you can use `:dfu-split-left`/`:dfu-split-right` to flash these EEPROM files
   * For boards with Caterina bootloader (like stock Pro Micros), use `:avrdude-split-left`/`:avrdude-split-right`
   * For boards with ARM DFU bootloader (like Proton C), use `:dfu-util-split-left`/`:dfu-util-split-right`
3. Set `MASTER_RIGHT`: Half that is plugged into the USB port is determined to be the master and right half (inverse of the default)
4. Default: The side that is plugged into the USB port is the master half and is assumed to be the left half. The slave side is the right half

#### Defines for handedness

* `#define SPLIT_HAND_PIN B7`
  * For using high/low pin to determine handedness, low = right hand, high = left hand. Replace `B7` with the pin you are using. This is optional, and if you leave `SPLIT_HAND_PIN` undefined, then you can still use the EE_HANDS method or MASTER_LEFT / MASTER_RIGHT defines like the stock Let's Split uses.

* `#define SPLIT_HAND_MATRIX_GRID <out_pin>,<in_pin>`
  * The handedness is determined by using the intersection of the keyswitches in the key matrix, which does not exist. Normally, when this intersection is shorted (level low), it is considered left. If you define `#define SPLIT_HAND_MATRIX_GRID_LOW_IS_RIGHT`, it is determined to be right when the level is low.

* `#define EE_HANDS` (only works if `SPLIT_HAND_PIN` and `SPLIT_HAND_MATRIX_GRID` are not defined)
  * Reads the handedness value stored in the EEPROM after `eeprom-lefthand.eep`/`eeprom-righthand.eep` has been flashed to their respective halves.

* `#define MASTER_RIGHT`
  * Master half is defined to be the right half.

### Other Options

* `#define USE_I2C`
  * For using I2C instead of Serial (defaults to serial)

* `#define SOFT_SERIAL_PIN D0`
  * When using serial, define this. `D0` or `D1`,`D2`,`D3`,`E6`.

* `#define MATRIX_ROW_PINS_RIGHT { <row pins> }`
* `#define MATRIX_COL_PINS_RIGHT { <col pins> }`
  * If you want to specify a different pinout for the right half than the left half, you can define `MATRIX_ROW_PINS_RIGHT`/`MATRIX_COL_PINS_RIGHT`. Currently, the size of `MATRIX_ROW_PINS` must be the same as `MATRIX_ROW_PINS_RIGHT` and likewise for the definition of columns.

* `#define DIRECT_PINS_RIGHT { { F1, F0, B0, C7 }, { F4, F5, F6, F7 } }`
  * If you want to specify a different direct pinout for the right half than the left half, you can define `DIRECT_PINS_RIGHT`. Currently, the size of `DIRECT_PINS` must be the same as `DIRECT_PINS_RIGHT`.

* `#define RGBLED_SPLIT { 6, 6 }`
  * See [RGB Light Configuration](#rgb-light-configuration)

* `#define SELECT_SOFT_SERIAL_SPEED <speed>` (default speed is 1)
  * Sets the protocol speed when using serial communication
  * Speeds:
    * 0: about 189kbps (Experimental only)
    * 1: about 137kbps (default)
    * 2: about 75kbps
    * 3: about 39kbps
    * 4: about 26kbps
    * 5: about 20kbps

* `#define SPLIT_USB_DETECT`
  * Detect (with timeout) USB connection when delegating master/slave
  * Default behavior for ARM
  * Required for AVR Teensy

* `#define SPLIT_USB_TIMEOUT 2000`
  * Maximum timeout when detecting master/slave when using `SPLIT_USB_DETECT`

* `#define SPLIT_USB_TIMEOUT_POLL 10`
  * Poll frequency when detecting master/slave when using `SPLIT_USB_DETECT`

# The `rules.mk` File

This is a [make](https://www.gnu.org/software/make/manual/make.html) file that is included by the top-level `Makefile`. It is used to set some information about the MCU that we will be compiling for as well as enabling and disabling certain features.

## Build Options

* `DEFAULT_FOLDER`
  * Used to specify a default folder when a keyboard has more than one sub-folder.
* `FIRMWARE_FORMAT`
  * Defines which format (bin, hex) is copied to the root `qmk_firmware` folder after building.
* `SRC`
  * Used to add files to the compilation/linking list.
* `LIB_SRC`
  * Used to add files as a library to the compilation/linking list.  
    The files specified by `LIB_SRC` is linked after the files specified by `SRC`.  
    For example, if you specify:
    ```
    SRC += a.c
    LIB_SRC += lib_b.c
    SRC += c.c
    LIB_SRC += lib_d.c
    ```
    The link order is as follows.
    ```
     ...  a.o c.o  ...  lib_b.a lib_d.a  ...
    ```
* `LAYOUTS`
  * A list of [layouts](feature_layouts.md) this keyboard supports.
* `LINK_TIME_OPTIMIZATION_ENABLE`
  * Enables Link Time Optimization (LTO) when compiling the keyboard.  This makes the process take longer, but it can significantly reduce the compiled size (and since the firmware is small, the added time is not noticeable).
However, this will automatically disable the legacy TMK Macros and Functions features, as these break when LTO is enabled.  It does this by automatically defining `NO_ACTION_MACRO` and `NO_ACTION_FUNCTION`.  (Note: This does not affect QMK [Macros](feature_macros.md) and [Layers](feature_layers.md).)
* `LTO_ENABLE`
  * Has the same meaning as `LINK_TIME_OPTIMIZATION_ENABLE`.  You can use `LTO_ENABLE` instead of `LINK_TIME_OPTIMIZATION_ENABLE`.

## AVR MCU Options
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
  * `USBasp`

## Feature Options :id=feature-options

Use these to enable or disable building certain features. The more you have enabled the bigger your firmware will be, and you run the risk of building a firmware too large for your MCU.

* `BOOTMAGIC_ENABLE`
  * Virtual DIP switch configuration
* `MOUSEKEY_ENABLE`
  * Mouse keys
* `EXTRAKEY_ENABLE`
  * Audio control and System control
* `CONSOLE_ENABLE`
  * Console for debug
* `COMMAND_ENABLE`
  * Commands for debug and configuration
* `COMBO_ENABLE`
  * Key combo feature
* `NKRO_ENABLE`
  * USB N-Key Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
* `AUDIO_ENABLE`
  * Enable the audio subsystem.
* `RGBLIGHT_ENABLE`
  * Enable keyboard underlight functionality
* `LEADER_ENABLE`
  * Enable leader key chording
* `MIDI_ENABLE`
  * MIDI controls
* `UNICODE_ENABLE`
  * Unicode
* `BLUETOOTH_ENABLE`
  * Legacy option to Enable Bluetooth with the Adafruit EZ-Key HID. See BLUETOOTH
* `BLUETOOTH`
  * Current options are AdafruitEzKey, AdafruitBLE, RN42
* `SPLIT_KEYBOARD`
  * Enables split keyboard support (dual MCU like the let's split and bakingpy's boards) and includes all necessary files located at quantum/split_common
* `CUSTOM_MATRIX`
  * Allows replacing the standard matrix scanning routine with a custom one.
* `DEBOUNCE_TYPE`
  * Allows replacing the standard key debouncing routine with an alternative or custom one.
* `WAIT_FOR_USB`
  * Forces the keyboard to wait for a USB connection to be established before it starts up
* `NO_USB_STARTUP_CHECK`
  * Disables usb suspend check after keyboard startup. Usually the keyboard waits for the host to wake it up before any tasks are performed. This is useful for split keyboards as one half will not get a wakeup call but must send commands to the master.

## USB Endpoint Limitations

In order to provide services over USB, QMK has to use USB endpoints.
These are a finite resource: each microcontroller has only a certain number.
This limits what features can be enabled together.
If the available endpoints are exceeded, a build error is thrown.

The following features can require separate endpoints:

* `MOUSEKEY_ENABLE`
* `EXTRAKEY_ENABLE`
* `CONSOLE_ENABLE`
* `NKRO_ENABLE`
* `MIDI_ENABLE`
* `RAW_ENABLE`
* `VIRTSER_ENABLE`

In order to improve utilisation of the endpoints, the HID features can be combined to use a single endpoint.
By default, `MOUSEKEY`, `EXTRAKEY`, and `NKRO` are combined into a single endpoint.

The base keyboard functionality can also be combined into the endpoint,
by setting `KEYBOARD_SHARED_EP = yes`.
This frees up one more endpoint,
but it can prevent the keyboard working in some BIOSes,
as they do not implement Boot Keyboard protocol switching.

Combining the mouse also breaks Boot Mouse compatibility.
The mouse can be uncombined by setting `MOUSE_SHARED_EP = no` if this functionality is required.
