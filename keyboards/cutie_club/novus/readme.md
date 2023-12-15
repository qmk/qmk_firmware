# Novus

![Novus](https://i.imgur.com/kuCDFb0h.png)

Novus 60% Keyboard

* Keyboard Maintainer: [Cutie Club](https://github.com/cutie-club)
* Hardware Supported: Atmega32u4 based pcb for Novus keyboard
* Hardware Availability: https://mechsandco.com/products/gb-novus60-keyboard

Make example for this keyboard (after setting up your build environment):

    make cutie_club/novus:default

Flashing example for this keyboard:

    make cutie_club/novus:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Using the default keymaps you can enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the top left key) and plug in the keyboard
* **Physical reset button**: Press the button on the back of the PCB