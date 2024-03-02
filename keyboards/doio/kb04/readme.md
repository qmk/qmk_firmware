# doio/kb04

![doio/kb04](https://i.imgur.com/lqABZw4h.png)

A macropad that have 4-key keyboard made by DOIO, which controlled by an APM32F103CBT6 chipset. The keyboard features per-key RGB and 1 encoder.

* Keyboard Maintainer: [filmstarr](https://github.com/filmstarr)
* Hardware Supported: DOIO Knob Board - KB04
* Hardware Availability: [keebmonkey.com](https://www.keebmonkey.com/products/megalodon-macro-pad-with-a-knob)

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb doio/kb04 -km default

Flashing example for this keyboard:

    qmk flash -kb doio/kb04 -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (1! key) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
