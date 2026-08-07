# BAMFK-1

![bamfk1](https://cdn.shopify.com/s/files/1/1851/5125/products/bamfk-1-back_1100x.png?v=1635304218)

PCB for the Big Switch with support for horizontal rotary encoders.

* Keyboard Maintainer: [Keebio](https://github.com/nooges)
* Hardware Supported: BAMFK-1 PCB
* Hardware Availability: [Keebio](https://keeb.io/)

Make example for this keyboard (after setting up your build environment):

    make keebio/bamfk1:default

Flashing example for this keyboard:

    make keebio/bamfk1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
