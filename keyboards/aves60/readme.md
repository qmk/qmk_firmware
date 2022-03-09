# aves60

![Aves60](https://i.imgur.com/U5UpFAVl.jpg)

A universally compatible 60% PCB.

* Keyboard Maintainer: [Evelien Dekkers](https://github.com/evyd13)
* Hardware Supported: Aves60 PCB
* Hardware Availability: [I/O Keyboards](https://iokeyboards.eu/)

Make example for this keyboard (after setting up your build environment):

    make aves60:default

Flashing example for this keyboard:

    make aves60:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the space bar and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
