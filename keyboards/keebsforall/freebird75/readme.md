# Freebird 75

![fb75](https://i.imgur.com/fGRQZ2gh.jpg)

The Freebird75 is the latest addition to the Freebird line at KeebsForAll, a series aiming to provide a set of good quality keyboards at an affordable price

* Keyboard Maintainer: [Elliot Powell](https://github.com/e11i0t23)
* Hardware Supported: Freebird75
* Hardware Availability: [KeebsForAll](https://keebsforall.com/products/freebird75)

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb keebsforall/freebird75 -km via

Flashing example for this keyboard:

    qmk flash -kb keebsforall/freebird75 -km via

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
