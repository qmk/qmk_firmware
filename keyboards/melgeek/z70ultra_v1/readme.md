# Z70 Ultra v1

![z70ultra](https://drive.google.com/file/d/1m8Qra8L7Nq4I-ewq1_GkKi9j0LVPN7_l/view?usp=sharing)

A hotswap 65% RGB Custom Mechanical keyboard.

* Keyboard Maintainer: [MelGeek](https://github.com/melgeek001365)
* Hardware Supported: Z70 Ultra v1 20230821
* Hardware Availability: [MelGeek](https://www.melgeek.com/)

Make example for this keyboard (after setting up your build environment):

    make melgeek/z70ultra_v1/rev1:default
	
Flashing example for this keyboard:

    make melgeek/z70ultra_v1/rev1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

# Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
