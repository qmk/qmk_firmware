# amj84

![amj84](https://i.imgur.com/oKAkyBW.jpeg)

A 84 key keyboard by AMJ

* Keyboard Maintainer: [peepeetee](https://github.com/peepeetee)
* Hardware Supported: AMJ84
* Hardware Availability: no longer available

Make example for this keyboard (after setting up your build environment):

    make amjkeyboard/amj84:default

Flashing example for this keyboard:

    make amjkeyboard/amj84:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
