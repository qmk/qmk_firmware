# lyra

![lyra](https://github.com/park-csu/Lyra/raw/main/assets/built.jpg)

*A short description of the keyboard/project*

* Keyboard Maintainer: [Changsu Park](https://github.com/park-csu)
* Hardware Supported: *Dedicated pcb and case files available at [My repo](https://github.com/park-csu/Lyra)*
* Hardware Availability: *Gerber files and BOM is available in github*

Make example for this keyboard (after setting up your build environment):

    make lyra:default

Flashing example for this keyboard:

    make lyra:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Physical reset button**: Short the RST and GND for few seconds
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
