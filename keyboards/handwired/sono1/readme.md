# QMK-based firmware for ASkeyboard Sono1 keyboard with additional Sono2 numpad

![Sono1](https://i.imgur.com/eb046DOh.jpeg)

ASkeyboard Sono1 keyboard conversion project: direct connection of Black Pill to the matrix.

* Keyboard Maintainer: [DmNosachev](https://github.com/DmNosachev)
* Hardware Supported: [ASkeyboard Sono1](http://www5f.biglobe.ne.jp/~silencium/keyboard/html/alps.html), Black Pill STM32F103C8T6 MCU board. Alternatively you can use any MCU which is supported by QMK and has 28 IO pins or more (15x8 matrix and 5 LEDs): Teensy 2.0++, Blue Pill, etc.

Make example for this keyboard (after setting up your build environment):

    make handwired/sono1:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

# Modding

## Matrix

ASkeyboard Sono1 has 15x8 matrix. Sono2 numpad connects directly to the main matrix.

Rows (R0-RE) and columns (R0-C7):
![Sono1 rows and columns](https://i.imgur.com/5Owazg6h.jpeg)

## LEDs
Keyboard has 5 LEDs with common anode. Their cathodes are connected to R10–R14 resistors (you may want to replace them to adjust LED brightness for 3.3V voltage). Add 5 wire jumpers to connect them to the corresponding traces.

![Sono1 LEDs](https://i.imgur.com/opxc2A3h.jpeg)

## Black Pill
Suggested mount position for the Black Pill (view from the bottom side of the PCB):

```
      R8  R9  RA  RB  RC  RD  RE  L0         Vcc  C7  C6  C5  C4  C3  C2       C1  C0 Vcc
       *   |   |   |   *   |   |   |               |   |   |   |   |   |        *   *   *
    ,------------------------------------------------------------------------,
,---|GND  B8  B9 C13 RST  A0  A1  A2  A3  A4  A5  A6  A7  B0  B1 B10 B11  3V3| A3  A4 3V3
|   | B7             A15                                                  A13|
|USB|                                                                     A14|
|   |                        B12                                     A10  GND|
'---|GND 3V3  B7  B6  B5  B4  B3 A15 A12 A11 A10  A9  A8 B15 B14 B13 B12     |
    '------------------------------------------------------------------------' A9  B3  A5
      |            |   |   |   *                       |   |   |   |   *        *   *   *
     GND          L2  L1  L3  L4                      R7  R6  R5  R4  R3       R2  R1  R0
```
Asterisk sign designates pins of the Black Pill that don't align properly with PCB and need to be rewired.

![Black Pill](https://i.imgur.com/KQjTWVbh.jpeg)

1. Desolder all ICs, capacitors and resistors except R10–R14.
1. Solder 4-pin SWD header to Black Pill.
2. Burn [STM32duino bootloader](https://github.com/rogerclarkmelbourne/STM32duino-bootloader/blob/master/bootloader_only_binaries/generic_boot20_pb12.bin) to Black Pill.
3. Compile and flash the firmware: `make handwired/sono1:default:flash`
4. Connect rows, columns and LED pads to the corresponding pins of the Black Pill.

## Keymap
'CUR LOCK' key on Sono2 numpad has locking switch by default (Alps SKCL lock). QMK [supports mechanical locking switches](https://docs.qmk.fm/#/faq_keymap?id=mechanical-lock-switch-support) for CapsLock, NumLock and ScrollLock keycodes.
