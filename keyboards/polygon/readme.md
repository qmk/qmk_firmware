# polygon

![Polygon](https://i.imgur.com/f5n6o7d.jpeg)

*Polygon, a 65% with an ISO and an ANSI layout*

* Keyboard Maintainer: [Rotwitt](https://github.com/rotwitt)
* Hardware Supported: *ATMEGA32U4*
* Hardware Availability: *[Discord](https://discord.gg/kQbxZnJdfF)*

### Compiling the firmare

#### ANSI

    qmk compile -kb polygon/ansi -km default

#### ISO

    qmk compile -kb polygon/iso -km default

The two layouts have distinct electrical layouts and the firmware compiled will not be cross-compatible.

### Flashing the firmware

I recommend using QMK toolbox to flash the firmware.


  See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead

