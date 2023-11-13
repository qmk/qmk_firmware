# Wookong WK87

![Wookong WK87](https://i.imgur.com/Vv3RaTOh.png)

A customizable 80% keyboard with two encoders.

* Keyboard Maintainer: Gyphae Team
* Hardware Supported: Wookong WK87
* Hardware Availability: Wookong

Make example for this keyboard (after setting up your build environment):

    make wookong/wk87:default

Flashing example for this keyboard:

    make wookong/wk87:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix, commonly programmed as *Esc* and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available