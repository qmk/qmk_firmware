# ScottoErgo

![ScottoErgo](https://i.imgur.com/FtdSJRBh.jpg)

A 36 key column staggered ergonomic keyboard with 10 degrees of tenting and 20 degrees of angle. Case files available [here](https://github.com/joe-scotto/scottokeebs).

-   Keyboard Maintainer: [Joe Scotto](https://github.com/joe-scotto)
-   Hardware Supported: RP2040
-   Hardware Availability: [Amazon](https://amazon.com)

# Compiling

Make example for this keyboard (after setting up your build environment):

    make handwired/scottokeebs/scottoergo:default

Flashing example for this keyboard:

    make handwired/scottokeebs/scottoergo:default

# Bootloader

Uses [bootmagic](https://github.com/qmk/qmk_firmware/blob/master/docs/feature_bootmagic.md) allowing you to hold the top left key (0, 0) when plugging the board in to enter bootloader mode.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
