# io_mini1800

This keyboard is a mini 1800 with a minimal navigation cluster, which also offers a rotary encoder option.

* Keyboard Maintainer: [s8erdude](https://github.com/jpuerto96)
* Hardware Supported: IO-Mini 1800
* Hardware Availability: [P3D Store](https://p3dstore.com/)

Make example for this keyboard (after setting up your build environment):

    make io_mini1800:default

Flashing example for this keyboard:

    make io_mini1800:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

To reset the board into bootloader, do one of the following:

* **Hardware reset**: short the pad labeled RESET on the back, near the microcontroller
* **Bootmagic reset**: hold down the top left key (usually programmed as Escape) while plugging in the keyboard (also resets persistent storage)
