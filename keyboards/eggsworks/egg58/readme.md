# egg58

* Keyboard Maintainer: [Travis Mick](https://github.com/tmick0)
* Hardware Supported: egg58 (v1-v2.x) PCB, with Pro Micro or compatible MCU
* Hardware Availability: https://eggs.works/ or https://github.com/eggsworks/egg58

Make example for this keyboard (after setting up your build environment):

    make eggsworks/egg58:default

Flashing example for this keyboard:

    make eggsworks/egg58:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
