# BINEPAD NEOKNOB KN01

![Binepad NeoKnob KN01](https://i.imgur.com/N8GXq7P.png)

The KN01 is a multifunction knob, which can be rotated, pressed, and rotated while pressed.

* Keyboard Maintainer: [Binpad](https://github.com/binepad)
* Hardware Supported: **NEOKNOB KN01**
* Hardware Availability: [Binepad.com](https://www.binepad.com/products/kn01)

Make example for this keyboard (after setting up your build environment):

    make binepad/kn01:default

Flashing example for this keyboard:

    make binepad/kn01:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.
Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).


## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the knob while plugging in the keyboard's USB cable
* **Physical reset button**: Briefly press the button on the underside of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
