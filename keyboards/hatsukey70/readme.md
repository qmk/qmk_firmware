# hatsukey70

![hatsukey70](https://scrapbox.io/files/657eefbbe3d8d30022ed614d.jpg)
※Hatsukey71 is printed on the board, but it is a mistake for Hatsukey70.


Low-profile keyboard with Kailh Choc V1 switches. The key layout is divided in a way that remains close to the keyboard you normally use and allows you to take advantage of the thumb keys.

* Keyboard Maintainer: [interestor](https://github.com/interestor)
* Hardware Supported: hatsukey70 rev1, ProMicro
* Hardware Availability: https://shop.yushakobo.jp/

Make example for this keyboard (after setting up your build environment):

    make hatsukey70:via

Flashing example for this keyboard:

    make hatsukey70:via:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
