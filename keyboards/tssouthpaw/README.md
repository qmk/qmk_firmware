# TS Southpaw

A southpaw numpad keyboard with RGB matrix and work timer functionality.

* Keyboard Maintainer: [TS Design Works LLC](https://github.com/tsdesignworks)
* Hardware Supported: TS Southpaw Rev 1.6, RP2040 MCU
* Hardware Availability: [GitHub](https://github.com/tsdesignworks/tssouthpaw)

Make example for this keyboard (after setting up your build environment):

    make tssouthpaw:default

Flashing example for this keyboard:

    make tssouthpaw:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly press the button on the back of the PCB
* **Bootmagic reset**: Hold down the ESC key and plug in the keyboard

## Features

* RGB Matrix with 104 LEDs
* Rotary encoder for volume control
* Work timer with visual notifications
* Southpaw numpad layout (numpad on the left side)