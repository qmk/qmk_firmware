# TwentyPad

![TwentyPad](https://i.imgur.com/e1Bsg1M.jpeg)

A simple twenty-key macro pad, built to learn PCB design.

* Keyboard Maintainer: [Harry Cutts](https://github.com/HarryCutts)
* Hardware Supported: ATMEGA32U4 on a [custom PCB](https://github.com/HarryCutts/twentypad/)

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb handwired/twentypad -km default

Flashing example for this keyboard:

    qmk flash -kb handwired/twentypad -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the top left key) and plug in the keyboard
* **Physical reset button**: Press the button marked `SWR1` in the top-left of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
