# Paws 60

A PCB that has been inspired by Bakeneko 60 from kkatano [GitHub](https://github.com/kkatano/bakeneko-60)

But more changes has been added: Hotswap socket, ...

* Keyboard Maintainer: [HorrorTroll](https://github.com/HorrorTroll)
* Hardware Supported: Atmega32u4
* Hardware Availability: [Open source on GitHub](https://github.com/HorrorTroll/KeebProj/tree/default/paws60/pcb/Hotswap)

Make example for this keyboard (after setting up your build environment):

    make horrortroll/paws60:default

Flashing example for this keyboard:

    make horrortroll/paws60:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (3,6) in the matrix (B key) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
