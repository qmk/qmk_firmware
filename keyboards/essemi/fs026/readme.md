# FS026

Supported Hardware: *ES32-PDS-ES32F0283-V1.1*.(FS026 and ES32F0283 share the same librariy)

This is a 17x6 keyboard with WS2812B key lighting.
It's designed for a modular keyboard mount using an FS026(ES32F0283).

* Keyboard Maintainer: [liuhy](https://github.com/liuhy-2020)
* Hardware Supported: *ES-PDS, FS026(ES32F0283)*
* Hardware Availability: *https://www.essemi.com/*

Make example for this keyboard (after setting up your build environment):

    make essemi/fs026:default

Flashing example:

    make essemi/fs026:default:flash

## Bootloader

Enter the bootloader in 1 ways:

* **Bootmagic reset**: Hold down the key at Esc in the matrix and plug in the keyboard.

## issues
1. MCU driver supports supports few functions.(GPIO,USB,PWM)
2. There are few configuration options in mcuconf.h.

## solve issues
1.Improve MCU driver.(ChibiOS-Contrib)
2.Update mcuconf.h.(qmk_firmware)
