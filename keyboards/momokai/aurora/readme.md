# Momokai Aurora

A 6 key keypad with a rotary encoder

* Keyboard Maintainer: [peepeetee](https://github.com/peepeetee)
* Hardware Supported: Aurora
* Hardware Availability: [Momokai](https://www.momokai.com/)

Make example for this keyboard (after setting up your build environment):

    make momokai/aurora:default

Flashing example for this keyboard:

    make momokai/aurora:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (1,0) in the matrix (the top left physical key) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
