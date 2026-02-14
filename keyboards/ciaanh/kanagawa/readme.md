# Kanagawa


![Kanagawa](https://i.imgur.com/KKOZbUCh.jpeg)

*A 75% keyboard with oled, rotary encoder and split spacebar for Raspberry Pico*

* Keyboard Maintainer: [Nicolas Fabre](https://github.com/Ciaanh)
* Hardware Supported: *Kanagawa PCB rev 2.1, Raspberry Pico*
* Hardware Availability: *open source files for the PCB and case available [here](https://github.com/Ciaanh/keyboards/tree/main/Kanagawa)*

Make example for this keyboard (after setting up your build environment):

    make ciaanh/kanagawa/ansi:default
    make ciaanh/kanagawa/iso:default


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,13) in the matrix (the rotary encoder push-button) and plug in the keyboard
* **Physical reset button**: Briefly press both the reset and the Bootsel on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available