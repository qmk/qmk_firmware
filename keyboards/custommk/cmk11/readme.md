# CMK11

![cmk11](https://i.imgur.com/y8MEwXYh.jpeg)

CMK11 supports eleven 1u keys (or eight 1u keys and one 3u key). The PCB is fully compatible with the Cary Works C11 macropad.

* Keyboard Maintainer: [customMK](https://github.com/customMK)
* Hardware Supported: CMK11
* Hardware Availability: [customMK](https://shop.custommk.com/products/cmk11)

Make example for this keyboard (after setting up your build environment):

    make custommk/cmk11:default

Flashing example for this keyboard:

    make custommk/cmk11:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the key in the top left corner) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
