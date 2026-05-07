# DE80

![deemen17/de80](https://i.imgur.com/oZvFM0G.png)

The DE80 is a portable TKL PCB that features a compact A87 form factor, dual USB Type C ports (breakable), seven JST SH 4P 1.0 ports, two FPC ports, and compatibility with both F12 and F13 footprints, making it suitable for use with a variety of TKL boards.

* Keyboard Maintainer: [Deemen17](https://github.com/Deemen17)
* Hardware Supported: DE80 R1 2024 PCB w/ STM32F103 MCU
* Hardware Availability: [Deemen17 Facebook Page](https://www.facebook.com/deemen17/), [Deemen17 Works Instagram](https://www.instagram.com/deemen17.works)

Make example for this keyboard (after setting up your build environment):

    make deemen17/de80:default

Flashing example for this keyboard:

    make deemen17/de80:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (ESC/Escape) and plug in the keyboard
* **Physical reset button**: Double tap the button RESET on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
