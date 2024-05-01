# Adware

![Adware](https://i.imgur.com/2WTMjDL.jpeg)

A Hotswap Multi-layout F13 TKL PCB (h88c compatible) powered by RP2040.

* Keyboard Maintainer: Mai The San
* Hardware Supported: Adware
* Hardware Availability: [Adware](https://paramountkeeb.com/products/adiuvare-ad-ware-tkl)

Make example for this keyboard (after setting up your build environment):

    make chikenman/adware:default

Flashing example for this keyboard:

    make chikenman/adware:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly short the `RST` and `GND` pads on the SWD header twice, or short the `BOOT` header and plug in keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
