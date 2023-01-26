# DigiCarpice

Alice like keyboard with arrow keys

* Keyboard Maintainer: Swiftrax
* Hardware Supported: DigiCarpice
* Hardware Availability: https://github.com/swiftrax

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (top left key) and plug in the keyboard
* **Physical reset button**: short the pads on the back of the pcb
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

Make example for this keyboard (after setting up your build environment):

    make handwired/swiftrax/digicarpice:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
