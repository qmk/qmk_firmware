# 2d4d

![2d4d](https://i.imgur.com/famGFG8h.jpg)

![2d4d_2](https://i.imgur.com/IfoQUnch.jpg)


*Handwired %50 keyboard (48 switches) There is 2 places for rotary encoders/switches and 2 indicator leds. You can use switches instead of rotary encoder just break the extensions from thumb cluster.*

* Keyboard Maintainer: [mechMehmet](https://github.com/mechMehmet)
* Hardware Supported: *f401 blackpill*
* Hardware Availability: [3d model](https://www.thingiverse.com/thing:5798852)

Make example for this keyboard (after setting up your build environment):

    make 2d4d:default

Flashing example for this keyboard:

    make 2d4d:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
