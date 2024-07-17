# K67rpo
[![K67rpo](https://s21.ax1x.com/2024/06/26/pky9MTO.jpg)](https://imgse.com/i/pky9MTO)

A 67keys RGB low profile switch keyboard.

* Keyboard Maintainer: [jonylee@hfd](https://github.com/jonylee1986)
* Hardware Supported: K67rpo
* Hardware Availability: [K67rpo](http://en.dgata.com/wproducts_content-273807.html)

Make example for this keyboard (after setting up your build environment):

    make bbbkeyboard/k67pro:default

Flashing example for this keyboard:

    make bbbkeyboard/k67pro:flash
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the top left key (commonly programmed as *Esc*) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
