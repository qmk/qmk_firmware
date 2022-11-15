# BINEPAD BN006

The BN006 is a CNC machined 6-key macropad

* Keyboard Maintainer: [Binepad](https://github.com/binepad)
* Hardware Supported: BN006
* Hardware Availability: [Binepad.com](https://www.binepad.com/bn006)

Make example for this keyboard (after setting up your build environment):

    make binepad/bn006:default

Flashing example for this keyboard:

    make binepad/bn006:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.
Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` *(or `RESET`)* if it is available
