# DOIO KB03-01

![KB03-01](https://i.imgur.com/bnlDpkY.png)

QMK for Megalodon DOIO Dual Layer Knob 3 Key macropad.

* Keyboard Maintainer: [clownfish-og](https://github.com/clownfish-og)
* Hardware Supported: DOIO KB03-01 using APM32F103CBT6 (clone STM32F103CBT6)
* Hardware Availability: https://www.keebmonkey.com/products/megalodon-dual-layer-knob-macro-pad

Make example for this keyboard (after setting up your build environment):

    make doio/kb03:default

Flashing example for this keyboard:

    make doio/kb03:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
