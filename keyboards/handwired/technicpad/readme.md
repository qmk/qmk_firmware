# TechnicPad

![TechnicPad](https://i.imgur.com/LPD0KSL.jpg)

A 4% (2x2) macropad, that is compatible to technic building blocks. 

* Keyboard Maintainer: [Niclas Hirschfeld](https://github.com/nwhirschfeld)
* Hardware Supported: Pro Micro boards
* Hardware Availability: for now TechnicPad is handwired and uses an Arduino pro micro. [TechnicPad repository](https://github.com/nwhirschfeld/TechnicPad) 

Make example for this keyboard (after setting up your build environment):

    make handwired/technicpad:default

Flashing example for this keyboard:

    make handwired/technicpad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the upper left key and plug in the keyboard
* **Physical reset**: Short the _RST_ and _GND_ pins of the PCB
* **Keycode in layout**: Press the key mapped to QK_BOOT if it is available
