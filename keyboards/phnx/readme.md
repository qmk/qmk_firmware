# PHNX Unibody Split

[![phnx.png](https://raw.githubusercontent.com/sini6a/phnx/main/assets/20240428_165111.jpg)](https://www.youtube.com/watch?v=Z5Uw6cO_Igg)

An unibody split ergonomic keyboard featuring 54 keys, each equipped with customizable addressable LEDs. Powered by ATMega and based on Miryoku.

-   Keyboard Maintainer: [sini6a](https://github.com/sini6a)
-   Hardware Supported: PHNX PCB

Make example for this keyboard (after setting up your build environment):

    make phnx:default

Flashing example for this keyboard:

    make phnx:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

-   **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard.
-   **Keycode in layout**: Press the key mapped to `QK_BOOT`. Accessible through function layer plus Escape key.
