# lilith101

![lilith101](imgur.com image replace me!)

*A short description of the keyboard/project*

* Keyboard Maintainer: [Technorage Developments](https://github.com/St0RM53)
* Hardware Supported: Prototype PCB, Custom full-size alike compact ANSI 101+1 key layout, Running Teensy 3.2 with integrated 4-port USB 2.0 hub, SK9816/SK6805 ARGB leds per key, 128x32 oled screen, rotary encoder, and hotswappable Kailh Choc V1 switches.
* Hardware Availability: https://www.facebook.com/TechnoRageDevelopments/

Make example for this keyboard (after setting up your build environment):

    make lilith101:default

Flashing example for this keyboard:

    make lilith101:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available