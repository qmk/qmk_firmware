# M7
![M7](https://www.monsgeek.com/wp-content/uploads/2023/12/M7-VIA-Main-1.png)

A customizable 65% (68 key) keyboard.

* Keyboard Maintainer: [jonylee@hfd](https://github.com/jonylee1986)
* Hardware Supported: monsgeek M7
* Hardware Availability: [monsgeek](https://www.monsgeek.com)

Make example for this keyboard (after setting up your build environment):

    make monsgeek/m7:default

Flashing example for this keyboard:

    make monsgeek/m7:default:flash
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the Hold down the top left key (commonly programmed as *Esc*) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
