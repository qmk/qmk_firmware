# Mach 3

A 3x3 macropad with RGB underglow. 
Note: It sets an output pin to high, which is the alimentation of the backlight circuit.

* Keyboard Maintainer: [etiennelepagel](https://github.com/etiennelepagel)
* Hardware Supported: Mach 3 from Mach Keyboards
* Hardware Availability: [Mach Keyboards Official Website](https://machkeyboards.com/)

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

Make example for this keyboard (after setting up your build environment):

    make machkeyboards/mach3:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
