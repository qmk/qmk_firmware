# Keyboards with AVR Processors

This page describes the support for for AVR processors in QMK. AVR processors include the atmega32u4, atmega32u2, at90usb1286, and other processors from Atmel Corporation. AVR processors are 8-bit MCUs that are designed to be easy to work with. The most common AVR processors in keyboards have on-board USB and plenty of GPIO for supporting large keyboard matrices. They are the most popular MCU for use in keyboards today.

If you have not yet you should read the [Keyboard Guidelines](hardware_keyboard_guidelines.md) to get a sense of how keyboards fit into QMK.

## Adding Your AVR Keyboard to QMK

QMK has a number of features to simplify working with AVR keyboards. For most keyboards you don't have to write a single line of code. To get started, run `qmk new-keyboard`:

```
$ qmk new-keyboard
Ψ Generating a new QMK keyboard directory

Keyboard Name: mycoolkeeb
Keyboard Type:
        1. avr
        2. ps2avrgb
Please enter your choice:  [1]
Your Name: [John Smith]
Ψ Copying base template files...
Ψ Copying avr template files...
Ψ Renaming keyboard.[ch] to mycoolkeeb.[ch]...
Ψ Replacing %YEAR% with 2021...
Ψ Replacing %KEYBOARD% with mycoolkeeb...
Ψ Replacing %YOUR_NAME% with John Smith...

Ψ Created a new keyboard called mycoolkeeb.
Ψ To start working on things, `cd` into keyboards/mycoolkeeb,
Ψ or open the directory in your preferred text editor.
```

This will create all the files needed to support your new keyboard, and populate the settings with default values. Now you just need to customize it for your keyboard.

## `readme.md`

This is where you'll describe your keyboard. Please follow the [Keyboard Readme Template](documentation_templates.md#keyboard-readmemd-template) when writing your `readme.md`. You're encouraged to place an image at the top of your `readme.md`, please use an external service such as [Imgur](https://imgur.com) to host the images.

## `<keyboard>.c`

This is where all the custom logic for your keyboard goes. Many keyboards do not need to put anything at all in here. You can learn more about writing custom logic in [Custom Quantum Functions](custom_quantum_functions.md).

## `<keyboard>.h`

This is the file you define your [Layout Macro(s)](feature_layouts.md) in. At minimum you should have a `#define LAYOUT` for your keyboard that looks something like this:

```c
#define LAYOUT(          \
      k00, k01, k02,     \
      k10,   k11         \
) {                      \
    { k00, k01,   k02 }, \
    { k10, KC_NO, k11 }, \
}
```

The first half of the `LAYOUT` pre-processor macro defines the physical arrangement of keys. The second half of the macro defines the matrix the switches are connected to. This allows you to have a physical arrangement of keys that differs from the wiring matrix.

Each of the `k__` variables needs to be unique, and typically they follow the format `k<row><col>`.

The physical matrix (the second half) must have a number of rows equaling `MATRIX_ROWS`, and each row must have exactly `MATRIX_COLS` elements in it. If you do not have this many physical keys you can use `KC_NO` to fill in the blank spots.

## `config.h`

The `config.h` file is where you configure the hardware and feature set for your keyboard. There are a lot of options that can be placed in that file, too many to list there. For a complete overview of available options see the [Config Options](config_options.md) page.

### Hardware Configuration


At the top of the `config.h` you'll find USB related settings. These control how your keyboard appears to the Operating System. If you don't have a good reason to change you should leave the `VENDOR_ID` as `0xFEED`. For the `PRODUCT_ID` you should pick a number that is not yet in use.

Do change the `MANUFACTURER` and `PRODUCT` lines to accurately reflect your keyboard.

```c
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    You
#define PRODUCT         my_awesome_keyboard
```

?> Windows and macOS will display the `MANUFACTURER` and `PRODUCT` in the list of USB devices. `lsusb` on Linux instead prefers the values in the list maintained by the [USB ID Repository](http://www.linux-usb.org/usb-ids.html). By default, it will only use `MANUFACTURER` and `PRODUCT` if the list does not contain that `VENDOR_ID` / `PRODUCT_ID`. `sudo lsusb -v` will show the values reported by the device, and they are also present in kernel logs after plugging it in.

### Keyboard Matrix Configuration

The next section of the `config.h` file deals with your keyboard's matrix. The first thing you should set is the matrix's size. This is usually, but not always, the same number of rows and columns as the physical key arrangement.

```c
#define MATRIX_ROWS 2
#define MATRIX_COLS 3
```

Once you've defined the size of your matrix you need to define which pins on your MCU are connected to rows and columns. To do so simply specify the names of those pins:

```c
#define MATRIX_ROW_PINS { D0, D5 }
#define MATRIX_COL_PINS { F1, F0, B0 }
#define UNUSED_PINS
```

The number of `MATRIX_ROW_PINS` entries must be the same as the number you assigned to `MATRIX_ROWS`, and likewise for `MATRIX_COL_PINS` and `MATRIX_COLS`. You do not have to specify `UNUSED_PINS`, but you can if you want to document what pins are open.

Finally, you can specify the direction your diodes point. This can be `COL2ROW` or `ROW2COL`.

```c
#define DIODE_DIRECTION COL2ROW
```

#### Direct Pin Matrix
To configure a keyboard where each switch is connected to a separate pin and ground instead of sharing row and column pins, use `DIRECT_PINS`. The mapping defines the pins of each switch in rows and columns, from left to right. Must conform to the sizes within `MATRIX_ROWS` and `MATRIX_COLS`, use `NO_PIN` to fill in blank spaces. Overrides the behaviour of `DIODE_DIRECTION`, `MATRIX_ROW_PINS` and `MATRIX_COL_PINS`.

```c
// #define MATRIX_ROW_PINS { D0, D5 }
// #define MATRIX_COL_PINS { F1, F0, B0 }
#define DIRECT_PINS { \
    { F1, E6, B0, B2, B3 }, \
    { F5, F0, B1, B7, D2 }, \
    { F6, F7, C7, D5, D3 }, \
    { B5, C6, B6, NO_PIN, NO_PIN } \
}
#define UNUSED_PINS

/* COL2ROW, ROW2COL */
//#define DIODE_DIRECTION
```

### Backlight Configuration

QMK supports backlighting on most GPIO pins. A select few of these can be driven by the MCU in hardware. For more details see the [Backlight Documentation](feature_backlight.md).

```c
#define BACKLIGHT_PIN B7
#define BACKLIGHT_LEVELS 3
#define BACKLIGHT_BREATHING
#define BREATHING_PERIOD 6
```

### Other Configuration Options

There are a lot of features that can be configured or tuned in `config.h`. You should see the [Config Options](config_options.md) page for more details.

## `rules.mk`

You use the `rules.mk` file to tell QMK what files to build and what features to enable. If you are building around an atmega32u4 you can largely leave these defaults alone. If you are using another MCU you may have to tweak some parameters.

### MCU Options

These options tell the build system what CPU to build for. Be very careful if you change any of these settings, you can render your keyboard inoperable.

```make
MCU = atmega32u4
F_CPU = 16000000
ARCH = AVR8
F_USB = $(F_CPU)
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT
```

### Bootloaders

The bootloader is a special section of your MCU that allows you to upgrade the code stored on the MCU. Think of it like a Rescue Partition for your keyboard. 

#### Teensy Bootloader Example

```make
BOOTLOADER = halfkay
```

#### Atmel DFU Loader Example

```make
BOOTLOADER = atmel-dfu
```

#### Pro Micro Bootloader Example

```make
BOOTLOADER = caterina
```

### Build Options

There are a number of features that can be turned on or off in `rules.mk`. See the [Config Options](config_options.md#feature-options) page for a detailed list and description.
