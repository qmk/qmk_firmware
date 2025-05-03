# Sha

![Sha](https://i.imgur.com/4yuQwRXh.jpg)

Sha is a 50 key ortholinear keyboard, powered by a Waveshare RP2040-Zero or Waveshare RP2040-Matrix.

* Keyboard Maintainer: [Steven Karrmann](https://github.com/skarrmann)
* Hardware Supported: Sha PCBs with either RP2040-Zero or RP2040-Matrix
* Hardware Availability: [Sha GitHub repository](https://github.com/skarrmann/sha)

Make example for this keyboard (after setting up your build environment):

    make sha:default

Flashing example for this keyboard:

    make sha:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the top left key) and plug in the keyboard.
* **Physical reset button**: Doublet-tap the EN/RESET button on the MCU board.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.
