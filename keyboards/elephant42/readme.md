# elephant42

[![elephant42](https://i.imgur.com/rgvNteb.jpg)](https://i.imgur.com/rgvNteb.jpg)

A split keyboard with 3x5+2 vertically staggered keys and 4 thumb keys.

* Keyboard Maintainer: [illness072](https://github.com/illness072), [Twitter](https://twitter.com/illness072)
* Hardware Supported: elephant42 PCB, ProMicro
* Hardware Availability: [https://illness072.booth.pm/](https://illness072.booth.pm/)  

Make example for this keyboard (after setting up your build environment):

    make elephant42:default

Flashing example for this keyboard:

    make elephant42:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
