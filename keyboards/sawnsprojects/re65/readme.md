# RE65

![RE65](https://i.imgur.com/bzeWSwwh.png)

A Keyboard from Nuxros

* Keyboard Maintainer: [Mai The San](https://github.com/maithesan)
* Hardware Supported: RE65, KBD67 MKII
* Hardware Availability: [Nuxros Store](https://nuxroskb.store/en/products/re65?variant=45628371370283)
Make example for this keyboard (after setting up your build environment):

    make sawnsprojects/re65:default

Flashing example for this keyboard:

    make sawnsprojects/re65:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly short the `RST` and `GND` pads on the SWD header twice, or short the `BOOT` header and plug in keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
