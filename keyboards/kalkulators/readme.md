# kalkulators

![kalkulators](https://imgur.com/a/VdijoMC)

An 8 digit 7-segment display calculator and numpad. 
USB-C, STM32F072, TM1638 LED controller, 1xAA battery.

*When editing layers through keymap or VIA, do not delte/edit the 1st layer, it is needed for the calculator functionality!*

* Keyboard Maintainer: [georgsnarbuts](https://github.com/georgsnarbuts)

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb kalkulators -km via

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Combos

To decrese display brightness: Tap "Delete" and "Divide" buttons in unison.

To increase display brightness: Tap "Delete" and "*" buttons in unison.

To switch between calculator and numpad mode when connected to a host computer: Tap "+" and "-" buttons in unison.

## Bootloader

Enter the bootloader:

* **Physical reset button**:

1) Turn off the battery power switch on the right side of the board.
2) Toggle the boot switch to the bottom position on the back of the PCB.
3) If board already connected to a host computer through USB-C, press the reset button on the back of the PCB. If not plugged in, then just connect the USB-C cable to a host computer and the PCB.
4) Board should have entered the bootloader.

