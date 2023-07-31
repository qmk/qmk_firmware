# rephlex/2k

![%KEYBOARD%](imgur.com image replace me!)

*An analog keypad intended for Osu! with dynamic actuation point, VIA, OLED and RGB*

* Keyboard Maintainer: [Jake Stewart](https://github.com/RephlexZero)
* Hardware Supported: *MoonPad, Minipad, Alphatec Helios, anything RP2040 with minor adjustment*
* Hardware Availability: *https://github.com/RephlexZero/MoonPad*

Make example for this keyboard (after setting up your build environment):

    make rephlex/2k:via

Flashing example for this keyboard:

    make rephlex/2k:via:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Not possible due to analog calibration of keyboard on boot
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Unmapped due to small layout.
* **VIA**: Enter the flashing mode in the VIA configurator.