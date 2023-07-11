# Keychron V2

![Keychron V2](https://i.imgur.com/mEZWo30h.jpg)

A customizable 65% keyboard.

* Keyboard Maintainer: [Keychron](https://github.com/keychron)
* Hardware Supported: Keychron V2
* Hardware Availability: [Keychron V2 QMK Custom Mechanical Keyboard](https://www.keychron.com/products/keychron-v2-qmk-custom-mechanical-keyboard)

Make example for this keyboard (after setting up your build environment):

    make keychron/v2/ansi:default
    make keychron/v2/ansi_encoder:default
    make keychron/v2/iso:default
    make keychron/v2/iso_encoder:default
    make keychron/v2/jis:default
    make keychron/v2/jis_encoder:default

Flashing example for this keyboard:

    make keychron/v2/ansi:default:flash
    make keychron/v2/ansi_encoder:default:flash
    make keychron/v2/iso:default:flash
    make keychron/v2/iso_encoder:default:flash
    make keychron/v2/jis:default:flash
    make keychron/v2/jis_encoder:default:flash

**Reset Key**: Hold down the key located at *K00*, commonly programmed as *Esc* while plugging in the keyboard.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).