# stardustn0

![stardustn0](https://imgur.com/a/OtCh0fQ)

This project is a custom-built split ergonomic mechanical keyboard, using two Raspberry Pi Pico microcontrollers.

* Keyboard Maintainer: [navidyt](https://github.com/navidyt)
* Hardware SupportedRaspberry Pi Pico, MX switches, Gateron hot-swap sockets, 1N4148 diodes, generic USB-C breakout board

Make example for this keyboard (after setting up your build environment):

    make stardustn0:default

Flashing example for this keyboard:

    make stardustn0:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Entering the bootloader:

* **Physical reset button**: Briefly press the  reset button on the pico while connecting the usb c to enter the flash mode



This keyboard uses the #MASTER_RIGHT handedness method, so you must connect it to the PC using the right half.
To change this behavior, define your target method in the config.h file.
See [This Page](https://docs.qmk.fm/features/split_keyboard#setting-handedness) for more information on this.
