# Ampersand

![Ampersand](https://i.imgur.com/jbr7Bld.png)

Ampersand is a gummyworm mounted 13.5u keyboard with minimum 40s support needed.
Its frosted polycarbonate case and blasted brass weight will pair well with most keysets, with greater compatibility than most 40s.

* Keyboard Maintainer: [roarmstrong](https://github.com/roarmstrong)
* Hardware Supported: Ampersand custom PCB, using Atmega32u4
* Hardware Availability: [Coffee Break Keyboards](https://www.cbkbd.com/product/ampersand), [Keeb Supply](https://keeb.supply/products/ampersand)

Make example for this keyboard (after setting up your build environment):

    make whitefacemountain/ampersand:default

Flashing example for this keyboard:

    make whitefacemountain/ampersand:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the top left key) and plug in the keyboard
* **Physical reset button**: Briefly press the button labelled SW1 on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
