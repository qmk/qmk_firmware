# Elrgo S Split Keyboard

This is a fork of the VOID Ergo S with QMK Configurator support.

Elrgo S uses 2x Arduino Pro Micro (ATmega32U4) with 3D printed case.
 
[Building guide, models for 3D printing](https://github.com/Eloren1/Elrgo_S)

* Keyboard Maintainer: [Eloren](https://github.com/Eloren1)
* Hardware Supported: Arduino Pro Micro
* Hardware Availability: [Open Source](https://github.com/Eloren1/Elrgo_S)

Make example for this keyboard (after setting up your build environment):

    make handwired/elrgo_s:default

Flashing example for this keyboard:

    make handwired/elrgo_s:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly press the button through the hole on the left side of the case.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
