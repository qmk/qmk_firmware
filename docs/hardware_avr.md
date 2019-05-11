# Keyboards with AVR Processors

This page describes the support for for AVR processors in QMK. AVR processors include the atmega32u4, atmega32u2, at90usb1286, and other processors from Atmel Corporation. AVR processors are 8-bit MCU's that are designed to be easy to work with. The most common AVR processors in keyboards have on-board USB and plenty of GPIO for supporting large keyboard matrices. They are the most popular MCU for use in keyboards today.

If you have not yet you should read the [Keyboard Guidelines](hardware_keyboard_guidelines.md) to get a sense of how keyboards fit into QMK.

## Adding Your AVR Keyboard to QMK

QMK has a number of features to simplify working with AVR keyboards. For most keyboards you don't have to write a single line of code. To get started, run the `util/new_keyboard.sh` script:

```
$ ./util/new_keyboard.sh
Generating a new QMK keyboard directory

Keyboard Name: mycoolkb
Keyboard Type [avr]: 
Your Name [John Smith]: 

Copying base template files... done
Copying avr template files... done
Renaming keyboard files... done
Replacing %KEYBOARD% with mycoolkb... done
Replacing %YOUR_NAME% with John Smith... done

Created a new keyboard called mycoolkb.

To start working on things, cd into keyboards/mycoolkb,
or open the directory in your favourite text editor.
```

This will create all the files needed to support your new keyboard, and populate the settings with default values. Now you just need to customize it for your keyboard.

## `readme.md`

This is where you'll describe your keyboard. Please follow the [Keyboard Readme Template](documentation_templates.md#keyboard-readmemd-template) when writing your `readme.md`. You're encouraged to place an image at the top of your `readme.md`, please use an external service such as [Imgur](http://imgur.com) to host the images.

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

Do change the `MANUFACTURER`, `PRODUCT`, and `DESCRIPTION` lines to accurately reflect your keyboard.

```c
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    You
#define PRODUCT         my_awesome_keyboard
#define DESCRIPTION     A custom keyboard
```

?> Note: On Windows and macOS the `MANUFACTURER`, `PRODUCT`, and `DESCRIPTION` fields will be displayed in the list of USB devices. ?> On Linux these values will not be visible in lsusb by default, since Linux takes the information from the list maintained by [USB ID Repository](http://www.linux-usb.org/usb-ids.html) by default. lsusb will show the information reported by the device when executed with -v option. It is also present in kernel logs after plugging in the device.

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

By default QMK supports backlighting on pins `B5`, `B6`, and `B7`. If you are using one of those you can simply enable it here. For more details see the [Backlight Documentation](feature_backlight.md).

```c
#define BACKLIGHT_PIN B7
#define BACKLIGHT_LEVELS 3
#define BACKLIGHT_BREATHING
#define BREATHING_PERIOD 6
```

?> You can use backlighting on any pin you like, but you will have to do more work to support that. See the [Backlight Documentation](feature_backlight.md) for more details.

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
