# AULA F75 Ultra

A 75% tri-mode mechanical keyboard manufactured by AULA.

* Keyboard Maintainer: QMK Community
* Hardware Supported: AULA F75 Ultra
* Hardware Availability: https://aulaindia.com/product/aula-f75ultra-75-tri-mode-rgb-wireless-mechanical-gaming-keyboard-whiteblue-matcha-latte-switch-f75ultrawuml/

Make example for this keyboard (after setting up your build environment):

    make aula/f75_ultra:default

Flashing example for this keyboard:

    make aula/f75_ultra:default:flash

## Bootloader

Enter the bootloader using one of the following methods:

* **Bootmagic reset**: Hold the Escape key while plugging in the keyboard.
* **Keycode reset**: Press the key mapped to `QK_BOOT` if available.

The keyboard uses the WB32 DFU bootloader.

See the [build environment setup](https://docs.qmk.fm/newbs_getting_started) and the [make instructions](https://docs.qmk.fm/newbs_building_firmware) for more information.
