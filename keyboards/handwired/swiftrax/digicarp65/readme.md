# DigiCarp65

A 65% keyboard

* Keyboard Maintainer: Swiftrax
* Hardware Supported: DigiCarp65
* Hardware Availability: https://github.com/swiftrax

Make example for this keyboard (after setting up your build environment):

    make handwired/swiftrax/digicarp65:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (top left key)and plug in the keyboard
* **Physical reset button**: Briefly short the pad on the back of the PCB labeled QK_BOOT
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
