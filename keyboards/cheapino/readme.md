# Cheapino

![Cheapino](https://imgur.com/OhU5RCc.png)

A budget-friendly 36-key split keyboard with a rotary encoder, designed as an accessible entry point for building and programming your own keyboard. Both halves share one RP2040 controller, connected over an RJ45 cable.

* Keyboard Maintainer: [Thomas Haukland](https://github.com/tompi)
* Hardware Supported: Cheapino v1 and v2 PCBs with an RP2040-Zero controller
* Hardware Availability: Open source, design files and build guide at [tompi/cheapino](https://github.com/tompi/cheapino)

Make example for this keyboard (after setting up your build environment), using `v1` or `v2` to match your PCB:

    make cheapino/v2:default

Flashing example for this keyboard:

    make cheapino/v2:default:flash

The firmwares aren't interchangeable, because the two revisions are wired differently.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key (Q in the default keymap) and plug in the keyboard
* **Physical reset button**: Hold the BOOT button on the RP2040-Zero while plugging in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
