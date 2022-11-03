# KD87A_BFG_Edition 

An 87 keys keyboard. Equipped with the WestBerry G7 microcontroller

* Keyboard Maintainer: [GSKY](https://github.com/gksygithub)
* Hardware Supported: KD87A_BFG_Edition
* Hardware Availability: [GSKY GitHub](https://github.com/gksygithub/keyboard1)

Make example for this keyboard (after setting up your build environment):

    make darkproject/kd87a_bfg_edition:default

Flashing example for this keyboard:

    make darkproject/kd87a_bfg_edition:default:flash

To reset the board into bootloader mode, do one of the following:

* Hold the Reset switch mounted on the surface of the PCB while connecting the USB cable (remove the spacebar key and press and hold the pin on the right side)
* Hold the Escape key while connecting the USB cable (also erases persistent settings)
* Fn+Backslash will reset the board to bootloader mode if you have flashed the default QMK keymap

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
