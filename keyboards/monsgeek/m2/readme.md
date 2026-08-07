# MonsGeek M2
![M2](https://i.imgur.com/kv9ChJn.png)

A customizable 95% keyboard

* Keyboard Maintainer: [jonylee@hfd](https://github.com/jonylee1986)
* Hardware Supported: MonsGeek M2 PCB
* Hardware Availability: [monsgeek](https://www.monsgeek.com/product/m2/)

Make example for this keyboard (after setting up your build environment):

    make monsgeek/m2:default

Flashing example for this keyboard:

    make monsgeek/m2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the top left key (commonly programmed as *Esc*) while plugging in the keyboard.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
