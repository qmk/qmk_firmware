# El Cantor HS

![El Cantor HS](https://imagestack.de/i/905c30a38469.png)

The El Cantor HS keyboard is a 44 key diodeless split keyboard with support for hotswap sockets, designed with simplicity in mind. Based on the popular [Cantor](https://github.com/diepala/cantor) keyboard, this keyboard features a stronger, Corne like, column stagger whilst aiming to simplify assembly and improve cost efficiency.

* Keyboard Maintainer: [azhizhinov](https://github.com/azhizhinov)
* Hardware Supported: Blackpill STM32F401
* Hardware Availability: https://github.com/azhizhinov/ELCANTORHS

Make example for this keyboard (after setting up your build environment):

    make elcantorhs:default

Flashing example for this keyboard:

    make elcantorhs:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard. For the right side, hold the top right key and plug the keyboard.
* **Physical reset button**: 
  * Press and hold the BOOT0 button.
  * Press and release the NRST button.
  * Release the BOOT0 button.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
