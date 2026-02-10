# Slimdash

![mzmkb/slimdash/rev1](https://i.imgur.com/ymf8ROw.jpeg)

__SlimDash__ is a slim low profile split ortho-staggered keyboard inspired by omkbd/ErgoDash
with following key highlights:

* Ortho-Staggered Split keyboard layout
* Slim body (20-22mm depending on key caps and rubber feet used)
* Rigid body structure
* Per-Key RGB LED Matrix lighting
* USB-C connector
* Easy build utilizing PCBA service for the harder SMT components
* Keyboard Maintainer: [mizma](https://github.com/mizma)
* Hardware Supported: [SlimDash](https://github.com/mizma/SlimDash/)
* Hardware Availability: Build your own using design data at [SlimDash](https://github.com/mizma/SlimDash/)

Make example for this keyboard (after setting up your build environment):

    make mzmkb/slimdash/rev1:default

Flashing example for this keyboard:

    make mzmkb/slimdash/rev1:default:flash

You may also enter Bootloader on your keyboard, and copy the `mzmkb_slimdash_*_*.uf2`
file into the `RPI-RP2` drive shown in your PC.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools)
and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide)
for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* __Reset button__: Double-tap the RESET button on the side of the keyboard near
  TRRS jack.
* __Physical reset button__: Hold BOOT_SW and press RESET on the side of the keyboard
  near TRRS jack.
* __Keycode in layout__: Press the key mapped to `QK_BOOT` if it is available
