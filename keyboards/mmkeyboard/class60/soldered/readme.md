# Class60

![Class60 E-Retro White](https://i.imgur.com/9T0KbBHh.jpeg)

The Class60 is a Leaf-spring/Top dual mounting 60% Keyboard that includes a buzzer and solenoid.

* Keyboard Maintainer: [lexbrugman](https://github.com/lexbrugman)
* Hardware Supported: Class60 soldered PCB
* Hardware Availability: https://www.mmkeyboard.com/products/mm-class60-retro-custom-mechanical-keyboard

Make example for this keyboard (after setting up your build environment):

    make mmkeyboard/class60/soldered:default

Flashing example for this keyboard:

    make mmkeyboard/class60/soldered:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
