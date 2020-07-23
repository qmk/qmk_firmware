# QMK-based firmware for Zenith Z-150 keyboard

![Z-150](https://i.imgur.com/zNTHmZa.jpg)

Zenith Z-150 keyboard conversion project: direct connection of Black Pill to the matrix.

* Keyboard Maintainer: [DmNosachev](https://github.com/DmNosachev)
* Hardware Supported: [Zenith Z-150 keyboard](https://deskthority.net/wiki/Zenith_Z-150), Black Pill STM32F103C8T6 MCU board. Alternatevely you can use any MCU which is supported by QMK and has 22 or more IO pins: Arduino Micro, Teensy 2.0, Teensy 2.0++, Blue Pill, etc.

Make example for this keyboard (after setting up your build environment):

    make handwired/z-150:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

# Modding

## Matrix

Z-150 has 11x8 matrix:

The PCB is ghost-free thanks to the diodes.



## Black Pill
Suggested mount position for the Pro Micro:

![PCB bottom side](https://i.imgur.com/bb7zZD0.jpg)

1. Solder 12-pin header to the Black Pill (pins B11–A0 on the left side).
2. Solder two 3-pin headers for boot jumpers.
3. Solder 4-pin SWD header.
4. By this point rows 0-4 and all columns will be already in place.
5. Connect rows 5-9 (see right side of the PCB) to the corresponding pins of the Pro Micro using additional wires.
6. Optional: connect a push button between Reset and Ground pins.

![PCB top side](https://i.imgur.com/PVEXIxj.jpg)

Compile and flash the firmware. Use matrix [debug mode](https://docs.qmk.fm/#/feature_command) if something is wrong.