# qoolee

![qoolee](https://github.com/takashicompany/qoolee/raw/master/images/qmk.jpg?raw=true)

QooLee is a keyboard with a 30% layout with ISO Enter.
It can also be equipped with a rotary encoder.
It supports hot-swapping of keyswitches with MX sockets and mounting of LEDs.
VIA (Remap) firmware is also available.

* Keyboard Maintainer: [takashicompany](https://github.com/takashicompany)
* Hardware Supported: PCB, Pro Micro
* Hardware Availability: https://github.com/takashicompany/qoolee

Make example for this keyboard (after setting up your build environment):

    make takashicomoany/qoolee:default

Flashing example for this keyboard:

    make takashicompany/qoolee:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
