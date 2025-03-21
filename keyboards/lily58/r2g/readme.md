# Lily58 R2G

![Lily58_R2G](https://i.imgur.com/4vPkIQ5.png)

Lily58 R2G is factory assembled version of the Lily 58 featuring hotswap and perkey RGB.

* Keyboard Maintainer: [Elliot Powell](https://github.com/e11i0t23)
* Hardware Supported: Lily58 R2G PCB
* Hardware Availability: [Mechboards UK](https://mechboards.co.uk/products/lily58-r2g-ready2go-kit)

Make example for this keyboard (after setting up your build environment):

    make lily58/r2g:mb_via

Flash example for this keyboard:

    make lily58/r2g:mb_via:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

These PCBs have a reset on the underside of the PCB next to the controller which may be pressed to enter in to the bootloader.

Additionally, if you hold down the "ESC" or "GRV" buttons when plugging in that half of the keyboard (per the default QWERTY layout), this will jump to the bootloader and reset the EEPROM (persistent storage).
