# mzmkb/slimdash/rev1

![mzmkb/slimdash/rev1](imgur.com image replace me!)

__slimDash__ is a slim low profile split ortho-staggered keyboard inspired by omkbd/ergoDash
with following key highlights:

* Minimum soldering using PCBA services
  * Only require Kailh Choc sockets, and a few through hole components.
  * (Optional) RGB LED soldering
* Slim body and Uses the low profile Kailh Choc V1 switches.
* Supports Backlight RGB for each key.
* USB-C connector instead of micro-B
* Keyboard Maintainer: [mizma](https://github.com/mizma)
* Hardware Supported: [slimDash](https://github.com/mizma/slimdash/)
* Hardware Availability: Build your own using design data at [slimDash](https://github.com/mizma/slimdash/)

Make example for this keyboard (after setting up your build environment):

    make mzmkb/slimdash/rev1:default

Flashing example for this keyboard:

    make mzmkb/slimdash/rev1:default:flash

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
