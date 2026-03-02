# Gherkin

![Gherkin](https://i.imgur.com/XrqqtTq.jpg)

A 30 key keyboard.

* Keyboard Maintainer: QMK Community  
* Hardware Supported: Gherkin PCB w/ Pro Micro compatible development board
* Hardware Availability: [Gherkin project on 40% Keyboards](http://www.40percent.club/2016/11/gherkin.html)

Make example for this keyboard (after setting up your build environment):

    make 40percentclub/gherkin:default

Flashing example for this keyboard:

    make 40percentclub/gherkin:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix and plug in the keyboard
* **Physical reset**: Short the Ground and Reset pins on the microcontroller
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
