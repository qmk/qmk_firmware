# KBDCraft Adam0110b

![Adam0110b](https://i.imgur.com/2XqTtGS.png)

A 64-key custom mechanical keyboard with a brick-built case + 17-key numpad. 

# Note
This uses the `tinyuf2` bootloader, which makes the board show up as a drive when put into bootloader mode, requiring a `.uf2` file for flashing. This isn't the same as with the `KBDCraft adam64` which uses the `stm32-dfu`, which requires QMK Toolbox for flashing.

* Keyboard Maintainer: QMK community
* Hardware Supported: STM32F401
* Hardware Availability: https://kbdcraft.store/products/adam

Make example for this keyboard (after setting up your build environment):

    make kbdcraft/adam0110:default

Flashing example for this keyboard:

    make kbdcraft/adam0110:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **UF2 bootloader**: Double-tap the RXT pads on the under-side of the circuit board.
* **Bootmagic reset**: Hold down the top left key (Escape) and plug in the keyboard.
* **DFU**: Bridge the BOT pad, and tap the RXT pad on the under-side of the circuit board.