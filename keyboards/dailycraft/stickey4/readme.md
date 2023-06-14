# stickey4

![stickey4](https://raw.githubusercontent.com/yfuku/stickey4/main/images/stickey4.jpeg)

macropad

* Keyboard Maintainer: [yfuku](https://github.com/yfuku)
* Hardware Supported: stickey4 PCB, Pro Micro
* Hardware Availability: https://shop.dailycraft.jp/

Make example for this keyboard (after setting up your build environment):

    make dailycraft/stickey4:default

Flashing example for this keyboard:

    make dailycraft/stickey4:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly press the button on the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
