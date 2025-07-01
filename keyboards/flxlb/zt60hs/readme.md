# flxlb ZT60

![ZT60](https://i.imgur.com/3t3Q4eN.jpeg)

A premium 60% ortholinear keyboard engineered for both form and function, the ZT60 features a clean ortholinear layout that enhances finger symmetry and ergonomics without compromising usability. Designed with meticulous attention to detail, it supports most standard keycap sets and offers extensive layout customization options, combining versatility with aesthetic elegance.

* Keyboard Maintainer: [cccywj](https://github.com/cccywj)
* Hardware Supported: ATMEGA32U4
* Hardware Availability: [flxlb](https://www.flxlb.ca)

Make example for this keyboard (after setting up your build environment):

    make flxlb/zt60hs:default

Flashing example for this keyboard:

    make flxlb/zt60hs:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
