# HexBoard

![HexBoard](https://i.imgur.com/8vtaXb7h.jpg)

*The HexBoard is a 140-key hexagonal MIDI controller which can double as a 120% keyboard*

* Keyboard Maintainer: [Zach DeCook](https://github.com/earboxer)
* Hardware Supported: Dev Unit with RP2040 Processor, HexBoard Production Unit (1.1)
* Hardware Not Supported: Dev Unit with Teensy Processor
* Hardware Availability:
	* HexBoard Production Unit (1.1) https://shapingthesilence.com/tech/hexboard-midi-controller/ Since 2023.

The ["Arduino" firmware](https://sr.ht/~earboxer/HexBoard/) remains the official firmware for the HexBoard, but QMK can be used as an alternative which offers keyboard functionality.

Make example for this keyboard (after setting up your build environment):

    make hexboard/1_1:default
    make hexboard/dev:default

Flashing example for this keyboard:

    make hexboard/1_1:default:flash
    make hexboard/dev:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Flashing the Firmware

0. When you run the flash command, it will say "Waiting for drive to deploy..."
1. On the production model, hold the little button next to the USB-C port when plugging it in.
    * On the dev model, hold the little button labeled RPBOOT while plugging it in
2. Mount the device on your computer
3. The flash command will copy the uf2 file onto the mounted device
4. Wait (maybe seven seconds)
