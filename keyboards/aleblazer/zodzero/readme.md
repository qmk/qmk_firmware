# ZodZero

![ZodZero](https://i.imgur.com/iOvyZLMh.jpeg)

A split keyboard with 4x8 including a thumbcluster, encoders on each side (Panasonic Roller Encoder on the left), per key RGB, and 2x I2C headers per side, supporiting 1.3"/.96" 128x64 OLEDs (the 1.3" is an SSH1106 OLED, refer to QMK documentation for limitations), .91" 128x32 OLEDs. Also uses the Lil-CC interconnect daughter board for split communication over a USB-C to USB-C cable.

* Keyboard Maintainer: [Aleblazer](https://github.com/Aleblazer/), [Discord Link](https://discord.gg/BCSbXwskVt)
* Hardware Supported: RP2040-Zero
* Hardware Availability: [Split Logic Keyboards](https://splitlogic.xyz/)

## Make example for this keyboard (after setting up your build environment):

    make aleblazer/zodzero:default

## Flashing example for this keyboard:
    make aleblazer/zodzero:default: flash
    
## Bootloader

Remove the interconnect USB-C cable from halves, plug host into one side, hold boot, press reset, release boot. Move the UF2 file to the removable media. Repeat process on the other side.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).