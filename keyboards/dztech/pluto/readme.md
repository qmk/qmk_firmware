# PLUTO

![PLUTO](https://i.imgur.com/BWVvKMO.jpg)

The main purpose of this board is to introduce more people to the best layout.
This board was originally designed to be O-ring gasket mount only, Top mount was added to make the board whole.
Sticking with a mimal design, the engraving of planets was replaced with the Logo surrounding with pluto moons and planets.
Pluto now also features an accent Piece with an engraving of Pluto Symbol below the nav cluster.

* Keyboard Maintainer: [DZTECH](https://github.com/moyi4681)
* Hardware Supported: DZTECH
* Hardware Availability: KBDFANS

Make example for this keyboard (after setting up your build environment):

    make dztech/pluto:default

Flashing example for this keyboard:

    make dztech/pluto:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
