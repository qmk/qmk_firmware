# Athena 1800

![Athena 1800](https://kbdfans.com/cdn/shop/files/6_39788097-d299-4f00-9dc4-591a1b301aaf.jpg)

A 96%/1800-layout aluminium keyboard from KBDFans, built around an RP2040 with a
GC9107 128x128 SPI display. This is a mainline-QMK port (the board ships on a
Vial-based vendor fork that dedicates the RP2040's second core to playing GIFs on
the display); the status screen shows Caps/Num/layer indicators.

* Keyboard Maintainer: [laszloth](https://github.com/laszloth)
* Hardware Supported: Athena 1800 PCB (RP2040) w/ GC9107
* Hardware Availability: [kbdfans.com](https://kbdfans.com/products/athena-1800)

Make example for this keyboard (after setting up your build environment):

    make kbdfans/athena1800:default

Flashing example for this keyboard:

    make kbdfans/athena1800:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in any of these ways:

* **Bootmagic reset**: Hold down the top-left key (Esc) and plug in the keyboard.
* **Physical reset**: Short the reset pad on the PCB.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` (Fn + F12 in the default keymap).
