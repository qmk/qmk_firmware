# EASY-CONVERT

![EASY-CONVERT](https://i.imgur.com/ODpqjlah.jpg)

* Keyboard Maintainer: [LiGuo Studio](https://github.com/mechlovin)
* Hardware Supported: easyconvert, STM32L433 
* Hardware Availability: Local Indonesia GB.

Make example for this keyboard (after setting up your build environment):

    make easyconvert:default

Flashing example for this keyboard:

    make easyconvert:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

Enter the bootloader in 2 ways:

* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
* Double-tap the `nRST` button on the PCB.