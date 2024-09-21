# Cascade

60% universal hotswap/solder PCB with USB-C that supports multiple commonly used layouts.

* Keyboard Maintainer: [Studio Kestra](https://github.com/studiokestra/)
* Hardware Supported: Most GH60-style keyboards, more info at [studiokestra.ca/cascade](https://studiokestra.ca/cascade/)
* Hardware Availability: [RNDKBD.com](https://rndkbd.com/)

## Bootload Sequence

There are 3 ways to put the board in bootloader mode:

- Hold the top-left key (typically `Esc`) while plugging in the USB cable, OR
- While the PCB is plugged into the PC, press the physical `RESET` button on the back of the board, OR
- With the default layout, toggle Layer 1 and press the `ESC` key.

## Compiling Firmware

Make example for this keyboard (after setting up your build environment):

    make studiokestra/cascade:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
