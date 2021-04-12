# Viktus Deltablade

![Deltablade](https://i.imgur.com/)

The Viktus Deltablade is a 660 layout created in collaboration with BlindAssassin111 (Viktus owner) and ai03 (Lunar, Polaris, and Vega ). The board supports ANSI and ISO enter, split backspace, stepped/non-stepped caps lock, split left and right shift, as well as 6.25u and 7u spacebars.

The PCB is an arm powered board utilizing the STM32F072CBT6 mcu. The PCB is designed to work with the universal daughterboard and a 4in (~100mm) 4 pin JST SR cable with reversed pinout (pin 1 of both connectors is the same wire etc.).

On the PCB is a single button reset for flashing. As well, there is a [Segger J-Link 6-pin Needle Adapter](https://www.segger.com/products/debug-probes/j-link/accessories/adapters/6-pin-needle-adapter/) footprint for reflashing the mcu as a backup in case of a bootloader issue.

* Keyboard Maintainer: [jrfhoutx](https://github.com/jrfhoutx), blindassassin111
* Hardware Supported: Deltablade
* Hardware Availability: <https://www.Viktus.Design>

Make example for this keyboard (after setting up your build environment):

    make viktus/deltablade:default

Flashing example for this keyboard:

    make viktus/deltablade:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
