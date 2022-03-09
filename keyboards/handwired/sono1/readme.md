# QMK-based firmware for ASkeyboard Sono1 keyboard with additional Sono2 numpad

![Sono1](https://i.imgur.com/eb046DOh.jpeg)

ASkeyboard Sono1 keyboard conversion project: direct connection of Black Pill to the matrix.

* Keyboard Maintainer: [DmNosachev](https://github.com/DmNosachev)
* Hardware Supported: [ASkeyboard Sono1](http://www5f.biglobe.ne.jp/~silencium/keyboard/html/alps.html), Teensy 2.0++ or Black Pill STM32F103C8T6 MCU board. Alternatively you can use any MCU which is supported by QMK and has 28 IO pins or more (15x8 matrix and 5 LEDs): Blue Pill, Black Pill STM32F4xx, etc.

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb handwired/sono1:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

# Modding

## Matrix

ASkeyboard Sono1 has 15x8 matrix. Sono2 numpad connects directly to the main matrix.

Rows (R0-RE) and columns (R0-C7):
![Sono1 rows and columns](https://i.imgur.com/5Owazg6h.jpeg)

Desolder all ICs, capacitors and resistors except R10–R14.

## LEDs
Keyboard has 5 LEDs with common anode. Their cathodes are connected to R10–R14 resistors (you may want to replace them to adjust LED brightness for 3.3V voltage). Add 5 wire jumpers to connect them to the corresponding traces.

![Sono1 LEDs](https://i.imgur.com/opxc2A3h.jpeg)

## Teensy 2.0++
Suggested mount position for the Teensy 2.0++ (view from the bottom side of the PCB):
```
     R8 R9 RA RB RC RD RE L0    R8    C7 C6 C5 C4 C3 C2 C1 C0
      *  |  |  |  |  |  |  |     *     |  |  |  |  |  |  |  |
    ,------------------------------------------------------------,
,---|GN B7 D0 D1 D2 D3 D4 D5 D6 D7 E0 E1 C0 C1 C2 C3 C4 C5 C6 C7 |
|   |D7                                                          |
|USB|                                                            |
|   |GN                                                          |
'---|V  B6 B5 B4 B3 B2 B1 B0 E7 E6 G  A  F0 F1 F2 F3 F4 F5 F6 F7 |
    `------------------------------------------------------------'
     *         |  |  |  |                 |  |  |  |  |  |  |  |
     GN       L2 L1 L3 L4                R7 R6 R5 R4 R3 R2 R1 R0
```
Asterisk sign designates pins of the Teensy that don't align properly with PCB and need to be rewired.

1. Compile and flash the firmware: `qmk compile -kb handwired/sono1/t2pp:default:flash`. Press the reset button on Teensy to launch the bootloader.
2. You will need to solder several pin headers to Teensy: two 7 pin headers (C0–C7, D5–B7), 8 pin (F0–F7) and 4 pin (B1—B4). 
3. Solder the Teensy to keyboard's PCB. You will need to manually reroute only 3 pins.

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

1. Solder 4-pin SWD header to Black Pill.
2. Burn [STM32duino bootloader](https://github.com/rogerclarkmelbourne/STM32duino-bootloader/blob/master/bootloader_only_binaries/generic_boot20_pb12.bin) to Black Pill.
3. Compile and flash the firmware: `qmk compile -kb handwired/sono1/stm32f103:default:flash`
4. Connect rows, columns and LED pads to the corresponding pins of the Black Pill.

## Keymap
'CUR LOCK' key on Sono2 numpad has locking switch by default (Alps SKCL lock). QMK [supports mechanical locking switches](https://docs.qmk.fm/#/faq_keymap?id=mechanical-lock-switch-support) for CapsLock, NumLock and ScrollLock keycodes.

There is 'debug' keymap which doesn't output any scancodes, but displays row and column numbers of pressed buttons to console (hid_listen or QMK Toolbox).
