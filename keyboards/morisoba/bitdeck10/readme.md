# morisoba/bitdeck10

![morisoba/bitdeck10](https://imgur.com/ca8egkz.jpg)
BitDeck10 is a 5x2 keys + 1 rotary encoder macro keyboard with OLED.

* Keyboard Maintainer: [morisoba](https://github.com/morisobaR)
* Hardware Supported: BitDeck10 PCB, XIAO RP2040
* Hardware Availability: [PCB & Case Data](https://github.com/morisobaR/BitDeck10)

Make example for this keyboard (after setting up your build environment):

    make morisoba/bitdeck10:default

Flashing example for this keyboard:

    make morisoba/bitdeck10:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Press the "B" button on the XIAO RP2040 and plug in the keyboard. Or hold the "B" button and press the "R" button on the XIAO RP2040.
* **Physical reset button**: Briefly press the "R" button on the XIAO RP2040.
