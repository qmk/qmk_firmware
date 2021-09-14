# Charybdis Nano

A very small keyboard with a trackball, made for ergonomic enthusiasts.

* Keyboard Maintainer: [Bastard Keyboards](https://github.com/Bastardkb/)
* Hardware Supported: elite-C V4
* Hardware Availability: [Bastardkb.com](https://bastardkb.com/)

Make examples for this keyboard (after setting up your build environment):

    make bastardkb/charybdis/3x5:default
    

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

See the [keyboard build instructions](http://docs.bastardkb.com/)

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly press the button on the shield PCB (marked RST)
* **Keycode in layout**: Press the key mapped to `RESET` if it is available