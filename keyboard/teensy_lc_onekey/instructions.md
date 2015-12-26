# Teensy LC, 3.0, 3.1, 3.2 support

These ARM Teensies are now supported through [chibios](http://chibios.org).

You'll need to install an ARM toolchain, for instance from [gcc ARM embedded](https://launchpad.net/gcc-arm-embedded) website, or using your favourite package manager. After installing, you should be able to run `arm-none-eabi-gcc -v` in the command prompt and get sensible output. This toolchain is used instead of `avr-gcc`, which is only for AVR chips. Naturally you'll also need the usual development tools (e.g. `make`), just as in the AVR setting.

You'll need this fork/branch of TMK. If you're reading this from your own hard drive, then you already have it ;) Anyway, you can get a zip from [here](https://github.com/flabbergast/tmk_keyboard/archive/chibios.zip) {or clone this repo from github and checkout the `chibios` branch}.

Next, you'll need ChibiOS. The current release (3.0.4) does not have sufficient Kinetis support, so you'll need to get a patched version from [my fork](https://github.com/flabbergast/ChibiOS/tree/kinetis): you can download a current tree zipped from [here](https://github.com/flabbergast/ChibiOS/archive/kinetis.zip) {or clone that repo from github and checkout the `kinetis` branch}. Unpack the zip, rename the newly created `ChibiOS-kinetis` to `chibios`, and move it to `tmk/tool/chibios/` (so that the ChibiOS files reside in `tmk/tool/chibios/chibios`).

This should be it. Running `make` in `keyboard/teensy_lc_onekey` should create a working firmware in `build/`, called `ch.hex`.

For more notes about the ChibiOS backend in TMK, see `tmk_core/protocol/chibios/README.md`.

## About this onekey example

It's set up for Teensy LC. To use 3.x, you'll need to edit the `Makefile` (and comment out one line in `mcuconf.h`). A sample makefile for Teensy 3.0 is provided as `Makefile.3.0`, can be used without renaming with `make -f Makefile.3.0`. Similarly for Teensy 3.2, there's `Makefile.3.2`.

## Credits

TMK itself is written by hasu, original sources [here](https://github.com/tmk/tmk_keyboard).

The USB support for Kinetis MCUs is due to RedoX. His ChibiOS fork is also [on github](https://github.com/RedoXyde/ChibiOS); but it doesn't include Teensy LC definitions.

## Features that are not implemented yet

Currently only the more fancy suspend features are not there (power saving during suspend). The rest should work fine (reports either way are welcome).

# Matrix programming notes

The notes below explain what commands can be used to examine and set the status of Teensy pins.

## ChibiOS pin manipulation basics

### Pins

Each pin sits on a "port", each of which comprises at most 32 individual pins.
So for instance "PTC5" from Kinetis manual/datasheet refers to port C (or GPIOA), pin 5. Most functions dealing with pins take 2 parameters which specify the pin -- the first being the port, the second being the pin number.

Within ChibiOS, there are definitions which simplify this a bit for the Teensies. `TEENSY_PINn_IOPORT` represents the port of the MCU's pin connected Teensy's PIN `n`, and `TEENSY_PINn` represents its MCU's pin number.

### Mode

A MCU pin can be in several modes. The basic command to set a pin mode is

        palSetPadMode(TEENSY_PINn_IOPORT, TEENSY_PINn, PAL_MODE_INPUT_PULLUP);

The last parameter is the mode. For keyboards, the usual ones that are used are `PAL_MODE_INPUT_PULLUP` (input with a pullup), `PAL_MODE_INPUT_PULLDOWN` (input with a pulldown), `PAL_MODE_INPUT` (input floating, a.k.a. Hi-Z), `PAL_MODE_OUTPUT_PUSHPULL` (output in the Arduino sense -- can be then set HIGH or LOW).

### Setting

Pins are set HIGH (after they've been put into `OUTPUT_PUSHPULL` mode) by

        palSetPad(TEENSY_PINn_IOPORT, TEENSY_PINn);

or set LOW by

        palClearPad(TEENSY_PINn_IOPORT, TEENSY_PINn);

Toggling can be done with

        palTogglePad(TEENSY_PINn_IOPORT, TEENSY_PINn);

Alternatively, you can use

        palWritePad(TEENSY_PINn_IOPORT, TEENSY_PINn, bit);

where `bit` is either `PAL_LOW` or `PAL_HIGH` (i.e. `0` or `1`).

### Reading

Reading pin status is done with

        palReadPad(TEENSY_PINn_IOPORT, TEENSY_PINn);

The function returns either `PAL_HIGH` (actually `1`) or `PAL_LOW` (actually `0`).

### Further docs

All the commands that are available for pin manipulation through ChibiOS HAL are documented in [ChibiOS PAL driver docs](http://chibios.sourceforge.net/docs3/hal/group___p_a_l.html).
