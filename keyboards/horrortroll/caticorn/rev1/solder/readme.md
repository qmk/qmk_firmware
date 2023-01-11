# Caticorn Solder (Rev 1)

A TKL keyboard, which controlled by an RP2040 chipset.

* Keyboard Maintainer: [HorrorTroll](https://github.com/HorrorTroll)
* Hardware Supported: RP2040
* Hardware Availability: Prototype PCB

Make example for this keyboard (after setting up your build environment):

    make horrortroll/caticorn/rev1/solder:default

Flashing example for this keyboard:

    make horrortroll/caticorn/rev1/solder:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (Esc key) and plug in the keyboard
* **Physical reset button**: Press and hold the button on the back of the PCB, then plug USB onto PC
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
