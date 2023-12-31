# snes_macropad

![Completed Build](https://i.imgur.com/WzzPJ3Yh.jpg)
*Completed Build*

![Completed Build, closer with RGB off](https://i.imgur.com/D7ki7Kkh.jpg)
*Completed Build, closer with RGB off*

![PCB and FR4 top/bottom plates](https://i.imgur.com/TgOev7lh.jpg)
*PCB and FR4 top/bottom plates*

The SNES Macropad is, as it sounds, a macropad that features a SNES connector. In addition it has a qwiic connector and a 3.5mm jack for 3.3V I2C (not audio), allowing additional expansion.

This QMK implementation exposes the SNES controller as a part of the keyboard, meaning you can map the controller to do anything a qmk keyboard can. The layout is thus a 4x6 keyboard logically, split with the 3 first rows being on the macro pad and the 3 following being buttons on the snes controller.

* Keyboard Maintainer: [JBarberU](https://github.com/jbarberu)
* Hardware Supported: SNES Macropad Rev 1, with a Raspberry Pi Pico Lite (AliExpress clone of Raspberry Pico with fewer grounds and all GPIO's exposed on the headers)
* Hardware Availability: The SNES Macro pad can be found [here](https://www.tindie.com/products/jbarberu/snes-macropad/) either as a kit, partially built or fully built.

Make example for this keyboard (after setting up your build environment):

    make snes_macropad:default

Flashing example for this keyboard:

    make snes_macropad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Physical bootsel button**: Hold down the bootsel button on the RPi Pico while plugging in the keyboard, or while pressing the reset button
* **Physical reset button**: Quickly double press the reset button
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
