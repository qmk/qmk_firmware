# HexBoard

![HexBoard](https://shapingthesilence.com/wp-content/uploads/2023/05/IMG_7850-scaled-e1683770617108.jpeg)

*The HexBoard is a MIDI controller which can double as a 120% keyboard*

* Keyboard Maintainer: [Zach DeCook](https://github.com/earboxer)
* Hardware Supported: *The PCBs, controllers supported*
* Hardware Availability: https://shapingthesilence.com/tech/hexboard-midi-controller/

Make example for this keyboard (after setting up your build environment):

    make hexboard:default

Flashing example for this keyboard:

    make hexboard:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
