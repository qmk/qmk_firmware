# Dactyl Manuform (5x6) with 3 thumb cluster

![Dactyl Manuform (5x6) with 3 thumb cluster](https://i.imgur.com/q7OX3Fq.jpeg)

[Build log](https://julianyap.com/posts/2025-11-16-1763340628/)

* Keyboard Maintainer: [jyap808](https://github.com/jyap808)
* Hardware Supported: Pro Micro

Make example for this keyboard (after setting up your build environment):

    make handwired/dactyl_manuform/5x6_3:default

Flashing example for this keyboard:

    make handwired/dactyl_manuform/5x6_3:default:flash

See the [build environment setup](getting_started_build_tools) and the [make instructions](getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
