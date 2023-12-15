# cosmo65 by BentoBox Studio

![cosmo65](https://imgur.com/Aav54LWh.png)

A 65% stacked acrylic keyboard with a unique space-themed look.

* Keyboard Maintainer: [Bento Box Studio](https://github.com/BentoBoxStudio)
* Hardware Supported: Supports the cosmo65 keyboard
* Hardware Availability: [BentoBoxStudio](https://bentoboxstudio.xyz)

Make example for this keyboard (after setting up your build environment):

    make cosmo65:default

Flashing example for this keyboard:

    make cosmo65:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
