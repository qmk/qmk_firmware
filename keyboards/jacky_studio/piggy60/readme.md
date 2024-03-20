# Piggy60

![piggy60](https://i.imgur.com/QXuKDual.jpg)

A gasket-mounted 60% in the style of the S7 Elephant.

* Keyboard Maintainer: [The QMK Community](https://github.com/qmk)
* Hardware Supported: Piggy60 PCB "rev1" (atmega32u4)
  * **Make sure your PCB uses an `atmega32u4` before flashing!** A PCB that uses an `APM32F103CBT6` with `uf2boot` has been shipped with some extras purchases and to replace some defective units. Flashing that PCB with "rev1" firmware may result in a non-functional PCB which can only be recovered using a hardware programmer (e.g. an ST-Link V2)
* Hardware Availability: Group Buy took place between 2021-05-22 1600 UTC and 2021-05-25 1600 UTC on [https://jackylab.com/](https://jackylab.com/).

Make example for this keyboard (after setting up your build environment):

    make jacky_studio/piggy60:default

Flashing example for this keyboard:

    make jacky_studio/piggy60:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard. This will also clear EEPROM, so it is a good first step if the keyboard is misbehaving.
* **Physical reset**: Short the set of vertical holes on the third row, to the right of Caps Lock. These can be reached with tweezers after the board has been assembled.
* **Keycode in layout**: There is no key mapped to `QK_BOOT` in the pre-created keymaps, but you may assign this key in any keymaps you create.
