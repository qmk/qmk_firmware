# Keychron C2 Pro V2

![Keychron C2 Pro](https://i.imgur.com/BQE1tFO.jpg)

A customizable 100% keyboard.

Rev1 is based on STM32L432 and rev2 is based on STM32F402.

* Keyboard Maintainer: [Keychron](https://github.com/keychron)
* Hardware Supported: Keychron C2 Pro
* Hardware Availability: [Keychron C2 Pro QMK/VIA Wired Mechanical Keyboard](https://www.keychron.com/products/keychron-c2-pro-qmk-via-wired-mechanical-keyboard)

Make example for this keyboard (after setting up your build environment):

    make keychron/c2_pro_v2/ansi/rgb:default
    make keychron/c2_pro_v2/ansi/white:default

Flashing example for this keyboard:

    make keychron/c2_pro_v2/ansi/rgb:default:flash
    make keychron/c2_pro_v2/ansi/white:default:flash

## bootloader

Enter the bootloader in two ways:

* **Bootmagic reset**: Hold down the key located at *K00*, commonly programmed as *Esc* while plugging in the keyboard.
* **Physical reset button**: Briefly press the RESET button under the spacebar.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
