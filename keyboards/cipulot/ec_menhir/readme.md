# EC Menhir

![EC Menhir](https://i.imgur.com/m0feb2Zh.png)

EC version of the Menhir.

* Keyboard Maintainer: [cipulot](https://github.com/cipulot)
* Hardware Supported: EC Menhir
* Hardware Availability: [fruitykeeb](https://fruitykeeb.xyz/)

Make example for this keyboard (after setting up your build environment):

    make cipulot/ec_menhir:default

Flashing example for this keyboard:

    make cipulot/ec_menhir:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical Boot0 pins**: Short the Boot0 pins on the back of the PCB while plugging in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
