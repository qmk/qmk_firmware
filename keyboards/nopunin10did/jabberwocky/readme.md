# Jabberwocky

![Jabberwocky](https://diplomacyvariants.files.wordpress.com/2021/03/dexterous_jabberwocky.jpg)

A full-size, columnar-staggered, Alice-style keyboard. The Jabberwocky comes in two varieties currently:
* Dexterous (with numpad on the right side, pictured above)
* Sinister (with numpad on the left side)

Both the Dexterous and Sinister use the same firmware.  The numpad and the four keys above it are simply transposed from the right to the left side of the board.

For more information, join the [NoPunIn10Key Discord](https://discord.gg/sku2Y6w).

* Keyboard Maintainer: [Alex Ronke](https://nopunin10did.com/), also known as NoPunIn10Did.
* Hardware Supported: Dexterous Jabberwocky and Sinister Jabberwocky (2021 March)
* Hardware Availability: Currently by request only

To reset the board into bootloader mode, do one of the following:

* If loaded with the default layout, use Function-Escape or Function-R *(the function buttons are the 1u keys next to B and N)*
* Use the physical reset switch near the USB port *(if provided for your version of the board)*
* Use the physical reset switch on the Elite C
* Briefly jump the Reset and Ground pins of the Elite C

Make example for this keyboard (after setting up your build environment):

    make nopunin10did/jabberwocky:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
