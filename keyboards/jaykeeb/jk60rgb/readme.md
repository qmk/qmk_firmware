# JK60 RGB

![jk60 RGB]( https://i.imgur.com/YP978wp.jpeg )

Layout 60% rgb per keys support keyboard case existing

* Keyboard Maintainer: [Alabahuy](https://github.com/Alabahuy)
* Hardware Supported: JK60 RGB pcb, RP2040, led sk6812 per switch
* Hardware Availability: Private GB

Make example for this keyboard (after setting up your build environment):

    make jaykeeb/jk60rgb:default

Flashing example for this keyboard:

    make jaykeeb/jk60rgb:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
