# Handwired Planck

A compact 40% (12x4) ortholinear keyboard.

* Keyboard Maintainer: [Ronnie Nissan](https://github.com/ronniedroid)
* Hardware Supported: Blackpill F411

Make example for this keyboard (after setting up your build environment):

    make handwired/ronniedroid_f411:default 

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Press and hold the `BOOT0` button, press and release the `NRST` button, release the `BOOT0` button - if the board has no physical keys, you must do the same by shorting the pins.
* **Keycode in layout**: Press the key mapped to `RESET` if it is available

Flashing example for this keyboard:

    make handwired/ronniedroid_f411:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
