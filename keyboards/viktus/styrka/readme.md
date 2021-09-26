# Viktus Styrka

![Styrka](https://i.imgur.com/)

The Viktus Styrka is a 65% + left macro block created in a collaboration of OneCreativeMind and BlindAssassin111 (Viktus owner). All design done by BlindAssassin111. The board supports ANSI and ISO modifiers as well as split backspace and stepped/non-stepped caps lock.

The PCB is an arm powered board utilizing the STM32F072CBT6 mcu. The PCB is designed to work with the universal daughterboard and a 4in (~100mm) 4 pin JST SR cable with reversed pinout (pin 1 of both connectors is the same wire etc.).

On the PCB is a single button for a reset for flashing. As well, there is a [Segger J-Link 6-pin Needle Adapter](https://www.segger.com/products/debug-probes/j-link/accessories/adapters/6-pin-needle-adapter/) footprint for reflashing the mcu as a backup in case of a bootloader issue.

* Keyboard Maintainer: [jrfhoutx](https://github.com/jrfhoutx), blindassassin111
* Hardware Supported: Styrka
* Hardware Availability: <https://www.Viktus.Design>

Make example for this keyboard (after setting up your build environment):

    make viktus/styrka:default

Flashing example for this keyboard:

    make viktus/styrka:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
