# Super 16 V2

A 4x4 macropad with RGB inswitch lighting and underglow. 

* Keyboard Maintainer: [MechMerlin](https://github.com/mechmerlin)
* Hardware Supported: 1upkeyboards Super 16 V2
* Hardware Availability: [1upkeyboards](https://1upkeyboards.com/)

Make example for this keyboard (after setting up your build environment):

    make 1upkeyboards/super16v2:default

Flashing example for this keyboard:

    make 1upkeyboards/super16v2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
