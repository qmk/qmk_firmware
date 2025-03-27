# TOTEM split keyboard

![totem](https://imgur.com/a/9GmHxAt)

TOTEM is 38 keys column-staggered split keyboard made by @geigeigeist. 
It uses the Seeed XIAO RP2040.

* Keyboard Maintainer: [GEIST](https://github.com/GEIGEIGEIST)
* Hardware Supported: Seeed XIAO RP2040
* Hardware Availability: [TOTEM Repo containing buildguide](https://github.com/GEIGEIGEIST/TOTEM)

Make example for this keyboard (after setting up your build environment):

    make totem:default

Flashing example for this keyboard:

    make totem:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Quickly double press the button on the top of the PCB, note that this only works after flashing the QMK firmware. For flashing the firmware for first time, you might have to follow Seeed XIAO RP2040 specific instructions to reset the MCU using the "R" and "B" buttons on the MCU.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
