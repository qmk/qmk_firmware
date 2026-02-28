# Dilemma

* Keyboard Maintainer: [BastardKB](https://github.com/BastardKB)
* Hardware Supported: Dilemma PCBs with integrated or devlopment board<sup>*</sup> microcontrollers
* Hardware Availability: [GitHub](https://github.com/Bastardkb/Dilemma)

Make example for this keyboard (after setting up your build environment):

    make bastardkb/dilemma/3x5_2/assembled:default
    make bastardkb/dilemma/3x5_2/promicro:default
    make bastardkb/dilemma/3x5_3:default
    make bastardkb/dilemma/4x6_4:default

Flashing example for this keyboard:

    make bastardkb/dilemma/3x5_2/assembled:default:flash
    make bastardkb/dilemma/3x5_2/promicro:default:flash
    make bastardkb/dilemma/3x5_3:default:flash
    make bastardkb/dilemma/4x6_4:default:flash

Note<sup>*</sup>: the `dilemma/3x5_2/promicro` revision is the only DIY Dilemma PCB. It is footprint and pin compatible with a Pro Micro development board, and the firmware is written as such it can be used with the Converter Feature. This PCB uses I2C communication for the Cirque Trackpad, opposed to SPI for the variants with an integrated microcontroller.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix and plug in the keyboard
* **Physical reset button**: Double-tap the reset button under/near the microcontroller.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
