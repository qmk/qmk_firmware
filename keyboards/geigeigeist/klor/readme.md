# Klor

![keyboard_image](https://i.imgur.com/1cx62B2.jpeg)

* Keyboard Maintainer: [waffle87](https://github.com/waffle87)
* Hardware Supported: Klor PCBs w/ Pro-Micro compatible microcontrollers
* Hardware Availability: [github:geigeigeist/klor](https://github.com/geigeigeist/klor)

**Note**: Audio and Pointing Device features are disabled by default to conserve firmware space on AVR

Make example for this keyboard (after setting up your build environment):

    make geigeigeist/klor:default

Flashing example for this keyboard:

    make geigeigeist/klor:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix
* **Physical reset button**: Briefly press the button on the PCB
