# Kastenwagen 1840

![Kastenwagen 1840](https://diplomacyvariants.files.wordpress.com/2022/01/late-harvest-on-kastenwagen.png)

Kastenwagen 1840 is a 40% keyboard with a mini-numpad and dedicated arrows.  The main alpha block is 13.75u long, allowing for more dedicated punctuation keys to be paired with common Minivan-like mod keys.

A second model of Kastenwagen, the [Kastenwagen 48](https://github.com/qmk/qmk_firmware/tree/master/keyboards/nopunin10did/kastenwagen48), is similar but replaces the numpad with a three-key macro column.

Please note that the Kastenwagen 1840 via-compatible keymap firmware is also compatible with the Kastenwagen 48.  The Kastenwagen 48 does not have a dedicated via-compatible firmware.

For more information, join the [NoPunIn10Key Discord](https://discord.gg/sku2Y6w).

* Keyboard Maintainer: [Alex Ronke](diplomacyvariants.wordpress.com), also known as NoPunIn10Did. 
* Hardware Supported: Kastenwagen 1840 & 48 (2021 June)
* Hardware Availability: Currently by request only

To jump the bootloader, either:
* If loaded with the default layout, use Function-Escape *(the function button is the farthest righthand 1.25u on the bottom row)* **OR**
* Use the physical reset switch on the Elite C **OR**
* Briefly jump the Reset and Ground pins of the Elite C

Make example for the 1840 model (after setting up your build environment):

    make nopunin10did/kastenwagen1840:default
    
Make example for the 48 model:

    make nopunin10did/kastenwagen48:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

![Kastenwagen Default Layouts](https://diplomacyvariants.files.wordpress.com/2022/01/kastenwagen-default-layouts.png)