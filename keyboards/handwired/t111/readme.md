# QMK-based firmware for Fujitsu N860-2500-T111 keyboard

![Fujitsu T111](https://i.imgur.com/aGtg7FMl.jpg)

Fujitsu N860-2500-T111 keyboard conversion project: direct connection of Black Pill to the matrix.

* Keyboard Maintainer: [DmNosachev](https://github.com/DmNosachev)
* Hardware Supported: [Fujitsu N860-2500-T111](https://deskthority.net/viewtopic.php?t=17087), Black Pill STM32F103C8T6 MCU board. Alternatively you can use any MCU which is supported by QMK and has 22 or more IO pins: Arduino Micro, Teensy 2.0, Teensy 2.0++, Blue Pill, etc.
* Thanks to Deskthority user *OldIsNew* for the matrix decoding.

Make example for this keyboard (after setting up your build environment):

    make handwired/t111:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

# Modding

## Matrix

Fujitsu N860-2500-T111 has 14x8 matrix. It's ghost-free thanks to the diodes.

Rows (0-7) and columns (0-D):
![T111 rows and columns](https://i.imgur.com/37MxQG8h.jpg)

## Black Pill
Suggested mount position for the Black Pill (view from the top side of the PCB):

```
  C1  C2  C3  C4  C7  C8  C9  CA                          R5  R6
,--------------------------------------------------------------------,
|B11 B10  B1  B0  A7  A6  A5  A4  A3  A2  A1  A0 RST C13  B9  B8 GND |---,
|                                                                    |USB|
|B12 B13 B14 B15  A8  A9 A10 A11 A12 A15  B3  B4  B5  B6  B7 3V3 GND |---'
'--------------------------------------------------------------------'
      CC  CD  C0  CB  C6  C5          R0  R4  R3  R2  R1  R7
```

![Black Pill](https://i.imgur.com/lJfdAQTh.jpg)

1. Desolder all ICs, capacitors and resistors.
1. Solder 4-pin SWD header to Black Pill.
2. Burn [STM32duino bootloader](https://github.com/rogerclarkmelbourne/STM32duino-bootloader/blob/master/bootloader_only_binaries/generic_boot20_pb12.bin) to Black Pill.
3. Compile and flash the firmware: `make handwired/t111:default:flash`
4. Connect rows and columns to the corresponding pins of the Black Pill.
