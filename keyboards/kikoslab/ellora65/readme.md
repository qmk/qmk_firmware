# Ellora65

65% With Macro Column, Encoder, and OLED

* Keyboard Maintainer: Kiko
* Hardware Supported: KL-65 PCB
* Hardware Availability: https://www.kikoslab.com

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (1,0) in the matrix (escape key) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

Make example for this keyboard (after setting up your build environment):

    make kikoslab/ellora65:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
