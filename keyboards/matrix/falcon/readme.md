# Falcon AVR

PCB using atmega32u4 for the Matrix Falcon

* Keyboard Maintainer: [astro](https://github.com/yulei)
* Hardware Supported: Matrix Falcon
* Hardware Availability: Limited GB

Make example for this keyboard (after setting up your build environment):

    make matrix/falcon:default

Flashing example for this keyboard:

    make matrix/falcon:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard.
* **Physical reset button**: Briefly short cut the *RST* pin with the *GND* pin (pin at the topside of the *RST*) on the back of the PCB.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.