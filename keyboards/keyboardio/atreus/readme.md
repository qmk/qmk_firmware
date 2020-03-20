# Keyboardio Atreus

![Atreus](https://atreus.technomancy.us/i/atreus2-mug.jpg)

A small mechanical keyboard that is based around the shape of the human hand.

* Keyboard Maintainer: [Keyboardio](https://github.com/keyboardio)
* Hardware Supported: Keyboardio Atreus
* Hardware Availability: https://www.kickstarter.com/projects/keyboardio/atreus

These configuration files are specifically for the Keyboardio Atreus, a
collaboration between [Phil Hagelberg](https://github.com/technomancy) and
[Keyboardio](https://github.com/keyboardio). The keyboard is currently on
Kickstarter, and will come fully assembled.

Make example for this keyboard (after setting up your build environment):

    make keyboardio/atreus:default:avrdude

*Unlike the TMK firmware, these commands should be run from the root of the repository, not the directory containing this readme.*

To flash new firmware, the keyboard needs to be in bootloader mode. To do that,
one needs to hold the bottom left key (`Esc` by default) and reset the
keyboard - either via a macro, or by sending a hang-up signal to the keyboard
device, or by pressing the reset button on the bottom with a pin.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
