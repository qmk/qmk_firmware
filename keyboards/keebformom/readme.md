# Keeb For Mom

![KeebForMom](https://i.imgur.com/MvBatHSh.jpg)

KFM is a low cost 4x5 modular mechanical keyboard that everyone can build. Modular it's mean two PCBs can be combined become one 40% keyboard, so you can use the PCB board as single 4x5 macro pad or 4x10 ortholinier mechanical keyboard. The PCB board has some feature like south facing switches orientation, RGB perkey and passive buzzer supported which can be used as layer indicator.

* Keyboard Maintainer: [sandipratama](https://github.com/nendezkombet)
* Hardware Supported: KFM PCB
* Hardware Availability: https://github.com/nendezkombet/Keeb-For-Mom

Make example for this keyboard (after setting up your build environment):

    make keebformom:default

Flashing example for this keyboard:

    make keebformom:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
