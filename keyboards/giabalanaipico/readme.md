# giabalanaipico

![giabalanaipico_logo](https://i.imgur.com/ZAKmV17h.png)
![giabalanaipico overview](https://i.imgur.com/A5JE5vOh.jpg)

A chromatic button accordion MIDI keyboard without bellows, Raspberry Pi Pico version.

* Keyboard Maintainer: [3araht](https://github.com/3araht)
* Hardware Supported: giabalanaipico keyboard, a split keyboard mainly work as MIDI keyboard.
* Hardware Availability: [BOOTH](https://3araht.booth.pm/). Click [here](https://www.tenso.com/en/static/lp_shop_booth) for BOOTH overseas shipping!

Make example for this keyboard (after setting up your build environment):

    make giabalanaipico:default

Flashing example for this keyboard:

    make giabalanaipico:default:flash

Run this while Raspberry Pi Pico is in bootloader mode.
## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly double-tap the reset button on the side of the PCB
* **Physical BOOTSEL button**: Press the BOOTSEL button and hold it while you connect a micro USB cable to your computer.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
