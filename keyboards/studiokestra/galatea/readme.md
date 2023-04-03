# Galatea

TKL H87/88c compatible PCB with support for the most common layouts.

* Keyboard Maintainer: [Studio Kestra](https://github.com/studiokestra/)
* Hardware Supported: [studiokestra.ca/galatea](https://studiokestra.ca/galatea/)
* Hardware Availability: In-Stock Sale (Dec 2021)
* Rev1 firmware is used for Galatea PCBs with no RGB underglow.
* Rev2 firmware is used for Galatea PCBs with RGB underglow. 

## Bootload Sequence

There are 3 ways to put the board in bootloader mode:

- Hold the top-left key (typically `Esc`) while plugging in the USB cable, OR
- While the PCB is plugged into the PC, press the physical `RESET` button on the back of the board, OR
- With the default layout, toggle Layer 1 and press the `R` key. 

## Compiling Firmware

Make example for this keyboard (after setting up your build environment):

    make studiokestra/galatea/rev1:default

If no revision is specified, it will build rev1 firmware by default.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
