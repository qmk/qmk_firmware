# Piggy60

![piggy60](https://i.imgur.com/QXuKDual.jpg)

A gasket-mounted 60% in the style of the S7 Elephant.

* Keyboard Maintainer: [The QMK Community](https://github.com/qmk)
* Hardware Supported:
  * Piggy60 PCB rev 1 (atmega32u4, atmel-dfu)
  * Piggy60 PCB rev 2 (APM32F103CBT6, uf2boot)
  **Check your PCB before flashing!** Loading rev1 firmware on a rev2 PCB may result in a non-functional PCB which can only be recovered using a hardware programmer (e.g. an ST-Link V2)
* Hardware Availability: Group Buy took place between 2021-05-22 1600 UTC and 2021-05-25 1600 UTC on [https://jackylab.com/](https://jackylab.com/). Rev 2 PCBs were provided during extras sales and as replacements.

Make example for this keyboard (after setting up your build environment):

    make jacky_studio/piggy60/rev1:default
    make jacky_studio/piggy60/rev2:default

Flashing example for this keyboard:

    make jacky_studio/piggy60/rev1:default:flash
    make jacky_studio/piggy60/rev2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard. This will also clear EEPROM/emulated EEPROM, so it is a good first step if the keyboard is misbehaving.
* **Physical reset**:
  - Rev 1: Short the set of vertical holes on the third row, to the right of Caps Lock. These can be reached with tweezers after the board has been assembled.
  - Rev 2: Near the MCU there are two square pads with a circle in the middle. This is an unpopulated footprint for a reset button. Short these two pads twice in quick succession.
* **Keycode in layout**: There is no key mapped to `QK_BOOT` in the pre-created keymaps, but you may assign this key in any keymaps you create.

## Flashing

After entering the bootloader through one of the three methods above:

- Rev 1: The keyboard will appear as an Atmel DFU device. It can be flashed using the QMK CLI or QMK Toolbox.
- Rev 2: The keyboard will appear as a USB mass storage device named `MT.KEY`. If the CLI is unable to find this device, the compiled `.uf2` file can be manually copied to it. The keyboard will reboot on completion with the new firmware loaded.
