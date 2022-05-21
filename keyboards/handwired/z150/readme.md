# QMK-based firmware for Zenith Z-150 keyboard

![Z-150](https://imgur.com/jayyyvJ.jpg)

Zenith Z-150 keyboard conversion project: direct connection of Black Pill to the matrix.

* Keyboard Maintainer: [DmNosachev](https://github.com/DmNosachev)
* Hardware Supported: [Zenith Z-150 keyboard, 100-1860 version with white logo](https://deskthority.net/wiki/Zenith_Z-150), Black Pill STM32F103C8T6 MCU board. Alternatevely you can use any MCU which is supported by QMK and has 22 or more IO pins: Arduino Micro, Teensy 2.0, Teensy 2.0++, Blue Pill, etc.

Earlier 100-1886 version with black logo has different PCB.

Make example for this keyboard (after setting up your build environment):

    make handwired/z150:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

# Modding

## Matrix

Z-150 has 11x8 matrix. It's ghost-free thanks to the diodes.

Columns are located under NEC D8049HC MCU IC:
![Z-150 columns](https://imgur.com/XiOsrnh.jpg)

Rows are connected to unmarked 24-pin MUX IC:
![Z-150 rows](https://imgur.com/Wu8rHY0.jpg)

## LEDs

LEDs (from left to right): NumLock, CapsLock, ScrollLock:
![Z-150 LED cathodes](https://imgur.com/MO5NLlZ.jpg)

Their anodes are connected to VCC through 220Ω resistors.
![Z-150 LED anodes](https://imgur.com/w1MfjRN.jpg)

You can keep the original resistors, but with Black Pill or any other 3.3V controller the LEDs may seem a little dim. Try 150Ω or close value if you want to fix that.


## Black Pill
Suggested mount position for the Black Pill (view from the bottom side of the PCB):

```
      R0  R1  R2  R3  R4  R6          R9  LC  LN  LS
,--------------------------------------------------------------------,
|B12 B13 B14 B15  A8  A9 A10 A11 A12 A15  B3  B4  B5  B6  B7 3V3 GND |---,
|                                                                    |USB|
|B11 B10  B1  B0  A7  A6  A5  A4  A3  A2  A1  A0 RST C13  B9  B8 GND |---'
'--------------------------------------------------------------------'
  C0  C1  C2  C3  C4  C5  C6  C7  R5  R8  R7  RA    
```


1. Desolder all ICs, crystal oscillator, capacitors and resistors except R0–R2 (they connect LEDs to VCC).
1. Solder 12-pin header to the Black Pill (pins B11–A0 on the left side).
2. Solder two 3-pin headers for boot jumpers.
3. Solder 4-pin SWD header.
4. Burn [STM32duino bootloader](https://github.com/rogerclarkmelbourne/STM32duino-bootloader/blob/master/bootloader_only_binaries/generic_boot20_pb12.bin) to Black Pill.
5. Compile and flash the firmware: `make handwired/z150:default:flash`
5. Align Black Pill pins B11–A4 with columns 0–7 and solder them.
6. Connect rows, LEDs, ground and VCC traces to the corresponding pins of the BlackPill using additional wires.
