# pad_plus

![pad_plus](https://i.imgur.com/9g3gNMZ.jpeg)

A 6-Key Macropad featuring a Oled Screen and Rotary Encoder based off an RP2040 and custom PCB.

* Keyboard Maintainer: [Jon Henry](https://github.com/togkey86)
* Hardware Supported: TogKey Pad Plus PCB, RP2040 Development Board
* Hardware Availability: (https://togkey.com)

Make example for this keyboard (after setting up your build environment):

    make togkey/pad_plus:default

Flashing example for this keyboard:

    make togkey/pad_plus:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
