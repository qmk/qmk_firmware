# Worm Eaten

![takashicompany/worm_eaten](https://i.imgur.com/8rIFpDRh.jpg)

Worm Eaten" is a simple design that can be assembled in a variety of ways.

It can be used as a 20-key macro pad, but can also be used as a split keyboard by connecting two units together with a TRRS cable.

Two units can also be soldered together to form a 40-key integrated keyboard.

The PCB can also be modified as a plate to fix the keyswitches.

LEDs and OLEDs can also be mounted.
MX and Choc(v1) keyswitches can be installed.

* Keyboard Maintainer: [takashicompany](https://github.com/takashicompany)
* Hardware Supported: PCB
* Hardware Availability: Pro Micro

Make example for this keyboard (after setting up your build environment):

    make takashicompany/worm_eaten/split:default

or 

    make takashicompany/worm_eaten/integrated:default

Flashing example for this keyboard:

    make takashicompany/worm_eaten/split:default:flash

or

    make takashicompany/worm_eaten/integrated:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
