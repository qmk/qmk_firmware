# null65ansi v1

![sp](https://i.imgur.com/zO7Jlwj.png)

65% tray mount PCB with RGB per key.

* Keyboard Maintainer: [Quark](https://github.com/quark-works)
* Hardware Supported: PCB
* Hardware Availability: https://nulldesignco.com/

Make example for this keyboard (after setting up your build environment):

    make nulldesignco/null65ansi/v1:default

Flashing example for this keyboard:

    make nulldesignco/null65ansi/v1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical boot button**: Hold the button labeled as "BOOT" on the back of the board or short the two pads on the front while you connect the keyboard to your computer.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available