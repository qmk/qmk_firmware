# Caffeinated Studios' Serpent65

![Serpent65](https://i.imgur.com/rAsZsXk.png)

The Serpent65 is a 65% created by Caffeinated Studios. The board supports ANSI and ISO modifiers as well as split backspace and stepped/non-stepped caps lock.

The PCB is an ARM powered board utilizing the STM32F072CBT6 mcu, designed by BlindAssassin111. The PCB is designed to work with the universal daughterboard and a 4in (~100mm) 4 pin JST SR cable with reversed pinout (pin 1 of both connectors is the same wire etc.).

On the PCB is a single button for a reset for flashing. As well, there is a [Segger J-Link 6-pin Needle Adapter](https://www.segger.com/products/debug-probes/j-link/accessories/adapters/6-pin-needle-adapter/) footprint for reflashing the mcu as a backup in case of a bootloader issue.

* Keyboard Maintainer: [jrfhoutx](https://github.com/jrfhoutx)
* Hardware Supported: Serpent65
* Hardware Availability: Coming Soon

Make example for this keyboard (after setting up your build environment):

    make caffeinated/serpent65:default

Flashing example for this keyboard:

    make caffeinated/serpent65:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
