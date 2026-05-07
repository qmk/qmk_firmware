# pad

![pad](https://i.imgur.com/KMS1btN.jpeg)

A simple 5-Key Macropad based off an RP2040 and custom PCB.

* Keyboard Maintainer: [Jon Henry](https://github.com/togkey86)
* Hardware Supported: TogKey Pad PCB, RP2040 Pro Micro Development Board
* Hardware Availability: (https://togkey.com)

Make example for this keyboard (after setting up your build environment):

     make togkey/pad:default

Flashing example for this keyboard:

    make togkey/pad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
