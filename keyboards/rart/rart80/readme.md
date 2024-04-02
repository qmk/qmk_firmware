# [RART 80 Hotswap]

![RART 80](https://i.imgur.com/QCeTuBeh.png)

PCB layout TKL, based on IMKG (Indonesia Mechanical Keyboard Group)

* Keyboard Maintainer: [Alabahuy](https://github.com/alabahuy)
* Hardware Supported: RART80 PCB, Atmega32a, Type C
* Hardware Availability: Private GB

Make example for this keyboard (after setting up your build environment):

    make rart/rart80:default

Flashing example for this keyboard:

    make rart/rart80:default:flash

## Bootloader

Enter the bootloader in 3 ways:

* To Enter the bootloader you can short and hold boot pin, short reset pin, release reset and boot pin. 

* Bootmagic reset, hold down the key at (0,0) in the matrix (ESC) and plug in the keyboard. 

* Bootloader reset on the matrix, hold down key at (0,1) and plug in the keyboard


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
