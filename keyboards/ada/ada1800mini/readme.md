# ada1800mini

![ada1800mini](https://i.imgur.com/87Rn2MJh.jpeg)

A per key RGB mini 1800 keyboard

* Keyboard Maintainer: [peepeetee](https://github.com/peepeetee)
* Hardware Supported: ada1800mini
* Hardware Availability: no longer avaliable - future groupbuy possible

Make example for this keyboard (after setting up your build environment):

    make ada/ada1800mini:default

Flashing example for this keyboard:

    make ada/ada1800mini:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
