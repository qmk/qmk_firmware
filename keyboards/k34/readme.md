# k34

![k34](https://i.imgur.com/tarkFIph.jpeg)

## Keyboard Info

The K34 is a custom 34-key unibody keyboard.

* Keyboard Maintainer: [wongjingping](https://github.com/wongjingping)
All hardware supported can be found in the [k34 repository](https://github.com/wongjingping/k34)

## Flashing Instructions

To enter the bootloader, short the RST and GND pins, or press the key mapped to `QK_BOOT`.

Make example for this keyboard (after setting up your build environment):

    make k34:default

Flashing example for this keyboard:

    make k34:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
