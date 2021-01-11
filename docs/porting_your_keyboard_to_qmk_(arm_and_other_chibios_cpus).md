Setting up your ARM based PCB is a little more involved than an Atmel MCU, but is easy enough. Start by running `util/new_keyboard.sh`:

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

# END OF NEW ARM DOC, OLD ATMEL DOC FOLLOWS

## `/keyboards/<keyboard>/config.h`

The `USB Device descriptor parameter` block contains parameters are used to uniquely identify your keyboard, but they don't really matter to the machine.

Your `MATRIX_ROWS` and `MATRIX_COLS` are the numbers of rows and cols in your keyboard matrix - this may be different than the number of actual rows and columns on your keyboard. There are some tricks you can pull to increase the number of keys in a given matrix, but most keyboards are pretty straight-forward.

The `MATRIX_ROW_PINS` and `MATRIX_COL_PINS` are the pins your MCU uses on each row/column. Your schematic (if you have one) will have this information on it, and the values will vary depending on your setup. This is one of the most important things to double-check in getting your keyboard setup correctly.

For the `DIODE_DIRECTION`, most hand-wiring guides will instruct you to wire the diodes in the `COL2ROW` position, but it's possible that they are in the other - people coming from EasyAVR often use `ROW2COL`. Nothing will function if this is incorrect.

To configure a keyboard where each switch is connected to a separate pin and ground instead of sharing row and column pins, use `DIRECT_PINS`. The mapping defines the pins of each switch in rows and columns, from left to right. Must conform to the sizes within `MATRIX_ROWS` and `MATRIX_COLS`, use `NO_PIN` to fill in blank spaces. Overrides the behaviour of `DIODE_DIRECTION`, `MATRIX_ROW_PINS` and `MATRIX_COL_PINS`.

`BACKLIGHT_PIN` is the pin that your PWM-controlled backlight (if one exists) is hooked-up to.

`BACKLIGHT_BREATHING` is a fancier backlight feature that adds breathing/pulsing/fading effects to the backlight. It uses the same timer as the normal backlight. These breathing effects must be called by code in your keymap.

`BACKLIGHT_LEVELS` is how many levels exist for your backlight - max is 15, and they are computed automatically from this number.

## `/keyboards/<keyboard>/Makefile`

The values at the top likely won't need to be changed, since most boards use the `atmega32u4` chip. The `BOOTLOADER_SIZE` will need to be adjusted based on your MCU type. It's defaulted to the Teensy, since that's the most common controller. Below is quoted from the `Makefile`.

```
# Boot Section Size in *bytes*
#   Teensy halfKay   512
#   Teensy++ halfKay 1024
#   Atmel DFU loader 4096
#   LUFA bootloader  4096
#   USBaspLoader     2048
OPT_DEFS += -DBOOTLOADER_SIZE=512
```

At the bottom of the file, you'll find lots of features to turn on and off - all of these options should be set with `?=` to allow for the keymap overrides. `?=` only assigns if the variable was previously undefined. For the full documentation of these features, see the [Makefile options](#makefile-options).

## `/keyboards/<keyboard>/readme.md`

This is where you'll describe your keyboard - please write as much as you can about it! Talking about default functionality/features is useful here. Feel free to link to external pages/sites if necessary. Images can be included here as well. This file will be rendered into a webpage at qmk.fm/keyboards/<keyboard>/.

## `/keyboards/<keyboard>/<keyboard>.c`

This is where all of the custom logic for your keyboard goes - you may not need to put anything in this file, since a lot of things are configured automatically. All of the `*_kb()` functions are defined here. If you modify them, remember to keep the calls to `*_user()`, or things in the keymaps might not work. You can read more about the functions [here](#custom-quantum-functions-for-keyboards-and-keymaps)

## `/keyboards/<keyboard>/<keyboard>.h`

Here is where you can (optionally) define your `LAYOUT` function to remap your matrix into a more readable format. With ortholinear boards, this isn't always necessary, but it can help to accommodate the dead spots on your matrix, where there are keys that take up more than one space (2u, staggering, 6.25u, etc). The example shows the difference between the physical keys, and the matrix design:

```
#define LAYOUT( \
    k00, k01, k02, \
      k10,  k11   \
) \
{ \
    { k00, k01,   k02 }, \
    { k10, KC_NO, k11 }, \
}
```

Each of the `kxx` variables needs to be unique, and usually follows the format `k<row><col>`. You can place `KC_NO` where your dead keys are in your matrix.
