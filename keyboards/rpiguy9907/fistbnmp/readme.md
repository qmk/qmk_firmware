# FistBNMP

![FistBNMP assembled proto and bare PCB](https://i.redd.it/uv34770qmc371.jpg)

A compact 9u layout with support for standard Cherry MX and Low Profile MX switches.

* Keyboard Maintainer: [rpiguy9907](https://github.com/rpiguy9907), [lesshonor](https://github.com/lesshonor)
* Hardware Supported: FistBNMP PCB (atmega32u4, atmel-dfu)
* Hardware Availability: Files available on request; ask in the 40% Discord

Make example for this keyboard (after setting up your build environment):

    make rpiguy9907/fistbnmp:default

Flashing example for this keyboard:

    make rpiguy9907/fistbnmp:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard. This will also clear EEPROM, so it is a good first step if the keyboard is misbehaving.
* **Physical reset button**: Briefly press the button labeled `SW1` on the back of the PCB.
* **Keycode in layout**: There is no key mapped to `QK_BOOT` in the pre-created keymaps, but you may assign this key in any keymaps you create.
