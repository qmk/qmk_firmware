# Constellation EC

![Constellation EC](https://i.imgur.com/ndgUV63.jpeg)

EC version of the  Constellation keyboard.

* Keyboard Maintainer: [cipulot](https://github.com/cipulot)
* Hardware Supported: Constellation EC PCB
* Hardware Availability: [Keyboard Treehouse](https://keyboardtreehouse.com/collections/constellation)

Make example for this keyboard (after setting up your build environment):

    make cipulot/ec_constellation:default

Flashing example for this keyboard:

    make cipulot/ec_constellation:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset**: Long short the exposed pins on the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
