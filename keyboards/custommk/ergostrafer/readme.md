# ergostrafer

![ergostrafer](https://i.imgur.com/ncJgD3jh.jpeg)

ErgoStrafer is a gaming mechanical keyboard that reproduces the layout of the discontinued SteelSeries Merc Stealth a.k.a. Zboard.

* Keyboard Maintainer: [customMK](https://github.com/customMK)
* Hardware Supported: ErgoStrafer
* Hardware Availability: [customMK](https://shop.custommk.com/collections/ergostrafer/products/ergostrafer)

Make example for this keyboard (after setting up your build environment):

    make custommk/ergostrafer:default

Flashing example for this keyboard:

    make custommk/ergostrafer:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the "Load" key in the top right corner) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
