# ENTER67 - PCB

![enter67](https://imgur.com/igF8Lurh.jpg)

67 layout PCB, with option for stepped Caps Lock

* Keyboard Maintainer: https://github.com/LXF-YZP
* Hardware Supported: enter67 PCB

Make example for this keyboard (after setting up your build environment):
    
    make enter67:default
    
Flashing example for this keyboard:

    make enter67:default:flash
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available