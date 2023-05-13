# Fidelity

* Keyboard Maintainer: [Cutie Club](https://github.com/cutie-club/)
* Hardware Supported: STM32F072 based PCB for the Fidelity keyboard

## Bootloader

Enter the bootloader in 2 ways with the default configuration:

* **Bootmagic reset**: Hold down the key at top left key (matrix position 0,0) and plug the device in
* **Physical reset button**: Press the button marked reset on the front of the PCB

Make example for this keyboard (after setting up your build environment):

    make cutie_club/keebcats/fidelity:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
