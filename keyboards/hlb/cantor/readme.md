# HLB CantorMX F411

Project based on original Cantor keyboard (42 key diodeless split keyboard), designed with simplicity in mind. It is inspired on the popular [corne](https://github.com/foostan/crkbd), [ferris](https://github.com/pierrechevalier83/ferris) and [sweep](https://github.com/davidphilipbarr/Sweep) keyboards, aiming to provide a more ergonomic (stronger column stagger) corne-like layout with a simple, easy to assemble and cheap design.
We upgraded blackpill version to STM32F411 8Mhz therefore original firmware maintained by [Diego Palacios](https://github.com/diepala) must be adapted to this hardware.
A case design has beed made to get a full 3DP Cantor project (see below)

* Keyboard Maintainer: [HLB H3lli0n](https://github.com/H3lli0n)
* Hardware Supported: Blackpill STM32F411 8Mhz only
* Hardware Availability: https://github.com/H3lli0n/CantorMx-3DP-case

This firmware is made for EE_HANDS split, to build and flash your firmwares (left and right) please follow the examples below with hand in DFU mode:

Make+flash example for this split (after setting up your build environment):
  make hlb/cantor:vial::dfu-util-split-left
  make hlb/cantor:vial::dfu-util-split-right

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the thumb key on the left and plug in the keyboard. For the right side, hold the thumb key on the right and plug the keyboard.
* **Physical reset button**: 
  * Press and hold the BOOT0 button.
  * Press and release the NRST button.
  * Release the BOOT0 button.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
