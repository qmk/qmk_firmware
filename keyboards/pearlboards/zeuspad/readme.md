# Zeuspad

![Zeuspad](https://i.imgur.com/F657DWwh.png)

Zeuspad is the perfect numpad complement to my TKL, Zeus. Standalone it is a glorious numpad with an encoder, oled and rgb.

* Keyboard Maintainer: Koobaczech
* Hardware Supported: Zeuspad
* Availability: https://pearlboards.net/products/zeuspadl-coming-2022?variant=39642771718276

Make example for this keyboard (after setting up your build environment):

    make pearlboards/zeuspad:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly press the button on the front of the PCB labeled `RESET`
* **Keycode in layout**: Press the key mapped to `QK_BOOT` in conjunction with the key mapped to `MO(1))` 
