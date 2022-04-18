# Formula 1800

Southpaw 1800 With Dual Encoder Option

* Keyboard Maintainer: Kiko
* Hardware Supported: Formula 1800 PCB
* Hardware Availability: https://www.kikoslab.com

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,2) in the matrix (Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB 
* **Keycode in layout**: Press the key mapped to `RESET` if it is available

Make example for this keyboard (after setting up your build environment):

    make kikoslab/formula1800:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
