# Macro3

![Macro3](https://github.com/davidphilipbarr/Macropads/raw/main/macro3/IMG_20200703_170424.jpg)

Macro3 is a low-profile macro pad with encoder support designed by [@davidphilipbarr](https://github.com/davidphilipbarr) using direct micro-controller pin wiring.

## Keyboard Info

* Keyboard Maintainer: [davidphilipbarr](https://github.com/davidphilipbarr)
* Hardware Supported: [Macro3](https://github.com/davidphilipbarr/Macropads/tree/main/macro3)
* Hardware Availability: order PCBs with gerber file from the repository

Make example for this keyboard (after setting up your build environment):

    make macro3:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top right key and plug in the controller.
* **Physical reset button**: Briefly press the reset button soldered on the PCB.
* **Keycode in layout**: Press the key mapped to `RESET` if it is configured.

