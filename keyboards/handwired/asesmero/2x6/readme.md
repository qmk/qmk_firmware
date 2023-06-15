# Asesmero 2x6

![Asesmero 2x6](https://i.imgur.com/ZHLcrb2h.jpg)

A simple 2x6 Keyboard made for use it as a streamdeck.


* Keyboard Maintainer: [Antonio Sesmero](https://github.com/asesmero)
* Hardware Supported: Sparkfun ProMicro (ATMEGA32U4), RP2040 Dev Boards
* Hardware Availability: 3d Printed & handwired.

Make example for this keyboard (after setting up your build environment):
    
    Promicro:
    make handwired/asesmero/2x6/promicro:default
    
    RP2040:
    make handwired/asesmero/2x6/rp2040:default

Flashing example for this keyboard:

    Promicro:
    make handwired/asesmero/2x6/promicro:flash
    
    RP2040:
    make handwired/asesmero/2x6/rp2040:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the top left key) and plug in the keyboard
