# Alpaca Keyboards whitefox-eclipse

![Alpaca Keyboards whitefox-eclipse](https://i.imgur.com/VlyDBYGh.jpg)

A customizable 68% keyboard.

- Keyboard Maintainer: [temp4gh](https://github.com/temp4gh)
- Hardware Supported: whitefox-eclipse PCB
- Hardware Availability: https://kono.store/collections/all-products-list/products/whitefox-eclipse?variant=43224249991367

Make example for this keyboard (after setting up your build environment):

    make alpaca/wfeclipse:default

Flashing example for this keyboard:

    make alpaca/wfeclipse:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
