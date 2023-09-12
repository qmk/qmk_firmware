# %KEYBOARD%

![%KEYBOARD%](imgur.com image replace me!)

A 60% custom mechanical keyboard with a brick-built case.

An updated version of the KBDCraft Adam64 keyboard.

* Keyboard Maintainer: QMK community
* Hardware Supported: STM32F401
* Hardware Availability: https://kbdcraft.store/products/adam

Make example for this keyboard (after setting up your build environment):

    make kbdcraft/adam0110:default

Flashing example for this keyboard:

    Enter UF2 bootloader mode, and copy the UF2 file (`kbdcraft_adam0110_default.uf2`) to the USB mass storage device.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **UF2 bootloader**: Double-tap the RXT pads on the under-side of the circuit board.
* **Bootmagic reset**: Hold down the top left key (Escape) and plug in the keyboard.
* **DFU**: Bridge the BOT pad, and tap the RXT pad on the under-side of the circuit board.
