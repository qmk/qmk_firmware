# ID80v3

![ID80v3](https://i.imgur.com/PGvZfQj.jpg)

A 75% hotswap in-switch RGB keyboard with an encoder.

* Keyboard Maintainer: [peepeetee](https://github.com/peepeetee)
* Hardware Supported: ID80v3
* Hardware Availability: Not avaliable yet

Make example for this keyboard (after setting up your build environment):

    make idobao/id80/v3:default

Flashing example for this keyboard:

    make idobao/id80/v3:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
