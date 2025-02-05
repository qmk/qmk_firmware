# S6xty5Neo Rev.2

![S6xty5Neo Rev.2](https://imgur.com/C6X3fCI.png)

A 65% keyboard PCB compatible with Neo65. Supports Neo65 keyboard like an out-of-the-box PCB without any modification.

* Keyboard Maintainer: [Trnthsn](https://github.com/trnthsn)
* Hardware Supported: STM32, S6xty5Neo Rev.2, Neo65
* Hardware Availability: [ThanhSon.Mech](https://www.facebook.com/ThanhSon.mech)

Make example for this keyboard (after setting up your build environment):

    make trnthsn/s6xty5neor2:default

Flashing example for this keyboard:

    make trnthsn/s6xty5neor2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
