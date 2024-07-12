# Sleepy Keeb

![sleepy_keeb](https://i.imgur.com/y3cessF.jpeg)

The Sleepy Keeb is a hand-wired keyboard based on the 4x12 Planck layout. The Sleepy Keeb integrates hot-swap socket and diode holders into the plate for easier building.

- Keyboard Maintainer: [Sleepy Craft Studios](https://github.com/sleepy-craft-studios)
- Hardware Supported: Pro Micro development board (and clones/adapations of)
- Hardware Availability: [Sleepy Craft Studios Shop](https://sleepycraftstudios.com/shop) for kits and full builds, [Sleepy Craft Studios Downloads](https://sleepycraftstudios.com/downloads) for CC-BY-SA-NC licensed stl files for 3D printing.

Make example for this keyboard (after setting up your build environment):

    make sleepy_keeb:default

Flashing example for this keyboard:

    make sleepy_keeb:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

- **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
- **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
- **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
