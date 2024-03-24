# ergodox_extended

![ergodox_extended](https://i.imgur.com/GKVULLC.png)

This version of the ErgoDox has 7 rows and 7 columns per side, for a total of 98 usable keys. This should result in less necessity for layer hopping and macros.

* Keyboard Maintainer: [Adam Coleman](https://github.com/Gephorian)
* Hardware Supported: [ErgoDox Extended PCB](https://github.com/Gephorian/ergodox-extended)
* Hardware Availability: Hardware is available only through a fab like JLCPCB, Elecrow, or PCBWay. Or, Oshpark if you're adventurous.

Make example for this keyboard (after setting up your build environment):

    make ergodox_extended:default

Flashing example for this keyboard:

    make ergodox_extended:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button near the MCU on the PCB.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
