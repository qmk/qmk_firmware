# Packrat

![Packrat](https://i.imgur.com/t6vWYIbh.jpeg)

Full Gallery: https://imgur.com/gallery/fZklCG6

Packrat is an 11u wide ortholinear keyboard featuring multiple bottom row options and top-centered rotary encoder support.

* Keyboard Maintainer: [H. Bond](https://github.com/drhigsby)
* Hardware Supported: Packrat (https://github.com/drhigsby/packrat)
* Hardware Availability: cases available at TBD / make your own

Make example for this keyboard (after setting up your build environment):

    make packrat:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
