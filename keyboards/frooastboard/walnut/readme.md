# Frooastboard Walnut

![frooastboard/walnut](https://i.imgur.com/4erTDZqh.jpg)

This is the Frooastboard Walnut keyboard. It is made of walnut wood, has 48 underglow LEDs and a solid aluminum base plate. It uses a USB Type-C connector and will likely be available for sale soon.

* Keyboard Maintainer: [Frooastside](https://github.com/Frooastside)
* Hardware Supported: Frooastboard Walnut
* Hardware Availability: [Frooastboard Github](https://github.com/Frooastside/Frooastboard)

Make example for this keyboard (after setting up your build environment):

    make frooastboard/walnut:default

Flashing example for this keyboard:

    make frooastboard/walnut:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
