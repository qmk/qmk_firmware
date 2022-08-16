# Kin80

![Kin80 controller](https://i.imgur.com/Im19DdHh.jpg)

Kin80 is a set of replacement PCBs and switch mounting plates for [Kinesis Contoured keyboards](https://deskthority.net/wiki/Kinesis_Contoured).

* Keyboard Maintainer: [Dmitriy Nosachev](mailto:quartz64@gmail.com)
* Hardware Supported: Kin80 PCB
* Hardware Availability: [Open Source (CC-BY-SA](https://github.com/DmNosachev/kin80)

There are 4 versions of the controller PCB, which correspond to the subfolder names:

* 'micro': rev. 1.1 (obsolete) used Arduino Micro board.
* 'blackpill103': rev. 1.2 (obsolete) used 'Black Pill' boards with STM32F103C8T6 MCU.
* 'blackpill401' and 'blackpill411'. Latest Kin80 PCB revisions (1.3+) use WeAct Studio STM32F401 or STM32F411 boards. They are pin compatible with each other, but use different MCUs.

Make example for this keyboard (after setting up your build environment):

    `qmk compile -kb kin80 -km default`

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

Default version is 'blackpill401'. If you need to build a firmware for STM32F411, use 'blackpill411' version, e.g.:

  `qmk compile -kb kin80:blackpill411 -km default`

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the the top left key and plug in the keyboard.
* **Physical reset button**. Hold 'boot0' button on MCU board, press 'reset', then release 'boot0'.
* **Keycode in layout**: Press the key mapped to `RESET` if it is available