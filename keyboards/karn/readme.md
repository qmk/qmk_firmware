# Karn 2

Split, ortholinear, non-staggered, diodeless, 38 key keyboard, with a unique set of 1.5u thumb arc keys and 1.5u pinky reach keys. 

* Keyboard Maintainer: [Robert Mills](https://github.com/robcmills)
* Hardware Supported: Blackpill STM32F401

Based on the excellent [cantor](https://github.com/diepala/cantor), and inspired by the popular [corne](https://github.com/foostan/crkbd), [ferris](https://github.com/pierrechevalier83/ferris) and [sweep](https://github.com/davidphilipbarr/Sweep) keyboards.

[https://github.com/robcmills/karn-keyboard](https://github.com/robcmills/karn-keyboard)

![karn-2-left](https://i.imgur.com/vm6XFyIh.jpeg)

![karn-2-full](https://i.imgur.com/R7WnlC3h.jpeg)

![karn-2-pcb](https://i.imgur.com/EQqyyEDh.png)


### Make

Make example for this keyboard (after setting up your build environment):

    make karn:default

Flashing example for this keyboard:

    make karn:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).


### Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard. For the right side, hold the top right key and plug the keyboard.
* **Physical reset button**: 
  * Press and hold the BOOT0 button.
  * Press and release the NRST button.
  * Release the BOOT0 button.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

