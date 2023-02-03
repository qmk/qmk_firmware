# Quarkeys Z40 Low Profile Keyboard

A 40% Bottom mount low-profile & MX switch compatible keyboard.

* Keyboard Maintainer: [Quarkeys Studio](www.quarkeys.com)
* Hardware Supported: Z40-ACR, Z40-Pastry
* Hardware Specs: Per-key RGBs, layer & Capslock indicators
* rgblgt folder contains firmware with RGB lighting effect; rgbmtix folder contains firmware with RGB matrix lighting effect

Make example for this keyboard solder version keymap(after setting up your build environment):

    make quarkeys/z40/rgblgt:default

Flashing example for this keyboard:

    make quarkeys/z40/rgblgt:default:flash

**Bootloader:** Press the `QK_BOOT` keycode at ESC position of layer 1.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).