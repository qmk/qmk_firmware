# MidEvil

<img width="600" src="https://user-images.githubusercontent.com/800930/274618949-4c9ed22e-2058-478e-86d4-d0328ce30bf2.jpg" />

If number pads are evil, then this keyboard places all that evilness smack dab in the middle.

* Keyboard Maintainer: [dcpedit](https://github.com/dcpedit)
* Hardware Supported: Raspberry Pi Pico, RP2040-Plus
* Hardware Availability: https://github.com/dcpedit/midevil

Make example for this keyboard (after setting up your build environment):

    make dcpedit/midevil:default

Flashing example for this keyboard:

    make dcpedit/midevil:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the ESC key (top-left key) and plug in the keyboard
* **Physical reset button**: On the Raspberry Pi Pico, while holding down the BOOT button, press and release the RESET button
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available