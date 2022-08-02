# Alexa Hotswap PCB by Maker Keyboards

The following is the QMK Firmware for the Alexa Hotswap PCB for [Maker Keyboards](https://www.makerkeyboards.com/).
---

* Keyboard Maintainer: [mrnoisytiger](https://github.com/mrnoisytiger)
* Hardware Supported: Alexa Hotswap PCB (ATmega32U4)
* Hardware Availability: [Maker Keyboards](https://www.makerkeyboards.com/products/alexa)

Make example for this keyboard (after setting up your build environment):

    make lucid/alexa:default

Flashing example for this keyboard:

    make lucid/alexa:default:flash

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `RESET` if it is available (Fn+Backslash by default)

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
