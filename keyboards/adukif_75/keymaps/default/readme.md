# adukif 75%

![%adukif75%](imgur.com image replace me!)

*A short description of the keyboard/project*

* Keyboard Maintainer: [%Luka_Aduashvili%](https://github.com/lukaaduashvili)
* Hardware Supported: Custom PCB using STM32F103C8T6
* Hardware Availability: Currently Nowhere personal project

Make example for this keyboard (after setting up your build environment):

    make adukif_75:default

Flashing example for this keyboard:

    make adukif_75:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
