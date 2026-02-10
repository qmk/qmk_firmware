# E8ghty

![trnthsn/e8ghty](https://imgur.com/M4Oudco.png)

A TKL keyboard PCB compatible with various keyboard cases. Supports both right USB Type-C connector and bottom USB Type-C connector, 1 FPC header, and 3 JST SH positions for a daughter board.

* Keyboard Maintainer: [ThanhSon.Mech](https://github.com/trnthsn)
* Hardware Supported: STM32F103/STM32F072, Geon F1 xx, TKD Cycle 8, Keycult, ...
* Hardware Availability: [ThanhSon.Mech](https://www.facebook.com/ThanhSon.mech)

Make example for this keyboard (after setting up your build environment):

    make trnthsn/e8ghty:default

Flashing example for this keyboard:

    make trnthsn/e8ghty:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
