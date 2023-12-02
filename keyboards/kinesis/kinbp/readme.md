# KinBP
[KinBP](https://github.com/DmNosachev/kinbp) is a drop-in replacement controller for [Kinesis Contoured keyboards](https://deskthority.net/wiki/Kinesis_Contoured).

It serves the same purpose as [KinT controller](https://github.com/kinx-project/kint) created by Michael Stapelberg.

![KinBP v1.2](https://i.imgur.com/tfWhnpxh.jpg)

* Keyboard Maintainer: Dmitriy Nosachev
* Hardware Supported: KinBP PCB, WeAct Black Pill STM32F401 or STM32F411 based development boards
* Hardware Availability: [Open Source (CC-BY-SA)](https://github.com/DmNosachev/kinbp)

## Features and advantages
- Controller with [QMK firmware](https://qmk.fm/) support.
- Uses inexpensive [WeAct Studio STM32F401/STM32F411](https://github.com/WeActTC/MiniSTM32F4x1) MCU board. The cost of manufacturing 5 sets is about 12 USD per controller. The PCB has dimensions less than 100×100 mm. Many manufacturers provide additional discounts for smaller boards.
- Compatible with all Kinesis Contoured keyboards but the earliest models (100/110/120).
- Additional pads for connecting up to 8 swithes (i.e. additional switches on the keyboard or foot pedals).
- Replacement thumb cluster PCBs with reversible design. They may be needed for some of 13x models (see below). 
- Thumb cluster switch mounting plates.

## Build
Make example for this keyboard (after setting up your build environment):

```
    make kinesis/kinbp:default
```

Flashing example for this keyboard:

```
    make kinesis/kinbp:default:flash
```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard.
* **Physical reset button**. Hold 'boot0' button on MCU board, press 'reset', then release 'boot0'.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

## Additional keys
You can use up to 19 additional switches (e.g. footpedals) by connecting them to the vacant positions of the matrix.
- With `LAYOUT_all` keyboard layout there will be two additonal group of keys below the main block.
- 8 switches (first row of additional keys in `LAYOUT_all`) can be attached to the 16 pin connector on the PCB. Corresponding matrix positions:
| Row    | Column |
| -------| ------ |
| 0      |   6    |
| 1      |   6    |
| 2      |   6    |
| 10 (A) |   6    |
| 11 (B) |   6    |
| 12 (C) |   6    |
| 13 (D) |   6    |
| 14 (E) |   6    |
- Another 11 switches (second row of additional keys in `LAYOUT_all`) must be soldered directly to the matrix. Corresponding matrix positions:
| Row    | Column |
| -------| ------ |
| 0      |   4    |
| 4      |   4    |
| 7      |   4    |
| 11 (B) |   4    |
| 0      |   5    |
| 1      |   5    |
| 4      |   5    |
| 9      |   5    |
| 10     |   5    |
| 11     |   5    |
| 7      |   6    |
