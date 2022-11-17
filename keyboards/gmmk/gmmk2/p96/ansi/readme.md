# GMMK V2 96% (ANSI)

A keyboard made and sold by Glorious LLC. Equipped with the WestBerry G7 ARM Cortex-M4 microcontroller

* Keyboard Maintainer: [GloriousThrall](https://github.com/GloriousThrall)
* Hardware Supported: GMMK V2
* Hardware Availability: [GloriousPCGaming.com](https://www.pcgamingrace.com)

Make example for this keyboard (after setting up your build environment):

    make gmmk/gmmk2/p96/ansi:default

Flashing example for this keyboard:

    make gmmk/gmmk2/p96/ansi:default:flash

To reset the board into bootloader mode, do one of the following:

* Hold the Reset switch mounted on the surface of the PCB while connecting the USB cable (remove the spacebar key and press and hold the pin on the right side)
* Hold the Escape key while connecting the USB cable (also erases persistent settings)
* Fn+Backslash will reset the board to bootloader mode if you have flashed the default QMK keymap

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
