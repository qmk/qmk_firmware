# mk47

A customizable 40% keyboard.

* Keyboard Maintainer: [jonylee@hfd](https://github.com/jonylee1986)
* Hardware Supported: mk47
* Hardware Availability: [Inland](https://www.microcenter.com/product/661264/inland-47-keys-hot-swappable-rgb-wired-mechanical-keyboard,)

Make example for this keyboard (after setting up your build environment):

    make inland/mk47:default

Flashing example for this keyboard:

    make inland/mk47:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
