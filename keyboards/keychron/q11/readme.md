# Keychron Q11

![Keychron Q11](https://i.imgur.com/FPTNqKj.jpg)

A customizable 75% split keyboard.

* Keyboard Maintainer: [Keychron](https://github.com/keychron)
* Hardware Supported: Keychron Q11
* Hardware Availability: [Keychron Q11 QMK Custom Mechanical Keyboard](https://www.keychron.com/products/keychron-q11-qmk-custom-mechanical-keyboard)

Make example for this keyboard (after setting up your build environment):

    make keychron/q11/ansi_encoder:default
    make keychron/q11/iso_encoder:default

Flashing example for this keyboard:

    make keychron/q11/ansi_encoder:default:flash
    make keychron/q11/iso_encoder:default:flash

**Reset Key**: The master and slave side should be flashed individually, to enter flashing mode, hold down the key located at *K01*, which programmed as *Esc* while plugging in the keyboard for the master side and hold down the key located at *K67*, which programmed as *Del* while plugging in the keyboard for the slave side.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
