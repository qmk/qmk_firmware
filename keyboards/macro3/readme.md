# Macro3

![Macro3](https://github.com/filterpaper/filterpaper.github.io/raw/main/images/macro3.png)

Macro3 is a low-profile macro pad with dual encoder support designed by [@davidphilipbarr](https://github.com/davidphilipbarr).

## Keyboard Info

* Keyboard Maintainer: [filterpaper](https://github.com/filterpaper), [davidphilipbarr](https://github.com/davidphilipbarr)
* Hardware Supported: [Macro3](https://github.com/davidphilipbarr/Macropads/tree/main/macro3)
* Hardware Availability: order PCBs with gerber file from the repository

Make example for this keyboard (after setting up your build environment):

    make macro3:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top right key and plug in the controller.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is configured.
* **Physical reset pins**: Briefly short the RST and GND pins on the microcontroller using tweezers, a paperclip, or any other conductive material.

