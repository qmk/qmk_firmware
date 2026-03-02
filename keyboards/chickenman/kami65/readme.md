# Kami65

![Kami65](https://i.imgur.com/SwXfDcr.png)

A 65% keyboard.

* Keyboard Maintainer: [Mai The San](https://github.com/maithesan)
* Hardware Supported: Kami65 Keyboard
* Hardware Availability: [UCSD GB](https://www.instagram.com/p/C1BD0RZsttm/)

Make example for this keyboard (after setting up your build environment):

    make chickenman/kami65:default

Flashing example for this keyboard:

    make chickenman/kami65:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available