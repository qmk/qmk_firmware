# rephlex/2k
![Rephlex/2k](https://media.discordapp.net/attachments/1007286874525667470/1138624777045684345/cV64ZQW.jpeg?width=913&height=685)

*An analog keypad intended for Osu! with dynamic actuation point, VIA, OLED and RGB*

* Keyboard Maintainer: [Jake Stewart](https://github.com/RephlexZero)
* Hardware Supported: *MoonPad, Minipad, Alphatec Helios, anything RP2040 with minor adjustment*
* Hardware Availability: *https://github.com/RephlexZero/MoonPad*

Make example for this keyboard (after setting up your build environment):

    make rephlex/2k:via

Flashing example for this keyboard:

    make rephlex/2k:via:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and
the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start
with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **VIA**: Enter the flashing mode in the VIA configurator.xz
