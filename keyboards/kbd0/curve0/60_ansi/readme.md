# kbd0/curve0/60_ansi

![Curve0](https://i.imgur.com/y5ZIbWI.jpeg)

Curve0 - Curved stainless steel keyboard by kbd0

* Keyboard Maintainer: [kbd0](https://github.com/kbd0)
* Hardware Supported: Curve0 PCB
* Hardware Availability: [kbd0.com](https://kbd0.com/item/curve0)

Make example for this keyboard (after setting up your build environment):

    make kbd0/curve0/60_ansi:default

Flashing example for this keyboard:

    make kbd0/curve0/60_ansi:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold the top left key of the keyboard while plugging in the keyboard
* **Physical reset button**: Hold the button on the main PCB (inside the keyboard) while plugging in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
