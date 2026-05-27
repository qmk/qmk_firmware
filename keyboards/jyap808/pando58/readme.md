# Pando58

![Pando58 - 3D printed case](https://i.imgur.com/e01JcXL.jpeg)

![Pando58 - Layered build](https://i.imgur.com/JyufNvG.jpeg)

*58-key columnar split keyboard driven by RP2040 Zero controllers, utilizing RJ45 sockets for interconnect.*

[Build guide](https://jyap808.github.io/pando58)

* Keyboard Maintainer: [jyap808](https://github.com/jyap808)
* Hardware Availability: [github/jyap808/pando58](https://github.com/jyap808/pando58)
* Hardware Supported: RP2040 Zero

Make example for this keyboard (after setting up your build environment):

    make jyap808/pando58:default

Flashing example for this keyboard:

    make jyap808/pando58:default:flash

See the [build environment setup](getting_started_build_tools) and the [make instructions](getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
