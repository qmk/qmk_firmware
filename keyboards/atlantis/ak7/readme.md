# AK7

![AK7](https://i.imgur.com/vbPhB2T.jpg)

A 6 key macropad with a encoder

* Keyboard Maintainer: [peepeetee](https://github.com/peepeetee)
* Hardware Supported: Atlantis AK7 play
* Hardware Availability: https://www.aliexpress.com/item/1005003301486950.html

Make example for this keyboard (after setting up your build environment):

    make atlantis/ak7:default

Flashing example for this keyboard:

    make atlantis/ak7:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Short the two contacts at the back of the PCB
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
