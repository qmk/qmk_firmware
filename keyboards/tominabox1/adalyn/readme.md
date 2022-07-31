# Adalyn

![Adalyn](https://i.imgur.com/3mGQlh2.jpg)

*A cool QAZ-Alice hybrid designed by [Marv](https://github.com/MarvFPV/Adalyn) with a PCB by [tominabox1](https://github.com/tominabox1)*
* Keyboard Maintainer: [tominabox1](https://github.com/tominabox1)
* Hardware Supported: Adalyn PCB, atmega32u4
* Hardware Availability: Open source on @tominabox1 GitHub

Make example for this keyboard (after setting up your build environment):
    make tominabox1/adalyn:default
Flashing example for this keyboard:
    make tominabox1/adalyn:default:flash
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
## Bootloader
Enter the bootloader in 3 ways:
* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
