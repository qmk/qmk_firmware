# Piantor UV 44

![Piantor UV 44](https://i.ibb.co/QvJM1GR/20240806-PIANTORUV44-00.png)

PiantorUV44 is a Piantor/Cantor fork with Raspberry Pi Pico, hybrid hotswap socket and soldered-in switches support and flippable PCB.

* Keyboard Maintainer: [azhizhinov](https://github.com/azhizhinov)
* Hardware Supported: RP2040
* Hardware Availability: https://github.com/azhizhinov/PIANTORUV44

Make example for this keyboard (after setting up your build environment):

    make piantoruv44:default

Flashing example for this keyboard:

    make piantoruv44:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Hold the `BOOT` button on the Pico and press the `RST` button on the Pico, release the the `RST` button before the `BOOT` button.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
Once you enter the bootloader, the keyboard will show up as a USB device on your computer, you could drag and drop a firmware file to flash it, but I recommend using the flash commands for the respective side.
