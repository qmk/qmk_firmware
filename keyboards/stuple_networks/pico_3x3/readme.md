# Pico 3x3 Macropad

A custom 3x3 macropad using the Raspberry Pi Pico (RP2040).

- Keyboard Maintainer: [Mitsuba100](https://github.com/Mitsuba100/)
- Hardware Supported: Pico-3x3 rev1
- Hardware Availability: [PCB](https://github.com/Stuple-Networks/Pico-3x3/tree/main/PCB) [Rasberry Pi Pico](https://www.raspberrypi.com/products/raspberry-pi-pico/)

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb stuple_networks/pico_3x3 -km default

Flashing example for this keyboard:

    qmk flash -kb stuple_networks/pico_3x3 -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.


## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
