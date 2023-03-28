# 404 x Basic I/O Instruments Harpe65

A compact USB/BLE duo-mode 65% keyboard design by 404 Studio.

![Harpe65](https://i.imgur.com/YmAK1GPh.jpg)

* Keyboard Maintainer: [Basic I/O Instruments (Scott Wei)](https://github.com/scottywei)
* Hardware Supported: [Basic I/O Instruments (Scott Wei)](https://github.com/scottywei)
* Hardware Availability: https://www.zfrontier.com/app/flow/293YaqglXwXO

Make example for this keyboard (after setting up your build environment):

    make bioi/harpe65:default

Flashing example for this keyboard:

    make bioi/harpe65:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
