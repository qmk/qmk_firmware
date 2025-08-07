# Elysian

![Elysian](https://i.imgur.com/W8yx11qh.jpeg)

Elysian is a 3x5 macropad including two rotary encoders.

* Keyboard Maintainer: [customMK](https://github.com/customMK)
* Hardware Supported: Elysian
* Hardware Availability: [customMK](https://shop.custommk.com/collections/keyboards/products/elysian)

Make example for this keyboard (after setting up your build environment):

    make custommk/elysian:default

Flashing example for this keyboard:

    make custommk/elysian:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Press and hold down the rotary encoder at (0,0) in the matrix (the rotary encoder in the top left corner) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
