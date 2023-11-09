# proteus67

![proteus67](https://i.imgur.com/mYhl7Ja.png)

*A short description of the keyboard/project*

* Keyboard Maintainer: [James Gzowski](https://github.com/gzowski)
* Hardware Supported: Elite-C, Elite-Pi or equivilent Pro-Micro with additional I/O along bottom.
* Build Guide: [Proteus67](https://github.com/gzowski/Proteus67)

Generate firmware:

Default firmware:
qmk flash --kb proteus67 --km default

VIA supported firmware:
qmk flash --kb proteus67 --km via

* Not curently listed within VIA, requires design json from [here](https://github.com/gzowski/Proteus67/blob/main/QMK%20Firmware/via.json)
* Enable design mode on [usevia.app](https://usevia.app/settings) and Load Draft definition within the design tab
* Choose the json file linked above.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB, if using a RP2040 press repeatidly to enter boot mode.
* **Hold down boot loader button on MCU** Hold down the boot loader button on the MCU while plugging in the keyboard
