# infinity81

![infinity81](https://i.imgur.com/9d6IcuA.jpg)

A per key RGB 75% with blocker keyboard

* Keyboard Maintainer: [peepeetee](https://github.com/peepeetee)
* Hardware Supported: infinity81
* Hardware Availability: no longer avaliable - future groupbuy possible

Make example for this keyboard (after setting up your build environment):

    make ada/infinity81:default

Flashing example for this keyboard:

    make ada/infinity81:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
