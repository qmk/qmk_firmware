# Matrice Pad Classic (Macropad)

![matrice_pad_classic](https://imgur.com/a/bY6L8Nx)

A simple 3x4 macropad utilizes the Arduino Pro Micro

* Keyboard Maintainer: [Matrice Technologies](https://github.com/matricetechnologies)
* Hardware Supported: Matrice Pad Classic, ATmega32U4
* Hardware Availability: https://matricetech.com

Make example for this keyboard (after setting up your build environment):

    make matrice_technologies/matrice_pad_classic:default

Flashing example for this keyboard:

    make matrice_technologies/matrice_pad_classic:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
