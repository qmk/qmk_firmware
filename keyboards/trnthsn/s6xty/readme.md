# S6xty

![trnthsn/s6xty](https://i.imgur.com/YJZxxqY.png)

A 60% keyboard PCB compatible with various keyboard cases. Supports a left USB Type-C connector or 3 JST SH positions for a daughter board

* Keyboard Maintainer: [ThanhSon.Mech](https://github.com/trnthsn)
* Hardware Supported: s6xty PCB, STM32F072
* Hardware Availability: [ThanhSon.Mech](https://www.facebook.com/ThanhSon.mech)

Make example for this keyboard (after setting up your build environment):

    make trnthsn/s6xty:default

Flashing example for this keyboard:

    make trnthsn/s6xty:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
