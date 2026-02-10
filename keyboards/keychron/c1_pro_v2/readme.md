# Keychron C1 Pro V2

![Keychron C1 Pro](https://i.imgur.com/Svdm4lph.jpg)

A customizable 80% TKL keyboard.

v1 is based on STM32L432 and v2 is based on STM32F402.

* Keyboard Maintainer: [Keychron](https://github.com/keychron)
* Hardware Supported: Keychron C1 Pro
* Hardware Availability: [Keychron](https://www.keychron.com)

Make example for this keyboard (after setting up your build environment):

    make keychron/c1_pro_v2/ansi/rgb:default
    make keychron/c1_pro_v2/ansi/white:default
    make keychron/c1_pro_v2/ansi/non_light:default

Flashing example for this keyboard:

    make keychron/c1_pro_v2/ansi/rgb:default:flash
    make keychron/c1_pro_v2/ansi/white:default:flash
    make keychron/c1_pro_v2/ansi/non_light:default:flash

## bootloader

Enter the bootloader in two ways:

* **Bootmagic reset**: Hold down the key located at *K00*, commonly programmed as *Esc* while plugging in the keyboard.
* **Physical reset button**: Briefly press the RESET button under the spacebar.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
