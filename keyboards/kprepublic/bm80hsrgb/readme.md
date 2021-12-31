# BM80HSRGB

![BM80HSRGB](https://i.imgur.com/AqjEjOi.jpeg)

A tkl, hotswap, in switch RGB keyboard from KPRepublic.

* Keyboard Maintainer: [peepeetee](https://github.com/peepeetee)
* Hardware Supported: BM80HSRGB
* Hardware Availability: [KP Republic](https://kprepublic.com/collections/new-arrival/products/bm80rgb-bm80-rgb-80-hot-swappable-custom-mechanical-keyboard-pcb-programmed-qmk-via-firmware-full-rgb-switch-underglow-type-c)

Make example for this keyboard (after setting up your build environment):

    make kprepublic/bm80hsrgb:default

Flashing example for this keyboard:

    make kprepublic/bm80hsrgb:default:flash

To reset the board into bootloader mode, do one of the following:

* Short the two-pad footprint between the "delete" key and the "end" key while the board is plugged in
* Press the switch labled RST on the back of the PCB, near the MCU, while the board is plugged in
* Hold the Esc key while connecting the USB cable (also erases persistent settings)

All of the RGB matrix effects are enabled by default. To disable specific ones, see [this section](https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects) for more information.


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).


