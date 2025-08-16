# Cata

![Cata](https://i.imgur.com/6jGENr9.jpeg)

Cata is a 34 key ortholinear keyboard, powered by a Waveshare RP2040-Zero.

* Keyboard Maintainer: [skarrmann](https://github.com/skarrmann)
* Hardware Supported: Cata PCBs with RP2040-Zero
* Hardware Availability: [Cata GitHub repository](https://github.com/skarrmann/cata)

Make example for this keyboard (after setting up your build environment):

    make cata:default

Flashing example for this keyboard:

    make cata:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the top left key) and plug in the keyboard.
* **Physical reset button**: Double-tap the RESET button on the RP-2040 Zero (button on the right).
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.
