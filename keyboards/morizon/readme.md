# Morizon

![Morizon](https://i.imgur.com/2EEP412h.jpg)

A simple 66-key (5x14) ortholinear keyboard, powered by an Arduino Pro Micro. The design is based on the [Horizon keyboard](https://github.com/skarrmann/horizon).

* Keyboard Maintainer: [Steven Karrmann](https://github.com/skarrmann)
* Hardware Supported: Morizon PCBs, Arduino Pro Micro
* Hardware Availability: [Morizon GitHub repository](https://github.com/skarrmann/morizon)

Make example for this keyboard (after setting up your build environment):

    make morizon:default

Flashing example for this keyboard:

    make morizon:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard.
* **Physical reset button**: Briefly press the button on the top center of the PCB.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.
