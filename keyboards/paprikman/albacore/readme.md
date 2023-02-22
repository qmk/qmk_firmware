# Albacore

A small 7-key macropad featuring hotswap and per-key RGB

![Albacore](https://i.imgur.com/BTPHnuQh.jpg)

* Keyboard Maintainer: paprikman
* Hardware Supported: Albacore hotswap pcb
* Hardware Availability: Private group buy

Make example for this keyboard (after setting up your build environment):

    make paprikman/albacore:default

Flashing example for this keyboard:

    make paprikman/albacore:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

There are several ways to enter the bootloader:
* **Using keycode**: Press the `QK_BOOT` key (if mapped)
* **Bootmagic reset**: Hold the left bottom key (default mod key) and plug the usb cable
* **Physical reset**: In the top right corner of the bottom part of the pcb you will find two pads. Shorten them with tweezers and plug the usb cable, then release. It is also possible to shorten these pads while the macropad is already connected (shorten and hold for a couple of seconds, then release).
