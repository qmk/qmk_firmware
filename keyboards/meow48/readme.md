# Meow48

*"Meow48" is a keyboard with a narrow pitch of 40%(48keys) exclusively for Kailh Choc.

* Keyboard Maintainer: [tsubuan145](https://github.com/tsubuan145)
* Hardware Supported: It is created with KiCAD 6.0.9.
* Hardware Availability: (https://tsubuan-145.booth.pm/items/4231893)

Make example for this keyboard (after setting up your build environment):

    make meow48:default
    
Flashing example for this keyboard:

    make meow48:default:flash
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
