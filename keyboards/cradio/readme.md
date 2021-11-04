# Cradio keyboards

![Cradio](https://github.com/davidphilipbarr/hypergolic/raw/main/hypergarlic/ht.png)

Cradio are low-profile 34-key split-keyboards designed by [@davidphilipbarr](https://github.com/davidphilipbarr), with no diodes and direct micro-controller pin wiring.

## Keyboard Info

* Keyboard Maintainer: [davidphilipbarr](https://github.com/davidphilipbarr)
* Hardware Supported:
    * [Sweep](https://github.com/davidphilipbarr/Sweep) (all versions)
    * [Hypergarlic](https://github.com/davidphilipbarr/hypergolic/tree/main/hypergarlic)
    * Variants of the same 34-key direct pin PCB
* Hardware Availability: order PCBs with gerber files from the repository

Make example for this keyboard (after setting up your build environment):

    make cradio:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Setting Handedness

Keyboard uses [handedness by EEPROM](https://docs.qmk.fm/#/feature_split_keyboard?id=handedness-by-eeprom) as default. The make commands are:

    make cradio:default:dfu-split-left
    make cradio:default:dfu-split-right

[QMK Toolbox](http://qmk.fm/toolbox) can also be used to set EEPROM handedness. Place the controller in bootloader mode and select menu option Tools -> EEPROM -> Set Left/Right Hand

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key on the left half (or the top right right key on the right half) and plug in the controller on that side.
* **Physical reset button**: Briefly press the reset button soldered on the PCB.
* **Keycode in layout**: Press the key mapped to `RESET` if it is configured.
