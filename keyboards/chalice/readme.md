# Chalice

A Cheap Alice, powered by a Pro-Micro

* Keyboard Maintainer: [CustomKBD](https://github.com/customkbd/)
* Hardware Supported: Pro-Micro (or equivalent - Sea Micro, Elite-C etc.)
* Hardware Availability: [CustomKBD](https://customkbd.com/products/chalice-pre-order)

Make example for this keyboard (after setting up your build environment):

    make chalice:default

Flashing example for this keyboard:

    make chalice:default:flash
    
## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down Escape and plug in the keyboard.
* **Physical reset button**: Briefly press the reset button below the pro-micro.
* **Keycode in layout**: The `RESET` key can be found by holding `FUNC` in between the space bars and pressing `ESC`.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
