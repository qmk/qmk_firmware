# ZodiarkPi

![ZodiarkPi](https://i.imgur.com/iOvyZLMh.jpeg)

WIP (Ignore the picture of the ZodZero)

* Keyboard Maintainer: [Aleblazer](https://github.com/Aleblazer/), [Discord Link](https://discord.gg/BCSbXwskVt)
* Hardware Supported: Raspberry Pi Pico/Waveshare RP2040 Plus
* Hardware Availability: [Split Logic Keyboards](https://splitlogic.xyz/)

## Make example for this keyboard (after setting up your build environment):

    make aleblazer/zodiarkpi:default

## Flashing example for this keyboard:
    make aleblazer/zodiarkpi:default: flash
    
## Bootloader

Remove the interconnect USB-C cable from halves, plug host into one side, hold boot, press reset, release boot. Move the UF2 file to the removable media. Repeat process on the other side.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
