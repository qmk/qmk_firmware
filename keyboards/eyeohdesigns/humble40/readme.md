# humble40

![humble40](https://i.imgur.com/yI0mwn9h.jpg)

A 12.5u WKL 40% offering uniform and standard row stagger configurations.

* Keyboard Maintainer: [Eye Oh Designs](https://github.com/joedinkle)
* Hardware Supported: humble40 (RP2040 MCU)
* Hardware Availability: Group buy took place between 2022-06-17 1900 UTC and 2022-07-09 0400 UTC on [Eye Oh Designs](https://eyeohdesigns.com/)

Make example for this keyboard (after setting up your build environment):

    make eyeohdesigns/humble40:default

Flashing example for this keyboard

    make eyeohdesigns/humble40:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard. This will also clear the emulated EEPROM, so it is a good first step if the keyboard is misbehaving.
* **Physical reset button**: Short the two holes in the PCB marked `TP6` and plug the board in.
* **Keycode in layout**: There is no key mapped to `QK_BOOT` in the pre-provided keymaps, but you may assign this key in any keymaps you create.

## Flashing

After entering the bootloader through one of the three methods above, the keyboard will appear as a USB mass storage device named `RPI-RP2`. If the CLI is unable to find this device, the compiled `.uf2` file can be manually copied to it. The keyboard will reboot on completion with the new firmware loaded.
