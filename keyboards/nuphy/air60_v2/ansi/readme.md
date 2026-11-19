# NuPhy Air60 V2

*NuPhy Air60 V2 is a tri-mode wireless 64 key keyboard (USB + 2.4GHz RF + Bluetooth x3).*

![NuPhy Air60 V2](https://bit.ly/48qfjbS)

* Keyboard Maintainer: [nuphy](https://github.com/nuphy-src)
* Hardware Supported: NuPhy Air60 V2 PCB (STM32F072, dual IS31FL3733)
* Hardware Availability: [nuphy.com](https://nuphy.com)

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb nuphy/air60_v2/ansi -km default

Flashing example for this keyboard:

    qmk flash -kb nuphy/air60_v2/ansi -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in one way:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
