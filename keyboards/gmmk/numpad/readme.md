# GMMK NUMPAD

A 17 Key macropad made ans old by Glorious LLC, equiped with a WB32 microcontroller, with support for a rotary encoder.

* Keyboard Maintainer: [GloriousThrall](https://github.com/GloriousThrall)
* Hardware Supported: GMMK Numpad
* Hardware Availability: [GloriousPCGaming.com](https://www.gloriousgaming.com/products/gmmk-numpad)

Make example for this keyboard (after setting up your build environment):

    make gmmk/numpad:default

Flashing example for this keyboard:

    make gmmk/numpad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the Num key and plug in the keyboard
* **Keycode in layout**: Press the Num+Del key which is mapped to `QK_BOOT`

## Broken

* Slider does not function
* Rotary input push button (mapped to gpio)