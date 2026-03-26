# rominronin/katana60/rev4_tp

![rominronin/katana60/rev4_tp](imgur.com image replace me!)

## Introduction

A recent revision of the original katana60, this one adds an often requested trackpoint to the board, and steps away from some of the original design goals.

The trackpoint is optional and requires soldering. Trackpoint support has been developed with a specific make and model in mind: Sprintek SK8707-01-005/8 - it can be ordered from [their website](link-to-sprintek). Some enterprising maker could no doubt make it work with an alternative, salvaged trackpoint unit, but I can offer no support for such endeavours (I barely had the time for this project!).

* Keyboard Maintainer: [Baris Tosun](https://github.com/rominronin)
* Hardware Supported: Katana60 TP PCB
* Hardware Availability: Not currently available.
* Cases: Compatible with 60% cases, please read compatibility notes at [rominronin.net](https://rominronin.net)

## Development notes

Make example for this keyboard (after setting up your build environment):

    make rominronin/katana60/rev4_tp:default

Flashing example for this keyboard:

    make rominronin/katana60/rev4_tp:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

## Credits

* Thank you to everyone at the Trackpoint Builders discord. I idled in that group for many years before I actually had the time (and motivation) to start this project.
* Thank you to everyone at the Keyboard Atelier, I levelled up from a headstrong guide follower to someone who makes deliberate choices in the PCB design process. I'm still no expert, but I'd be further from where I am without that wonderful community
* Thank you to David, fromerly from CandyKeys - without his support this project would have been a personal play thing, and nothing more. His support of this project brought the concept to an eccentric and niche audience.
* Thank you to 