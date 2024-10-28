<<<<<<<< HEAD:keyboards/trnthsn/e8ghtyneo/readme.md
# E8ghtyNeo

![E8ghtyNeo](https://imgur.com/YXYfqzZ.png)

A TKL keyboard PCB compatible with Neo80. Supports Neo80 keyboard like an out-of-the-box PCB without any modification.

* Keyboard Maintainer: [Trnthsn](https://github.com/trnthsn)
* Hardware Supported: STM32, E8ghtyNeo, Neo80
========
# S6xty5 Rev.2

![S6xty5 Rev.2](https://i.imgur.com/ag7Y7wp.jpg)


A 65% keyboard PCB compatible with various keyboard cases. Supports a left USB Type-C connector, 5 JST SH1.0 and 2 JST ZH1.25 positions for a daughter board

![Layout](https://i.imgur.com/vZrh43p.jpg)

* Keyboard Maintainer: [Trnthsn](https://github.com/trnthsn)
* Hardware Supported: STM32, S6xty5 Rev.2, Bakeneko65, Krush65
>>>>>>>> 5a06f63f15 ([Keyboard] Add support s6xty5 rev.2):keyboards/trnthsn/s6xty5r2/readme.md
* Hardware Availability: [ThanhSon.Mech](https://www.facebook.com/ThanhSon.mech)

Make example for this keyboard (after setting up your build environment):

<<<<<<<< HEAD:keyboards/trnthsn/e8ghtyneo/readme.md
    make trnthsn/e8ghtyneo/stm32f072:default

Flashing example for this keyboard:

    make trnthsn/e8ghtyneo/stm32f072:default:flash
========
    make trnthsn/s6xty5r2:default

Flashing example for this keyboard:

    make trnthsn/s6xty5r2:default:flash
>>>>>>>> 5a06f63f15 ([Keyboard] Add support s6xty5 rev.2):keyboards/trnthsn/s6xty5r2/readme.md

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
