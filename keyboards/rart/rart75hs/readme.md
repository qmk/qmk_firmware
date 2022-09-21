# [RART 75 Hotswap](https://github.com/alabahuy/RART/tree/master/RART75)

![RART 75](https://i.imgur.com/FVWlm8Uh.jpeg)

75% pcb with encoder, based on IMKG (Indonesia Mechanical Keyboard Group)

* Keyboard Maintainer: [Alabahuy](https://github.com/alabahuy)
* Hardware Supported: RART75 PCB, Atmega32a, Type C, Encoders
* Hardware Availability: Private GB

Make example for this keyboard (after setting up your build environment):

    make rart/rart75hs:default

Flashing example for this keyboard:

    make rart/rart75hs:default:flash

## Bootloader

Enter the bootloader in 3 ways:

* To Enter the bootloader you can short and hold boot pin, short reset pin, release reset and boot pin. 

* Bootmagic reset, hold down the key at (0,0) in the matrix (ESC) and plug in the keyboard. 

* Bootloader reset on the matrix, hold down key at (0,1) and plug in the keyboard


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
