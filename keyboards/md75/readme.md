# md75

![md77](https://drop.com/buy/xd75-aluminum-mechanical-keyboard)

This is keyboard layout for the Massdrop XD75, aka md75

* Keyboard Maintainer: [Nick Solarz](https://github.com/nsolarz)
* Hardware Supported: Massdrop XD75 clone
* Hardware Availability: https://drop.com/buy/xd75-aluminum-mechanical-keyboard

Make example for this keyboard (after setting up your build environment):

    make md75:default

Flashing example for this keyboard:

    make md75:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
