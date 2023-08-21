# Fidelity

![Fidelity](https://i.imgur.com/6xelfJeh.jpeg)

The Fidelity is a custom 65% keyboard, a collaboration between HAND Engineering and Koen.

* Keyboard Maintainer: [Cutie Club](https://github.com/cutie-club/)
* Hardware Supported: STM32F072 based PCB for the Fidelity keyboard

Make example for this keyboard (after setting up your build environment):

    make cutie_club/fidelity:default

Flashing example for this keyboard:

    make cutie_club/fidelity:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the top left key) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the front of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
