# Thirty

![Thirty](https://i.imgur.com/4g2fcYOh.jpeg)

A 3x10 toy with plenty of RGB effects.

* Keyboard Maintainer: [Leo Deng](https://github.com/myst729)
* Hardware Supported: APM32F103C8T6 (also hardware compatible with APM32F072CxT6).
* Hardware Availability: Private Groupbuy

Make example for this keyboard (after setting up your build environment):

    make deng/thirty:default

Flashing example for this keyboard:

    make deng/thirty:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
