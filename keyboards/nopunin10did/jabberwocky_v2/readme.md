# Jabberwocky

![Jabberwocky](https://diplomacyvariants.files.wordpress.com/2021/03/dexterous_jabberwocky.jpg)

A full-size, columnar-staggered, Alice-style keyboard. Specifically, this firmware is for the v2 PCB, which uses an STM MCU and a unified daughterboard. It is currently only available in the Sinister configuration (southpaw / left-side number pad).

For more information, join the [NoPunIn10Key Discord](https://discord.gg/sku2Y6w).

* Keyboard Maintainer: [Alex Ronke](https://nopunin10did.com/), also known as [NoPunIn10Did](https://github.com/NoPunIn10Did)
* Hardware Supported: Sinister Jabberwocky v2 (2022 Aug)
* Hardware Availability: Currently by request only

To reset the board into bootloader mode, do one of the following:

* If loaded with the default layout, use Function-Escape or Function-R *(the function buttons are the 1u keys next to B and N)*
* TBD: Instructions for the two-step boot

Make example for this keyboard (after setting up your build environment):

    make nopunin10did/jabberwocky_v2:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
