# haven60

![haven60](https://i.imgur.com/Uja750Oh.png)

Haven60 PCB for Atelier Haven Haven60% keyboard
both hotswap and solder pcbs use same firmware

* Keyboard Maintainer: [Freather](https://github.com/Freather)
* Hardware Supported: atmega32u4-mu
* Hardware Availability: keyspensory.store

Make example for this keyboard (after setting up your build environment):

    make ah/haven60:default

Flashing example for this keyboard:

    make ah/haven60:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
