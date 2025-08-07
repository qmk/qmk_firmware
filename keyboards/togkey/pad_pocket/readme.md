# pad_pocket

![pad_pocket](https://i.imgur.com/yCrqAe5.jpeg)

A simple 2-Key Macropad Keychain based off an RP2040 Development Board and a custom PCB that is pre-programmed to control media.

* Keyboard Maintainer: [Jon Henry](https://github.com/togkey86)
* Hardware Supported: Togkey Pad Pocket/Duo PCB, RP2040 Pro Micro Development Board
* Hardware Availability: (https://togkey.com)

Make example for this keyboard (after setting up your build environment):

     make togkey/pad_pocket:default

Flashing example for this keyboard:

    make togkey/pad_pocket:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (The left key closest to the USB Port) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available