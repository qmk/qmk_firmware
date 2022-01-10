# Kastenwagen

![Kastenwagen 1840](https://diplomacyvariants.files.wordpress.com/2022/01/late-harvest-on-kastenwagen.png)
![Kastenwagen 48](https://diplomacyvariants.files.wordpress.com/2022/01/kastenwagen-48-concept-art.png)


A description TBD: 
* Kastenwagen 1840 (with numpad)
* Kastenwagen 48 (with macro column)

Both models use the same firmware.  The keys corresponding to numpad keys 7, 4, and 1 are used as the macro column in the 48.
If using a rotary encoder in the top right, the operation of the rotational pins should be identical between versions.  However, the operation of the encoder when *pressed* will map to the key it replaces, which differs between the 48 and 1840.

For more information, join the [NoPunIn10Key Discord](https://discord.gg/sku2Y6w).

* Keyboard Maintainer: [Alex Ronke](diplomacyvariants.wordpress.com), also known as NoPunIn10Did. 
* Hardware Supported: Kastenwagen 1840 & 48 (2021 June)
* Hardware Availability: Currently by request only

To jump the bootloader, either:
* If loaded with the default layout, use Function-Escape *(the function button is the farthest righthand 1.25u on the bottom row)* **OR**
* Use the physical reset switch on the Elite C **OR**
* Briefly jump the Reset and Ground pins of the Elite C

Make example for the 1840 model (after setting up your build environment):

    make nopunin10did/kastenwagen:default
    
Make example for the 48 model:

    make nopunin10did/kastenwagen:default48

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

![Kastenwagen Default Layouts](https://diplomacyvariants.files.wordpress.com/2022/01/kastenwagen-default-layouts.png)