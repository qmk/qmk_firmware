# KinTwin
[KinTwin](https://github.com/alvicstep/kintwin) is a drop-in replacement of a controller and thumb cluster PCB boards for [Kinesis Contoured keyboards](https://deskthority.net/wiki/Kinesis_Contoured). The controller board is a fork of [KinBP](https://github.com/DmNosachev/KinBP). 

### Keyboard
![Kinesis keyboard](https://i.imgur.com/gmuYlUyh.jpg)

### Controller
![KinTwin controller](https://i.imgur.com/vu6pexwh.jpg)

The main difference between KinTwin and KinT controllers is that the former utilizes **Blackpill STM32F401** development board and the latter utilizes **Teensy** development boards.

* Keyboard Maintainer: Alex Stepanov
* Hardware Supported: KinTwin PCB, WeAct Black Pill STM32F401 micro controller
* Hardware Availability: [Open Source (CC-BY-SA)](https://github.com/alvicstep/kintwin)

Make example for this keyboard (after setting up your build environment):

    make kinesis/kintwin:default

Flashing example for this keyboard:

    make kinesis/kintwin:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard.
* **Physical reset button**. Hold 'boot0' button on MCU board, press 'reset', then release 'boot0'.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
