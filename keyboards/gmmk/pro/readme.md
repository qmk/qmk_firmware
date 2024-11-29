# GMMK PRO

A tenkeyless 75% keyboard made and sold by Glorious LLC. Equipped with the STM32 ARM Cortex-M4 microcontroller, with support for rotary encoders and three additional layouts. [More info at Glorious](https://www.gloriousgaming.com/products/glorious-gmmk-pro-75-barebone-black)

*Note*: GMMK submitted `rev2` firmware to QMK for PCBs using a WB32F3G71 microcontroller. It is quite certain that none of these PCBs were ever sold, however if you do happen have a PCB using this microcontroller, firmware for your keyboard can (most likely) be found [here](https://github.com/qmk/qmk_firmware/tree/breakpoint_2024_11_24/keyboards/gmmk/pro/rev2). It has been removed from QMK to prevent user confusion.

* Keyboard Maintainer: [GloriousThrall](https://github.com/GloriousThrall)
* Hardware Supported: GMMK Pro
* Hardware Availability: [GloriousPCGaming.com](https://www.gloriousgaming.com/products/glorious-gmmk-pro-75-barebone-black)

Make example for this keyboard (after setting up your build environment):

    make gmmk/pro/rev1/ansi:default
    make gmmk/pro/rev1/iso:default

Flashing example for this keyboard:

    make gmmk/pro/rev1/ansi:default:flash
    make gmmk/pro/rev1/iso:default:flash

To reset the board into bootloader mode, do one of the following:

* Hold the Reset switch mounted on the bottom side of the PCB while connecting the USB cable
* Hold the Escape key while connecting the USB cable (also erases persistent settings)
* Fn+Backslash will reset the board to bootloader mode if you have flashed the default QMK keymap

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Case Screw Replacements

Many users report stripped case screws when disassembling the board.

The stock case screws are:
* Thread: M2
* Thread length: ~5 mm
* Head diameter: ~3.8 mm
* Head counterbore diameter: ~4.0 mm
* Head counterbore depth: ~1.9 mm

Most M2x5mm screws should fit fine, although it's best to ensure that the screw head will fit inside the counterbore.
For reference, [this hex socket head screw](https://www.mcmaster.com/91292A005/) from McMaster-Carr should fit nearly flush (head will protrude above the counterbore by ~0.1 mm).
