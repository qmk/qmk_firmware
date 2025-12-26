# stardustn0

![stardustn0](https://i.imgur.com/9SWMHH4.jpeg)

This project is a custom-built split ergonomic mechanical keyboard, using two Raspberry Pi Pico microcontrollers.

* Keyboard Maintainer: [navidyt](https://github.com/navidyt)
* Hardware Supported: Raspberry Pi Pico, MX switches, Gateron hot-swap sockets, 1N4148 diodes, generic USB-C breakout board

Make example for this keyboard (after setting up your build environment):

    make stardustn0:default

Flashing example for this keyboard:

    make stardustn0:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:
* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the  reset button on the pico while connecting USB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
