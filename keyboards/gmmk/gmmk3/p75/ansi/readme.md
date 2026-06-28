# GMMK3 75% (ANSI)

A keyboard made and sold by Glorious LLC. Equipped with the WestBerry Q95 microcontroller.

* Keyboard Maintainer: [Glorious](TBD)
* Hardware Supported: GMMK V3
* Hardware Availability: [GloriousPCGaming.com](https://www.pcgamingrace.com)

Make example for this keyboard (after setting up your build environment):

    make gmmk/gmmk3/p75/ansi:default

Flashing example for this keyboard:

    make gmmk/gmmk3/p75/ansi:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:
* **Bootmagic reset**: Hold down the key the top left key (usually programmed as `Esc`) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
