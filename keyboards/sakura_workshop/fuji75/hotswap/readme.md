# Fuji75 Hotswap

![Fuji75 hotswap](https://i.imgur.com/SfucJxah.png)

* Keyboard Maintainer: [Freather](https://github.com/CMMS-Freather)
* Hardware Supported: PCB, Atmega32u4

Make example for this keyboard (after setting up your build environment):

    make sakura_workshop/fuji75/hotswap:default

Flashing example for this keyboard:

    make sakura_workshop/fuji75/hotswap:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
