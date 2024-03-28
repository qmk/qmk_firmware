# sauceball

![sauceball DIY trackball](https://i.imgur.com/h5vI6Rqh.jpg)

A trackball design for recycling old PS/2 compatible mice into trackballs.

* Keyboard Maintainer: [xia0](https://github.com/xia0)
* Hardware Supported: Atmega32u4 e.g. Teensy 2.0, Arduino Pro Micro
* Hardware Availability: [github](https://github.com/xia0/sauceball_files)
    

Make example for this keyboard (after setting up your build environment):

    make handwired/sauceball:default

Flashing example for this keyboard:

    make handwired/sauceball:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the MCU breakout board - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
