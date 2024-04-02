# Sol 3

![Sol 3](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/keyboards/rgbkb/sol3/rev1/rgbkb_sol3_rev1_01.jpg)

An extensible split keyboard with hotswap sockets and per-key RGB lighting.

* Keyboard Maintainer: [XScorpion2](https://github.com/XScorpion2), [RGBKB](https://github.com/rgbkb)
* Hardware Supported: RGBKB Sol 3 rev1 (STM32F303)
* Hardware Availability: [RGBKB.net](https://www.rgbkb.net/collections/sol-3)

Make example for this keyboard (after setting up your build environment):

    make rgbkb/sol3/rev1:default

Flashing example for this keyboard:

    make rgbkb/sol3/rev1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

To reset the board into bootloader mode, do one of the following:

* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available (Adjust + R by default)
* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard (also erases persistent settings)
