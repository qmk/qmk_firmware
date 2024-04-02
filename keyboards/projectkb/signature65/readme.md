# Signature65

Project Keyboard ANSI only PCB for Kepler FC65. 

* Keyboard Maintainer: [projectkeyboard](https://github.com/projectkeyboard)
* Hardware Supported: STM32F072CBU6
* Hardware Availability: [projectkeyboard](https://store.projectkeyboard.com/)

Make example for this keyboard (after setting up your build environment):

    make projectkb/signature65:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset switch/button**: Set the dipswitch to the "on" position. Briefly press the button on the back of the PCB. 
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.
