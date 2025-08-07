# kaly/kaly42

![kaly/kaly42](https://i.imgur.com/wSmUjFUh.jpeg)

The Kaly is a split, ergonomic keyboard inspired by the [Ferris](https://github.com/pierrechevalier83/ferris) and the [Cantor](https://github.com/diepala/cantor) with the main goals of comfort, affordability and cuteness! The stand-out features of the Kaly is the ease-to-solder and the natural thumb cluster that allow users to confortably reach all keys of the keyboard! To see more of the Kaly, visit [this video](https://www.youtube.com/watch?v=PhxM8o__9Xo) outlining the journey of making this keybord.

* Keyboard Maintainer: [Kael Soares Augusto](https://github.com/Dwctor)
* Hardware Supported: Blackpill STM32F401
* Hardware Availability: [https://github.com/Dwctor/Kaly](https://github.com/Dwctor/Kaly)

Make example for this keyboard (after setting up your build environment):

    make kaly/kaly42:default

Flashing example for this keyboard:

    make kaly/kaly42:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
