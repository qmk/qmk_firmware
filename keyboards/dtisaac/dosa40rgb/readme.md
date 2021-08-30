# dosa40rgb

![dosa40rgb](https://i.imgur.com/NfuF82nh.jpg)

A 40 percent keyboard dosa40rgb Bluetooth Low Energy

* Keyboard Maintainer: [DTIsaac](https://github.com/daotakisaac)
* Hardware Supported: ATmega32U4 + AdafruitBLE SPI

Make example for this keyboard (after setting up your build environment):

    make dtisaac/dosa40rgb:default

Flashing example for this keyboard:

    make dtisaac/dosa40rgb:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
