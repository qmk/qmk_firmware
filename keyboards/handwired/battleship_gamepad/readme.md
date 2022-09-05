# Battleship Gamepad

![Battleship Gamepad](https://imgur.com/FCpQfzQ.jpg)

A hand-wired 3d-printed mechanical keyboard intended for one hand with an analog thumbstick for movement. The layout matches the left side of large "battleship" keyboards with their extra bank of 2x5 1u F keys.

Build instructions and 3d printer files can be found in the [project github repo](https://github.com/abraini-Nascent/battleship_gamepad)

* Keyboard Maintainer: [arbraini](https://github.com/abraini-Nascent)
* Hardware Supported: Arduino Pro Micro
* Features: 40 keys in an ortho layout and an analog thumbstick.

Make example for this keyboard (after setting up your build environment):

    make handwired/battleship_gamepad:default
    
Flashing example for this keyboard:

    make handwired/battleship_gamepad:flash

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the top left key in the 2x5 bank) and plug in the keyboard.
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead.
* **Keycode in layout**: Press the key mapped to `QK_BOOT`.  In the default layout this is the key at (0,0) on layer 1.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
