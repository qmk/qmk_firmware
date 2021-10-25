# Cradio

![Cradio](https://github.com/davidphilipbarr/hypergolic/raw/main/hypergarlic/ht.png)

Cradio are 34-key split-keyboards designed by [@davidphilipbarr](https://github.com/davidphilipbarr), with no diodes and every key wired directly to the micro-controller pins.

## Keyboard Info

* Keyboard Maintainer: [davidphilipbarr](https://github.com/davidphilipbarr)
* Hardware Supported:
    * [Sweep](https://github.com/davidphilipbarr/Sweep)
    * [Hypergarlic](https://github.com/davidphilipbarr/hypergolic/tree/main/hypergarlic)
    * (Similar 34-key designs using the same direct pins)

Make examples for this keyboard (after setting up your build environment):

    make cradio:default

Firmware uses `EE_HANDS` split handedness. Each halve should be flashed once with the following:

    make cradio:default:dfu-split-left
    make cradio:default:dfu-split-right

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 4 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard. (With `EE_HANDS` configured, hold down the top right key on the right half to place the right controller in bootloader mode)
* **Physical reset button**: If a reset button was installed, briefly press the button on the back of the PCB. 
* **Short RST on MCU**: Briefly short the RST and GND pins on the microcontroller using tweezers, a paperclip, or any other conductive material.
* **Keycode in layout**: Press the key mapped to `RESET` if it is available.

