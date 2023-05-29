# Scarlet Bandana Version IV Mark 2

* Keyboard Maintainer: [Cole Markham](https://github.com/colemarkham)
* Hardware Supported: Scarlet Bandana Version IV Mark 2
* Hardware Availability: [~~WoodKeys.click~~ (no longer available)](https://woodkeys.click/product/scarlet-bandana-version-iv-mark-2/)

Make example for this keyboard (after setting up your build environment):

    make woodkeys/scarletbandana:default

Flashing example for this keyboard:

    make woodkeys/scarletbandana:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
