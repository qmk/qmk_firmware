# Kawayo

![Kawayo Board](https://i.imgur.com/MecyLFl.jpeg)

A board dedicated to Nakiri Ayame from Nakirigumi. 65% with top blocker.

* Keyboard Maintainer: [cipulot](https://github.com/cipulot) and the Mecha Team
* Hardware Supported: Kawayo
* Hardware Availability: [Mecha Store](https://mecha.store)

Make example for this keyboard (after setting up your build environment):

    make cipulot/kawayo:default
    make cipulot/kawayo:via

Flashing example for this keyboard:

    make cipulot/kawayo:default:flash
    make cipulot/kawayo:via:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Power up the board while having the `Reset/Boot0` pad shorted.

* **Keycode in layout**: Press the `GRV` key on layer 1 which is mapped to `RESET`
