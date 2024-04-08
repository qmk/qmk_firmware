# dasbob

![alt text](https://github.com/GroooveBob/DASBOB/blob/main/pic/dasbob.png)

DASBOB is a 36-key diodeless split with splay and buzzer.

* Keyboard Maintainer: [grooovebob](https://github.com/grooovebob)
* Hardware Supported: elite c
* Hardware Availability: https://github.com/GroooveBob/DASBOB

Make example for this keyboard (after setting up your build environment):

    make dasbob:default

Flashing example for this keyboard:

    make dasbob:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
