# Sunsetter R2

![Sunsetter R2](https://i.imgur.com/rQRuHRkh.jpeg)

A 65 + 10% F-Key Column Keyboard kit made and sold by Charue Design.

Round 2 includes RGB underglow, new case colors, a hotswap option, and a recessed USB port.

[More info on charue-design.com](https://charue-design.com/)

* Keyboard Maintainer: [ILWrites](https://github.com/PiKeeb)
* Hardware Supported: [Sunsetter PCB](https://charue-design.com/collections/sunsetter)
* Hardware Availability: [Charue Design](https://charue-design.com/)

Make example for this keyboard (after setting up your build environment):

    make charue/sunsetter_r2:default

Flashing example for this keyboard:

    make charue/sunsetter_r2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
