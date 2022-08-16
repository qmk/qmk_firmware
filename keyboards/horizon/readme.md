# Horizon

![Horizon](https://i.imgur.com/zR0wnA6.jpg)

A simple 52-key (4x14) ortholinear keyboard, powered by an Arduino Pro Micro.

* Keyboard Maintainer: [Steven Karrmann](https://github.com/skarrmann)
* Hardware Supported: Horizon PCBs, Arduino Pro Micro
* Hardware Availability: [Horizon GitHub repository](https://github.com/skarrmann/horizon)

Make example for this keyboard (after setting up your build environment):

    make horizon:default

Flashing example for this keyboard:

    make horizon:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard.
* **Physical reset button**: Briefly press the button on the top center of the PCB.
* **Keycode in layout**: Press the key mapped to `RESET` if it is available.
