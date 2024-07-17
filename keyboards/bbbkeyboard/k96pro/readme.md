# K96rpo
[![K96rpo](https://s21.ax1x.com/2024/07/17/pkIz1EQ.jpg)](https://imgse.com/i/pkIz1EQ)

A 95% RGB keyboard.

* Keyboard Maintainer: [jonylee@hfd](https://github.com/jonylee1986)
* Hardware Supported: K96rpo
* Hardware Availability: [K96rpo](http://en.dgata.com/wproducts_content-274599.html)

Make example for this keyboard (after setting up your build environment):

    make bbbkeyboard/k96pro:default

Flashing example for this keyboard:

    make bbbkeyboard/k96pro:flash
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the top left key (commonly programmed as *Esc*) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
