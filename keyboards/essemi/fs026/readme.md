# FS026

Supported Hardware: *FS026 PDS*.

This is a 17x6 keyboard with WS2812B key lighting.
It's designed for a modular keyboard mount using an FSO26.

* Keyboard Maintainer: [liuhy](https://github.com/liuhy-2020)
* Hardware Supported: *ES-PDS, FS026*
* Hardware Availability: *https://www.essemi.com/*

Make example for this keyboard (after setting up your build environment):

    make essemi\fs026:default

Flashing example:

    make essemi\fs026:default:flash(msc device or qmk_toolbox)

## Bootloader

Enter the bootloader in 1 ways:

* **Bootmagic reset**: Hold down the key at Esc in the matrix and plug in the keyboard.
