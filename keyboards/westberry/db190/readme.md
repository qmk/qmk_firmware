
# WestBerryTech DB190 keyboard

* Keyboard Maintainer: [JoyLee](https://github.com/itarze)
* Hardware Supported: WestBerryTech bd190 pcb
* Hardware Availability: [WestBerryTech](http://www.westberrytech.com)

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb westberry/db190 -km via

Flashing example for this keyboard:

    qmk flash -kb westberry/db190 -km via

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button below the space key
* **Keycode in layout**: Press the key mapped to `QK_BOOT` 
