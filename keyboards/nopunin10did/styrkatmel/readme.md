# Viktus Styrka Atmel Edition

The Viktus Styrka is a 65% + left macro block created in a collaboration of OneCreativeMind and BlindAssassin111 (Viktus owner).

This is a custom Atmel ISO Hotswap PCB for the Viktus Styrka designed and maintained by NoPunIn10Did.

* Firmware Maintainer: [nopunin10did](https://github.com/nopunin10did)
* Hardware Supported: Styrka
* Hardware Availability: <https://www.Viktus.Design>

Make example for this keyboard (after setting up your build environment):

    make nopunin10did/styrkatmel:default

Flashing example for this keyboard:

    make nopunin10did/styrkatmel:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at the top left in the macro columns (default: F1) and plug in the keyboard.
* **Physical reset button**: Briefly press the button on the back of the PCB.
* **Keycode in layout**: Press the key mapped to `QK_BOOT`. For the default layout, hold down the rightmost 1.25u key on the bottom row, then tap the top-left key in the macro columns.