# HexBoard

![HexBoard](https://zachdecook.com/HexBoard/qmk.jpg)

*The HexBoard is a MIDI controller which can double as a 120% keyboard*

* Keyboard Maintainer: [Zach DeCook](https://github.com/earboxer)
* Hardware Supported: Dev Unit with RP2040 Processor, HexBoard Production Unit (1.1)
* Hardware Not Supported: Dev Unit with Teensy Processor
* Hardware Availability:
	* HexBoard Production Unit (1.1) https://shapingthesilence.com/tech/hexboard-midi-controller/ Since 2023.

The ["Arduino" firmware](https://sr.ht/~earboxer/HexBoard/) remains the official firmware for the HexBoard, but QMK can be used as an alternative which offers keyboard functionality.

Make example for this keyboard (after setting up your build environment):

```sh
# make the default keymap (similar to the official firmware)
make hexboard/1_1:default
# make the 'keyboard' keymap (part keyboard, part music device)
make hexboard/1_1:keyboard
# make the 'keyboard' keymap for the dev unit
make hexboard/dev:keyboard
```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Flashing the Firmware

1. On the production model, hold the little button next to the USB-C port when plugging it in.
    * On the dev model, hold the little button labeled RPBOOT while plugging it in
2. Mount the device on your computer
3. Copy the uf2 file onto the mounted device
4. Wait (maybe seven seconds)
