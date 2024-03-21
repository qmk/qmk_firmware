# Pizza Keyboards (V2) Slice65

![Pizza V2](https://i.imgur.com/RfqnpVlh.jpeg)

A 65% keyboard kit made and sold by [pizza keyboards](https://keyboards.pizza).

* Keyboard Maintainer: [mm0nte](https://github.com/mm0nte)
* Hardware Supported: Pizza V2 Slice65 (Hotswap) PCB
* Hardware Availability: [Pizza Keyboards Store](https://keyboards.pizza/collections/store)

Make example for this keyboard (after setting up your build environment):

    make pizzakeyboards/slice65:default

Flashing example for this keyboard:

    make pizzakeyboards/slice65:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
