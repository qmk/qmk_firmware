# Steezy60

A universal 60% PCB for both tray mount and o-ring mount

* Keyboard Maintainer: [4pplet](https://github.com/4pplet)
* Hardware Supported: Ratio60 Rev B

Make example for this keyboard (after setting up your build environment):

    make rationalist/ratio60_hotswap/rev_a:default

Flashing example for this keyboard:

    make rationalist/ratio60_hotswap/rev_a:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down Escape and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB or short the reset header
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
