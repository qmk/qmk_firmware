# Alchemist Keyboards is0GR

is0GR Keyboard

Keyboard Maintainer: [Andrew Kannan](https://github.com/awkannan)  
Hardware Supported: STM32F072CBT6 or equivalent  

Make example for this keyboard (after setting up your build environment):

    make cannonkeys/is0gr:default

Flashing example for this keyboard:

    make cannonkeys/is0gr:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (on this board - it's the only key) and plug in the keyboard
* **Physical reset button**: Bridge the two pads labeled "RESET" on the top of the PCB using some tweezers, and hold the tweezers there until the board enters the bootloader mode
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available (it isn't by default)
