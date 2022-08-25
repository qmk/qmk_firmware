# Wearhaus66

![Wearhaus66](https://i.imgur.com/U0HNqSfl.jpeg)

A Wearhaus66 keyboard PCB, base on Zed65.

* Keyboard Maintainer: [Mechlovin' Studio](https://github.com/mechlovin)
* Hardware Supported: Zed65, APM32F103
* Hardware Availability: [Mechlovin' Store](https://mechlovin.studio/)

Make example for this keyboard (after setting up your build environment):

    make mechlovin/zed65/wearhaus66:default

Flashing example for this keyboard:

    make mechlovin/zed65/wearhaus66:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
