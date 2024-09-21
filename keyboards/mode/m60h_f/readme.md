# Mode Tempo M60H_F

![Mode Tempo M60H_F](https://i.imgur.com/6Wo7ySh.png)

The following is the QMK Firmware for the Mode Tempo M60H_F PCB.

* Keyboard Maintainer: [ToastyStoemp](https://github.com/ToastyStoemp)
* Hardware Supported: Mode Tempo M60H_F PCB.
* Hardware Availability: https://modedesigns.com/products/tempo

Make example for this keyboard (after setting up your build environment):

    make mode/m60h_f:default

Flashing example for this keyboard:

    make mode/m60h_f:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader Enter the bootloader in 3 ways: 
* **Bootmagic reset**: Hold down the key ESC key and plug in the keyboard (Top Left most switch)
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if available
* **Physical Reset Button**: Hold down the button on the back of the PCB
