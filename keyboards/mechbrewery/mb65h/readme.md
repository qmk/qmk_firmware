# MechBrewery MB65H

65% keyboard with originally sold for the MechBrewery MB-65H.

* Keyboard Maintainer: [tuananhnguyen204](https://github.com/AnthonyNguyen168) (tuananhnguyen204@gmail.com)
* Hardware Supported: MechBrewery MB-65H
* Hardware Availability: https://mechbrewery.com/
* Enter the bootloader in 3 ways:
* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

Make example for this keyboard (after setting up your build environment):

    make mechbrewery/mb65h:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
