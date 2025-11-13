# Equinox XL

![Cover image](https://i.imgur.com/sQpe0Zv.jpg)

A numrowless 50% keyboard  

* Keyboard Maintainer: [ai03](https://github.com/ai03-2725)
* Hardware Supported: The Equinox XL PCB, powered by the Atmega32u4
* Hardware Availability: Available via group buy


Make example for this keyboard (after setting up your build environment):

    make ai03/equinox_xl:default

Flashing example for this keyboard:

    make ai03/equinox_xl:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Press the reset button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
