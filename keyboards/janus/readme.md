# Janus

![Janus](https://i.imgur.com/7Lzhafeh.jpg)

A 34-key split ortholinear keyboard, powered by two Seeed XIAO RP2040.

* Keyboard Maintainer: [Steven Karrmann](https://github.com/skarrmann)
* Hardware Supported: Janus PCBs, Seeed XIAO RP2040
* Hardware Availability: [Janus GitHub repository](https://github.com/skarrmann/janus)

Make example for this keyboard (after setting up your build environment):

    make janus:default

Flashing example for this keyboard:

    make janus:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

If you would like to plug in your keyboard using either half, then set the EEPROM left/right UF2 bootloader parameter when flashing each half for the first time. Refer to [QMK's handedness by EEPROM documentation](https://docs.qmk.fm/features/split_keyboard#handedness-by-eeprom). Without this bootloader parameter, the configuration assumes the left half will be plugged in.

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key on the left half, or top right key on the right half, and then plug in the USB cable on that keyboard half.
* **Physical reset button**: Double tap the reset button on the XIAO RP2040.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.
