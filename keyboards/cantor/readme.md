# cantor

![cantor](https://i.imgur.com/Uvxm3zV.jpg)

The Cantor keyboard is a 42 key diodeless split keyboard, designed with simplicity in mind. It is inspired on the popular [corne](https://github.com/foostan/crkbd), [ferris](https://github.com/pierrechevalier83/ferris) and [sweep](https://github.com/davidphilipbarr/Sweep) keyboards, aiming to provide a more ergonomic (stronger column stagger) corne-like layout with a simple, easy to assemble and cheap design.

* Keyboard Maintainer: [Diego Palacios](https://github.com/diepala)
* Hardware Supported: Blackpill STM32F401
* Hardware Availability: https://github.com/diepala/cantor

Make example for this keyboard (after setting up your build environment):

    make cantor:default

Flashing example for this keyboard:

    make cantor:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard. For the right side, hold the top right key and plug the keyboard.
* **Physical reset button**: 
  * Press and hold the BOOT0 button.
  * Press and release the NRST button.
  * Release the BOOT0 button.
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
