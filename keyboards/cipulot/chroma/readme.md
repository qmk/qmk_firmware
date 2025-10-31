# Chroma

![Chroma](https://i.imgur.com/clhRkDDh.png)

A 60% hot swap PCB for MX switches.

* Keyboard Maintainer: [cipulot](https://github.com/cipulot)
* Hardware Supported: Chroma
* Hardware Availability: [Eloquent Clicks](https://eloquentclicks.com/)

Make example for this keyboard (after setting up your build environment):

    make cipulot/chroma:default

Flashing example for this keyboard:

    make cipulot/chroma:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is configured.
* **Physical reset button**: Long press the reset button soldered on the PCB.
* **Bootmagic reset**: Hold down the top left key and plug in the controller.
