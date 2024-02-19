# mino_plus

![mino_plus](https://i.imgur.com/vZJ6kaNh.jpg)

A 65% keyboard, inspried by tetrominos.

* Keyboard Maintainer: [ShandonCodes](https://github.com/ShandonCodes)
* Hardware Supported: Mino Plus PCB
* Hardware Availability: https://store.shandon.codes/mino-plus/

Make example for this keyboard (after setting up your build environment):

    make mino_plus/soldered:default
    make mino_plus/hotswap:default

Flashing example for this keyboard:

    make mino_plus/soldered:default:flash
    make mino_plus/hotswap:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `FN` + `R` if it is available.
