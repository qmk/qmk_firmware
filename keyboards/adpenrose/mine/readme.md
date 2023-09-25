# Mine

![mine](https://i.imgur.com/P9s2cI8h.jpg)

A hotswap ISO/ANSI-compatible 1800 alice, assembled only with THT components, including a solenoid and a chunky encoder.

* Keyboard Maintainer: [Arturo Avila](https://github.com/ADPenrose)
* Hardware Supported: Mine v1 PCB
* Hardware Availability: [Arturo Avila](https://github.com/ADPenrose)

Make example for this keyboard (after setting up your build environment):

    make adpenrose/mine:default

Flashing example for this keyboard:

    make adpenrose/mine:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Hold down the button labeled "BOOT" and briefly press the button labeled "RESET" on the front of the PCB. To exit the bootloader mode, briefly press the button labeled "RESET" once more.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
