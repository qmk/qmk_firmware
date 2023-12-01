# dymium65

A customizable 65% encoder keyboard.

![dymium65](https://i.imgur.com/5qAl7hgh.png)

* Keyboard Maintainer: [LiWenLiu](https://github.com/LiuLiuQMK)
* Hardware Supported: dymium65 PCB with atmega32u4 microcontroller
* Hardware Availability: Coming soon

Make example for this keyboard (after setting up your build environment):

    make dotmod/dymium65:default

Flashing example for this keyboard:

    make dotmod/dymium65:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: There is no key mapped to `QK_BOOT` in the pre-created keymaps, but you may assign this key in any keymaps you create.
