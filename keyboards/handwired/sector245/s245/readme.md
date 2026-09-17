# S245 Streamdeck

A 3x3 macropad with rotary encoder.

* Keyboard Maintainer: [sector245](https://github.com/sinomau)
* Hardware Supported: S245 Streamdeck PCB, RP2040

Make example for this keyboard (after setting up your build environment):

    make handwired/sector245/s245:default

Flashing example for this keyboard:

    make handwired/sector245/s245:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (top left key) and plug in the keyboard
* **Physical reset button**: Hold the BOOTSEL button on the Pico and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
