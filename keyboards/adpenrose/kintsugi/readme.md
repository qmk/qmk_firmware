# Kintsugi

![kintsugi](https://i.imgur.com/HPdmzdCl.jpeg)

A 65%-ish keyboard with some extra features.

## Features

* Powered by an ATmega32u4 microcontroller (current version needs an Elite-C to work).
* Encoder.
* OLED screen.
* Underglow.
* Hotswap sockets.

## General info

* Keyboard Maintainer: [Arturo Avila](https://github.com/ADPenrose)
* Hardware Supported: Kintsugi V1 PCB
* Hardware Availability: [Arturo Avila](https://github.com/ADPenrose)

Make example for this keyboard (after setting up your build environment):

    make kintsugi:default

Flashing example for this keyboard:

    make kintsugi:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the front of the Elite-C microcontroller _**before soldering**_ it to the PCB- some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
