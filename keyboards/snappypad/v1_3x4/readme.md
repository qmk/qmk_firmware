# Snappy Pad v.1


*Easy to use Macro Pad that can be configured by via and later with also Vial*

* Keyboard Maintainer: [Niilo M](https://github.com/snappykey)
* Hardware Supported: *The PCBs, controllers supported*
* Hardware Availability: *snappykey.eu*

qmk compile -kb snappypad/v1_3x4 -km default

Flashing example for this macropad:
Use for example QMK toolbox to upload the firmware to the Snappy Pad

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Press the first key in 3x4 matrix, not the first key (next to leds)
* **Shorting the gnd and rst pins:**: Touch with conductive material gnd and rst pads
