# 5075
[![5075](https://s21.ax1x.com/2024/03/19/pFRcz0H.jpg)](https://imgse.com/i/pFRcz0H)

A customizable 75% encoder keyboard.

* Keyboard Maintainer: [jonylee@hfd](https://github.com/jonylee1986)
* Hardware Supported: Akko 5075
* Hardware Availability: [akko](https://www.akkogear.com/)

Make example for this keyboard (after setting up your build environment):

    make akko/5075:default

Flashing example for this keyboard:

    make akko/5075:default:flash
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the top left key (commonly programmed as *Esc*) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
