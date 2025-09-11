# dropout

![dropout](https://i.imgur.com/VTjdJ4e.jpeg)

A numpad with a rotary encoder.
See more in the [github repository](https://github.com/enochchau/dropout-numpad).

* Keyboard Maintainer: [Enoch Chau](https://github.com/enochchau)
* Hardware Supported: PCB w/ Pro Micro compatible development board
* Hardware Availability: [Github](https://github.com/enochchau/dropout-numpad)

Make example for this keyboard (after setting up your build environment):

    make enochchau/dropout:default

Flashing example for this keyboard:

    make enochchau/dropout:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the micro-controller
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
