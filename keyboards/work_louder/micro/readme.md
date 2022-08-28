# work_louder/micro

![work_louder/micro](https://i.imgur.com/4Hdt41Gh.jpg)

A 16 "key" macro pad, with dual encoders, per key RGB, RGB underglow and more

* Keyboard Maintainer: [Drashna Jael're](https://github.com/Drashna Jael're)
* Hardware Supported:  atmega32u4 based PCB
* Hardware Availability: [Work Louder shop](https://worklouder.cc/creator-micro/)

Make example for this keyboard (after setting up your build environment):

    make work_louder/micro:default

Flashing example for this keyboard:

    make work_louder/micro:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the horizontal encoder (top left) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
