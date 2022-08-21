# Cradio keyboards

![Cradio](https://raw.githubusercontent.com/filterpaper/filterpaper.github.io/main/images/cradio.png)

Cradio are minimalist 34-key split-keyboards designed with no diodes, using direct micro-controller pin wiring.

## Keyboard Info

* Keyboard Maintainer: [David Barr](https://github.com/davidphilipbarr)
* Hardware Supported:
    * [Cradio](https://github.com/davidphilipbarr/36keys/tree/master/34Keys)
    * [Sweep](https://github.com/davidphilipbarr/Sweep)
    * [Hypergolic](https://github.com/davidphilipbarr/hypergolic)
    * Variants of the same 34-key direct pin PCB
* Hardware Availability: order PCBs using gerber files from the repository

Make example for this keyboard (after setting up your build environment):

    make cradio:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is configured.
* **Physical reset button**: Briefly press the reset button soldered on the PCB.
* **Bootmagic reset**: Hold down the top left key on the left half (or the top right key on the right half) and plug in the controller on that side.

