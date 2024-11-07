# Teton 78 QMK Firmware

## Introduction

![Teton 78](https://i.imgur.com/MnASIrv.jpeg)

This is the QMK firmware repository for the Teton78, a 68XT solder and hotswao keyboard designed by Mountain Mech Designs - Bennett Balogh.

The Teton 78 has entered GB and sucessfully finalized in November 2024 The IC page for the keyboard can be found [here](https://geekhack.org/index.php?topic=123275.0).
The sale page can be found [here](https://www.mountainmechdesigns.com/)
Discord link can be found [here](https://discord.gg/h9dMwRNfVy)

## About

* Keyboard Maintainer: [Bennett Balogh](https://github.com/AwesomeBalogh)
* Hardware Supported: Atmega32u4
* Hardware Availability: N/A

## How to compile

After setting up your build environment, you can compile the Teton 78 default keymap by using:

    make mountainmechdesigns/teton_78:default

Flash using

    make mountainmechdesigns/teton_78:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader 

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available