# Flashing Intrustructions

There are quite a few different types of bootloaders that keyboards use, and just about all of the use a different flashing method. Luckily, projects like the [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) aim to be compatible with all the different types without having to think about it much, but this article will describe the different types of bootloaders, and available methods for flashing them.

## DFU

Atmel's DFU bootloader comes on all atmega32u4 chips by default, and is used by many keyboards that have their own ICs on their PCBs (Older OLKB boards, Clueboards). Some keyboards may also use LUFA's DFU bootloader (or QMK's fork) (Newer OLKB boards) that adds in additional features specific to that hardware.

These bootloaders are usually 4096 bytes for the atmega32u4 chip. 

Compatible flashers:

* [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) (recommended GUI)
* [dfu-programmer](https://github.com/dfu-programmer/dfu-programmer) / `:dfu` in QMK (recommended commandline)
* [Atmel's Flip](http://www.atmel.com/tools/flip.aspx) (not recommended)

Flashing sequence:

1. Press the `RESET` keycode, or tap the RESET button (or short RST to GND).
2. Wait for the OS to detect the device
3. Erase the memory (may be done automatically)
4. Flash a .hex file
5. Reset the device into application mode (may be done automatically)

or:

    make <keyboard>:<keymap>:dfu

## Caterina

Arduino boards and their clones use the [Caterina bootloader](https://github.com/arduino/Arduino/tree/master/hardware/arduino/avr/bootloaders/caterina) (any keyboard built with a Pro Micro, or clone), and uses the avr109 protocol to communicate through virtual serial. Bootloaders like [A-Star](https://www.pololu.com/docs/0J61/9) are based on Caterina.

This block of code allows for Caterina compatibility in QMK:

    #define CATERINA_BOOTLOADER

These bootloaders are usually 4096 bytes for the atmega32u4 chip. 

Compatible flashers:

* [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) (recommended GUI)
* [avrdude](http://www.nongnu.org/avrdude/) with avr109 / `:avrdude` (recommended commandline)
* [AVRDUDESS](https://github.com/zkemble/AVRDUDESS)

Flashing sequence:

1. Press the `RESET` keycode, or short RST to GND quickly (you only have 7 seconds to flash once it enters)
2. Wait for the OS to detect the device
4. Flash a .hex file
5. Wait for the device to reset automatically

or

    make <keyboard>:<keymap>:avrdude

## Halfkay

Halfkay is a super-slim protocol developed by PJRC that uses HID, and come on all Teensys (namely the 2.0).

This bootloader is 512 bytes.

Compatible flashers:

* [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) (recommended GUI)
* [Teensy Loader](https://www.pjrc.com/teensy/loader.html)
* [Teensy Loader Command Line](https://www.pjrc.com/teensy/loader_cli.html) (recommended commandline)

Flashing sequence:

1. Press the `RESET` keycode, or short RST to GND quickly (you only have 7 seconds to flash once it enters)
2. Wait for the OS to detect the device
4. Flash a .hex file
5. Reset the device into application mode (may be done automatically)

