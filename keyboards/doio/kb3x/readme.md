# doio/kb3x

QMK for DOIO Three Knobs .

* Keyboard Maintainer: DOIO2022
* Hardware Supported: DOIO Three Knobs

Make example for this keyboard (after setting up your build environment):

    make doio/kb3x:default

Flashing example for this keyboard:

    make doio/kb3x:default:flash

See the build [environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the front of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
