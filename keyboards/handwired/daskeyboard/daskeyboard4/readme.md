# daskeyboard4

![daskeyboard4pro](https://i.imgur.com/Y3xT9Zuh.jpeg)

![PCB](https://i.imgur.com/UfzVHcjh.jpeg)

Reverse engineered PCB definition of daskeyboard 4 (Professional)

* Keyboard Maintainer: [Commander1024](https://github.com/Commander1024)
* Hardware Supported: The PCB, rotary encoder, LEDs
* Hardware Availability: https://www.daskeyboard.com/de/daskeyboard-4-professional/
* Microcontroller used: https://stm32-base.org/boards/STM32F401CEU6-WeAct-Black-Pill-V3.0.html

I used a WeAct Black Pill V3.0 featuring the STM32F401CEU6 processor to replace the keyboard's destroyed controller. This keyboard definition can also be easily adopted to use any other microcontroller compatible with QMK and with sufficient I/O ports.

The layout definition in **info.json** contains the magic. The rows and columns appear in the pin definition in the order they appear on the 26 pads, where the original ribbon cable was connected. **Note**: Pad 25 is not connected.

It *should* work for ANSI as well as ISO variants, although I only tested the latter.

Rotary encoder and LEDs are handwired.

## Media key mapping
KC_RGUI (right super key) is used to switch or toggle (double tap) to media layer.  
The rotary encoder is used for volume control.
![mediakeys](https://i.imgur.com/9g7tQzF.jpg)

Make example for this keyboard (after setting up your build environment):

    make handwired/daskeyboard/daskeyboard4:default

Flashing example for this keyboard:

    make handwired/daskeyboard/daskeyboard4:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (5,16) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

## PCB-Pinout
| PCB-pin | properties                  | STM32F411   |
|---------|-----------------------------|-------------|
| 1       | column, diode, 4 switches   |    C14      |
| 2       | row, no diode, 13 switches  |    A13      |
| 3       | row, no diode, 15 switches  |    A14      |
| 4       | column, diode, 3 switches   |    C15      |
| 5       | column, diode, 8 switches   |    A0       |
| 6       | row, no diode, 14 switches  |    A1       |
| 7       | column, diode, 7 switches   |    A2       |
| 8       | row, no diode, 13 switches  |    A3       |
| 9       | column, diode, 7 switches   |    A4       |
| 10      | column, diode, 7 switches   |    A5       |
| 11      | column, diode, 8 switches   |    A6       |
| 12      | column, diode, 8 switches   |    A7       |
| 13      | column, diode, 7 switches   |    B0       |
| 14      | column, diode, 7 switches   |    B1       |
| 15      | column, diode, 7 switches   |    B10      |
| 16      | column, diode, 7 switches   |    B9       |
| 17      | row, no diode, 12 switches  |    B8       |
| 18      | column, diode, 2 switches   |    B7       |
| 19      | column, diode, 2 switches   |    B6       |
| 20      | column, diode, 6 switches   |    B5       |
| 21      | column, diode, 6 switches   |    B4       |
| 22      | row, no diode, 12 switches  |    B3       |
| 23      | row, no diode, 10 switches  |    A15      |
| 24      | row, no diode, 15 switches  |    B15      |
| 25      | N/C                         |             |
| 26      | column, diode, 7 switches   |    A8       |
